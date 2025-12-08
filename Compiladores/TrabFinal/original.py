import sys
import ply.lex as lex
import ply.yacc as yacc
from graphviz import Digraph  # Importação necessária

# ==========================================
# 1. ESTRUTURA DA AST
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
# 2. VISUALIZADOR GRAPHVIZ (NOVO)
# ==========================================

class ASTVisualizer:
    def __init__(self, ast):
        self.ast = ast
        self.dot = Digraph(comment='Abstract Syntax Tree', format='png')
        self.dot.attr(rankdir='TB')  # Top to Bottom
        self.count = 0

    def build(self):
        if self.ast:
            self._visit(self.ast)
        return self.dot

    def _visit(self, node):
        # Usa o ID único do objeto em memória para identificar o nó no grafo
        node_id = str(id(node))
        
        # Cria o rótulo do nó (Tipo + Valor se for folha)
        label = node.type
        if node.leaf is not None:
            label += f"\n({node.leaf})"
        
        # Define a forma e cor baseada no tipo de nó
        shape = 'ellipse'
        color = 'black'
        if node.type in ['CONST', 'ID', 'NUM']:
            shape = 'box'
            color = 'blue'
        elif node.type in ['OP', 'ASSIGN']:
            shape = 'diamond'
            color = 'orange'
            
        self.dot.node(node_id, label, shape=shape, color=color)

        # Percorre filhos e cria arestas
        for child in node.children:
            if child: # Proteção contra None
                child_id = str(id(child))
                self.dot.edge(node_id, child_id)
                self._visit(child)

# ==========================================
# 3. SCANNER (LÉXICO)
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
    t.lexer.skip(1)

lexer = lex.lex()

# ==========================================
# 4. PARSER (SINTÁTICO)
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
    if p[1] == 'void': p[0] = Node('PARAMS_LIST', children=[]) 
    else: p[0] = Node('PARAMS_LIST', children=p[1]) # Agrupando para visualizar melhor

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
    # Agrupando filhos em nós intermediários para o gráfico ficar limpo
    decls = Node('LOCAL_DECLS', children=p[2]) if p[2] else None
    stmts = Node('STMTS', children=p[3]) if p[3] else None
    children = [c for c in [decls, stmts] if c]
    p[0] = Node('BLOCK', children=children, lineno=p.lineno(1))

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
    if p: print(f"ERRO SINTATICO: token '{p.value}', LINHA: {p.lineno}")
    else: print("ERRO SINTATICO: EOF")

parser = yacc.yacc()

# ==========================================
# 5. GERADOR DE CÓDIGO (3 ENDEREÇOS)
# ==========================================

class CodeGen:
    def __init__(self):
        self.temp_count = 0
        self.label_count = 0
    
    def new_temp(self):
        self.temp_count += 1
        return f"t{self.temp_count}"
    
    def new_label(self):
        self.label_count += 1
        return f"L{self.label_count}"

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
            print(f"{temp} = {t1} {node.leaf} {t2}")
            return temp
        elif node.type == 'ASSIGN':
            res = self.gen(node.children[1])
            var_name = node.children[0].leaf
            print(f"{var_name} = {res}")
            return var_name
        elif node.type == 'IF':
            l_else = self.new_label()
            l_end = self.new_label()
            cond = self.gen(node.children[0])
            print(f"if_false {cond} goto {l_else}")
            self.gen(node.children[1])
            print(f"goto {l_end}")
            print(f"label {l_else}")
            if len(node.children) > 2: self.gen(node.children[2])
            print(f"label {l_end}")
        elif node.type in ['BLOCK', 'PROGRAM', 'LOCAL_DECLS', 'STMTS']:
            for child in node.children: self.gen(child)
        elif node.type == 'FUN_DECL':
            print(f"\nfunc {node.leaf}:")
            # children[0] são params, children[1] é o corpo
            if len(node.children) > 1: self.gen(node.children[1])
            print(f"end func {node.leaf}")
        return ""

# ==========================================
# EXECUÇÃO PRINCIPAL
# ==========================================

if __name__ == "__main__":
    codigo_fonte = """
    int gcd(int u, int v) {
        if (v == 0) return u;
        else return gcd(v, u - u/v*v);
    }
    
    int main(void) {
        int x; 
        x = 10;
        x = x + 5 * 2;
    }
    """

    print("--- 1. PARSER ---")
    ast = parser.parse(codigo_fonte, lexer=lexer)
    
    print("\n--- 2. GERANDO VISUALIZAÇÃO ---")
    viz = ASTVisualizer(ast)
    dot = viz.build()
    
    # Salva e Renderiza o arquivo
    # 'ast_graph' será o nome do arquivo (ast_graph.pdf ou ast_graph.png)
    try:
        output_path = dot.render('ast_graph', view=True) 
        print(f"Gráfico gerado com sucesso em: {output_path}")
    except Exception as e:
        print(f"Erro ao gerar gráfico (verifique se o Graphviz está instalado no sistema): {e}")

    print("\n--- 3. CÓDIGO INTERMEDIÁRIO ---")
    cg = CodeGen()
    cg.gen(ast)