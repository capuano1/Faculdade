import sys
import ply.lex as lex
import ply.yacc as yacc
from graphviz import Digraph

# Flag para interromper a execução se tiver erro semantico
SEMANTIC_ERROR = False

# ==========================================
# 1. ESTRUTURA DA AST (Nós da Árvore)
# ==========================================

class Node:
    def __init__(self, type, children=None, leaf=None, lineno=None):
        self.type = type
        self.children = children if children else []
        self.leaf = leaf
        self.lineno = lineno
        self.val_type = None

    def __repr__(self):
        return f"<{self.type}>"

# ==========================================
# 2. VISUALIZADOR (Graphviz)
# ==========================================

class ASTVisualizer:
    def __init__(self, ast):
        self.ast = ast
        self.dot = Digraph(comment='Abstract Syntax Tree', format='png')
        self.dot.attr(rankdir='TB') 

    def build(self):
        if self.ast:
            self._visit(self.ast)
        return self.dot

    def _visit(self, node):
        node_id = str(id(node))
        label = node.type
        if node.leaf is not None:
            label += f"\n({node.leaf})"
        
        shape = 'ellipse'
        color = 'black'
        if node.type in ['CONST', 'ID', 'NUM', 'CALL']:
            shape = 'box'
            color = 'blue'
        elif node.type in ['OP', 'ASSIGN']:
            shape = 'diamond'
            color = 'orange'
            
        self.dot.node(node_id, label, shape=shape, color=color)

        for child in node.children:
            if child:
                child_id = str(id(child))
                self.dot.edge(node_id, child_id)
                self._visit(child)

# ==========================================
# 3. SCANNER (Analisador Léxico)
# ==========================================

reserved = {
    'if': 'IF', 'else': 'ELSE', 'while': 'WHILE', 'return': 'RETURN',
    'int': 'INT', 'void': 'VOID'
}

tokens = [
    'ID', 'NUM', 'PLUS', 'MINUS', 'TIMES', 'OVER',
    'LT', 'LE', 'GT', 'GE', 'EQ', 'NE', 'ASSIGN',
    'SEMI', 'COMMA', 'LPAREN', 'RPAREN', 'LBRACK', 'RBRACK', 'LBRACE', 'RBRACE'
] + list(reserved.values())

t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_OVER = r'/'
t_LT = r'<'
t_LE = r'<='
t_GT = r'>'
t_GE = r'>='
t_EQ = r'=='
t_NE = r'!='
t_ASSIGN = r'='
t_SEMI = r';'
t_COMMA = r','
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACK = r'\['
t_RBRACK = r'\]'
t_LBRACE = r'\{'
t_RBRACE = r'\}'

def t_ID(t):
    r'[a-zA-Z][a-zA-Z]*'
    t.type = reserved.get(t.value, 'ID')
    return t

def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

t_ignore = ' \t'

def t_COMMENT(t):
    r'/\*(.|\n)*?\*/'
    t.lexer.lineno += t.value.count('\n')

def t_error(t):
    print(f"ERRO LEXICO: '{t.value[0]}' LINHA: {t.lexer.lineno}")
    sys.exit(1)

lexer = lex.lex()

# ==========================================
# 4. PARSER (Analisador Sintático)
# ==========================================

precedence = (
    ('nonassoc', 'LT', 'LE', 'GT', 'GE', 'EQ', 'NE'),
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'OVER'),
)

def p_program(p):
    'program : declaration_list'
    p[0] = Node('PROGRAM', children=p[1], lineno=p.lineno(1))

def p_declaration_list(p):
    '''declaration_list : declaration_list declaration
                        | declaration'''
    if len(p) == 3: p[0] = p[1] + [p[2]]
    else: p[0] = [p[1]]

def p_declaration_var(p):
    '''declaration : type_specifier ID SEMI
                   | type_specifier ID LBRACK NUM RBRACK SEMI'''
    if len(p) == 4:
        p[0] = Node('VAR_DECL', leaf=p[2], lineno=p.lineno(2))
        p[0].val_type = p[1]
    else:
        p[0] = Node('VEC_DECL', leaf=p[2], lineno=p.lineno(2))
        p[0].val_type = p[1]; p[0].size = p[4]

def p_declaration_fun(p):
    'declaration : type_specifier ID LPAREN params RPAREN compound_stmt'
    p[0] = Node('FUN_DECL', children=[p[4], p[6]], leaf=p[2], lineno=p.lineno(2))
    p[0].val_type = p[1]

def p_type_specifier(p):
    '''type_specifier : INT
                      | VOID'''
    p[0] = p[1]

def p_params(p):
    '''params : param_list
              | VOID'''
    if p[1] == 'void': p[0] = Node('PARAMS', children=[]) 
    else: p[0] = Node('PARAMS', children=p[1])

def p_param_list(p):
    '''param_list : param_list COMMA param
                  | param'''
    if len(p) == 4: p[0] = p[1] + [p[3]]
    else: p[0] = [p[1]]

def p_param(p):
    '''param : type_specifier ID
             | type_specifier ID LBRACK RBRACK'''
    p[0] = Node('PARAM', leaf=p[2], lineno=p.lineno(2))
    p[0].val_type = p[1]

def p_compound_stmt(p):
    'compound_stmt : LBRACE local_declarations statement_list RBRACE'
    decls = Node('LOCALS', children=p[2]) if p[2] else None
    stmts = Node('STMTS', children=p[3]) if p[3] else None
    valid_children = [c for c in [decls, stmts] if c]
    p[0] = Node('BLOCK', children=valid_children, lineno=p.lineno(1))

def p_local_declarations(p):
    '''local_declarations : local_declarations declaration
                          | empty'''
    if len(p) == 3: p[0] = p[1] + [p[2]]
    else: p[0] = []

def p_statement_list(p):
    '''statement_list : statement_list statement
                      | empty'''
    if len(p) == 3: p[0] = p[1] + [p[2]]
    else: p[0] = []

def p_statement(p):
    '''statement : expression_stmt
                 | compound_stmt
                 | selection_stmt
                 | iteration_stmt
                 | return_stmt'''
    p[0] = p[1]

def p_expression_stmt(p):
    '''expression_stmt : expression SEMI
                       | SEMI'''
    p[0] = p[1] if len(p) == 3 else None

def p_selection_stmt(p):
    '''selection_stmt : IF LPAREN expression RPAREN statement
                      | IF LPAREN expression RPAREN statement ELSE statement'''
    if len(p) == 6:
        p[0] = Node('IF', children=[p[3], p[5]], lineno=p.lineno(1))
    else:
        p[0] = Node('IF', children=[p[3], p[5], p[7]], lineno=p.lineno(1))

def p_iteration_stmt(p):
    'iteration_stmt : WHILE LPAREN expression RPAREN statement'
    p[0] = Node('WHILE', children=[p[3], p[5]], lineno=p.lineno(1))

def p_return_stmt(p):
    '''return_stmt : RETURN SEMI
                   | RETURN expression SEMI'''
    if len(p) == 3: p[0] = Node('RETURN', lineno=p.lineno(1))
    else: p[0] = Node('RETURN', children=[p[2]], lineno=p.lineno(1))

def p_expression(p):
    '''expression : var ASSIGN expression
                  | simple_expression'''
    if len(p) == 4:
        p[0] = Node('ASSIGN', children=[p[1], p[3]], lineno=p.lineno(2))
    else: p[0] = p[1]

def p_simple_expression(p):
    '''simple_expression : additive_expression relop additive_expression
                         | additive_expression'''
    if len(p) == 4:
        p[0] = Node('OP', children=[p[1], p[3]], leaf=p[2], lineno=p[1].lineno)
    else: p[0] = p[1]

def p_relop(p):
    '''relop : LE
             | LT
             | GT
             | GE
             | EQ
             | NE'''
    p[0] = p[1]

def p_additive_expression(p):
    '''additive_expression : additive_expression addop term
                           | term'''
    if len(p) == 4:
        p[0] = Node('OP', children=[p[1], p[3]], leaf=p[2], lineno=p[1].lineno)
    else: p[0] = p[1]

def p_addop(p):
    '''addop : PLUS 
             | MINUS'''
    p[0] = p[1]

def p_term(p):
    '''term : term mulop factor
            | factor'''
    if len(p) == 4:
        p[0] = Node('OP', children=[p[1], p[3]], leaf=p[2], lineno=p[1].lineno)
    else: p[0] = p[1]

def p_mulop(p):
    '''mulop : TIMES 
             | OVER'''
    p[0] = p[1]

def p_factor(p):
    '''factor : LPAREN expression RPAREN
              | var
              | call
              | NUM'''
    if len(p) == 4: p[0] = p[2]
    elif isinstance(p[1], int): p[0] = Node('CONST', leaf=p[1], lineno=p.lineno(1))
    else: p[0] = p[1]

def p_call(p):
    'call : ID LPAREN args RPAREN'
    p[0] = Node('CALL', children=[p[3]], leaf=p[1], lineno=p.lineno(1))

def p_args(p):
    '''args : arg_list 
            | empty'''
    if p[1]: p[0] = Node('ARGS', children=p[1]) 
    else: p[0] = Node('ARGS', children=[])

def p_arg_list(p):
    '''arg_list : arg_list COMMA expression
                | expression'''
    if len(p) == 4: p[0] = p[1] + [p[3]]
    else: p[0] = [p[1]]

def p_var(p):
    '''var : ID
           | ID LBRACK expression RBRACK'''
    if len(p) == 2:
        p[0] = Node('ID', leaf=p[1], lineno=p.lineno(1))
    else:
        p[0] = Node('VECTOR_ID', children=[p[3]], leaf=p[1], lineno=p.lineno(1))

def p_empty(p):
    'empty :'
    pass

def p_error(p):
    if p:
        print(f"ERRO SINTATICO: token inesperado '{p.value}'", end="")
        
        if hasattr(p.lexer, 'parser'):
            parser = p.lexer.parser
            state = parser.statestack[-1]
            actions = parser.action[state]
            expected = [str(k) for k in actions.keys() if k not in ['$end', 'error']]
            
            if expected:
                expected_str = " ou ".join(expected)
                print(f", esperado '{expected_str}'", end="")
        
        print(f" LINHA: {p.lineno}")
    else:
        print("ERRO SINTATICO: Fim de arquivo inesperado")

parser = yacc.yacc()

# ==========================================
# 5. TABELA DE SÍMBOLOS & SEMÂNTICA
# ==========================================

class SymbolTable:
    def __init__(self):
        self.scopes = [{}] 
        self.all_symbols = [] 

    def enter_scope(self):
        self.scopes.append({})

    def exit_scope(self):
        self.scopes.pop()

    def insert(self, name, type_, category):
        if name in self.scopes[-1]:
            return False
        self.scopes[-1][name] = {'type': type_, 'cat': category}
        
        if len(self.scopes) == 1:
            scope_id = "Global"
        else:
            scope_id = f"Local {len(self.scopes)-1}"
            
        self.all_symbols.append({
            'name': name,
            'type': type_,
            'cat': category,
            'scope': scope_id
        })
        return True

    def lookup(self, name):
        for scope in reversed(self.scopes):
            if name in scope:
                return scope[name]
        return None

    def __str__(self):
        lines = ["=== TABELA DE SÍMBOLOS ==="]
        lines.append(f"{'NOME':<15} | {'TIPO':<10} | {'CATEGORIA':<10} | {'ESCOPO':<10}")
        lines.append("-" * 55)
        for s in self.all_symbols:
            lines.append(f"{s['name']:<15} | {s['type']:<10} | {s['cat']:<10} | {s['scope']:<10}")
        return "\n".join(lines)

def semantic_error(msg):
    global SEMANTIC_ERROR
    SEMANTIC_ERROR = True
    print(msg)

def semantic_analyze(node, symtab):
    if not node: return
    
    if node.type == 'FUN_DECL':
        if not symtab.insert(node.leaf, node.val_type, 'func'):
             semantic_error(f"ERRO SEMANTICO: Função '{node.leaf}' já declarada. LINHA: {node.lineno}")
        symtab.enter_scope()
        params_node = node.children[0]
        for param in params_node.children:
            symtab.insert(param.leaf, param.val_type, 'param')
        semantic_analyze(node.children[1], symtab)
        symtab.exit_scope()
        return

    elif node.type in ['VAR_DECL', 'VEC_DECL']:
        if not symtab.insert(node.leaf, node.val_type, 'var'):
            semantic_error(f"ERRO SEMANTICO: Variável '{node.leaf}' já declarada neste escopo. LINHA: {node.lineno}")

    elif node.type == 'ID' or node.type == 'VECTOR_ID':
        if not symtab.lookup(node.leaf):
            semantic_error(f"ERRO SEMANTICO: Variável '{node.leaf}' não declarada. LINHA: {node.lineno}")

    elif node.type == 'CALL':
        info = symtab.lookup(node.leaf)
        if not info:
            semantic_error(f"ERRO SEMANTICO: Função '{node.leaf}' não declarada. LINHA: {node.lineno}")
        elif info['cat'] != 'func':
            semantic_error(f"ERRO SEMANTICO: '{node.leaf}' não é uma função. LINHA: {node.lineno}")

    for child in node.children:
        semantic_analyze(child, symtab)

# ==========================================
# 6. GERADOR DE CÓDIGO INTERMEDIÁRIO
# ==========================================

class CodeGen:
    def __init__(self):
        self.temp_count = 0
        self.label_count = 0
        self.code_buffer = []

    def new_temp(self):
        self.temp_count += 1
        return f"t{self.temp_count}"
    
    def new_label(self):
        self.label_count += 1
        return f"L{self.label_count}"

    def emit(self, line):
        self.code_buffer.append(line)

    def get_code(self):
        return "\n".join(self.code_buffer)

    def gen(self, node):
        if not node: return ""
        
        if node.type == 'CONST':
            return str(node.leaf)
        elif node.type == 'ID':
            return node.leaf
        elif node.type == 'OP':
            t1 = self.gen(node.children[0])
            t2 = self.gen(node.children[1])
            temp = self.new_temp()
            self.emit(f"{temp} = {t1} {node.leaf} {t2}") 
            return temp
        elif node.type == 'ASSIGN':
            res = self.gen(node.children[1])
            var_name = node.children[0].leaf
            self.emit(f"{var_name} = {res}")
            return var_name
        elif node.type == 'IF':
            l_else = self.new_label()
            l_end = self.new_label()
            cond = self.gen(node.children[0])
            self.emit(f"if_false {cond} goto {l_else}")
            self.gen(node.children[1])
            self.emit(f"goto {l_end}")
            self.emit(f"label {l_else}")
            if len(node.children) > 2: self.gen(node.children[2])
            self.emit(f"label {l_end}")
        elif node.type == 'WHILE':
            l_start = self.new_label()
            l_end = self.new_label()
            self.emit(f"label {l_start}")
            cond = self.gen(node.children[0])
            self.emit(f"if_false {cond} goto {l_end}")
            self.gen(node.children[1])
            self.emit(f"goto {l_start}")
            self.emit(f"label {l_end}")
        elif node.type == 'FUN_DECL':
            self.emit(f"\nfunc {node.leaf}:")
            if len(node.children) > 1: self.gen(node.children[1])
            self.emit(f"end func {node.leaf}")
        elif node.type == 'RETURN':
            if node.children:
                res = self.gen(node.children[0])
                self.emit(f"return {res}")
            else:
                self.emit("return")
        elif node.type == 'CALL':
            args = []
            if node.children and node.children[0].type == 'ARGS':
                 for arg in node.children[0].children:
                     args.append(self.gen(arg))
            for a in args:
                self.emit(f"param {a}")
            t = self.new_temp()
            self.emit(f"{t} = call {node.leaf}, {len(args)}")
            return t
        
        elif node.children:
            for child in node.children:
                self.gen(child)
        return ""

# ==========================================
# 7. EXECUÇÃO PRINCIPAL
# ==========================================

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python compiler.py <arquivo.c>")
        sys.exit(1)

    filename = sys.argv[1]

    try:
        with open(filename, 'r', encoding='utf-8') as f:
            source_code = f.read()
    except FileNotFoundError:
        print(f"Erro: Arquivo '{filename}' não encontrado.")
        sys.exit(1)

    print(f"--- INICIANDO COMPILAÇÃO DE: {filename} ---")

    lexer.parser = parser

    ast = parser.parse(source_code, lexer=lexer)
    
    if not ast:
        print("Erro Fatal: AST não foi gerada devido a erros de sintaxe.")
        sys.exit(1)

    print("\n[OK] Análise Sintática Concluída.")

    print("\n[DEBUG] Iniciando Análise Semântica...")
    symtab = SymbolTable()
    symtab.insert('input', 'int', 'func')
    symtab.insert('output', 'void', 'func')
    
    semantic_analyze(ast, symtab)

    output_symtab = filename.split('.')[0] + "_symtab.txt"
    try:
        with open(output_symtab, 'w') as f:
            f.write(str(symtab))
        print(f"[OK] Tabela de Símbolos salva em: {output_symtab}")
    except IOError as e:
        print(f"Erro ao salvar tabela de símbolos: {e}")
    
    if SEMANTIC_ERROR:
        print("\n[FALHA] Compilação abortada devido a erros semânticos.")
        sys.exit(1)
        
    print("[OK] Verificação semântica finalizada com sucesso.")

    print("\n[DEBUG] Gerando visualização da AST...")
    viz = ASTVisualizer(ast)
    dot = viz.build()
    output_ast = filename.split('.')[0] + "_ast"
    try:
        # Mudar para cleanup=False se quiser o .dot
        file_path = dot.render(output_ast, view=True, cleanup=True)
        print(f"[OK] Gráfico da AST salvo em: {file_path}")
    except Exception as e:
        print(f"[AVISO] Graphviz não encontrado ou erro ao gerar imagem: {e}")

    print("\n[DEBUG] Gerando Código Intermediário...")
    cg = CodeGen()
    cg.gen(ast)
    
    output_code_file = filename.split('.')[0] + "_code.txt"
    try:
        with open(output_code_file, 'w') as f:
            f.write(cg.get_code())
        print(f"[OK] Código de 3 endereços salvo em: {output_code_file}")
    except IOError as e:
        print(f"Erro ao salvar arquivo de código: {e}")