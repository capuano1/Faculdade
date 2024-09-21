using System;
/*
Link para o diagram UML do Projeto

https://lucid.app/lucidchart/78f42a13-1e41-4808-a02c-e1da014b16f7/edit?viewport_loc=-1429%2C-921%2C3107%2C1352%2C0_0&invitationId=inv_28a8a5b3-e2e3-4e2c-a5d2-a9b5257834a9


Imagine que você é funcionário da Biblioteca da UNIFESP, caso um user seja novo na biblioteca (este user podendo ser aluno, professor ou um novo funcionário), 
você deve registrá-lo no banco de dados da biblioteca para poder emprestar os livros.


*/
public class Program
{    
    public static void Main(){
        Facade facade = new Facade();

        var input = 0;
        while (input != 7)
        {
            Thread.Sleep(1500);

            Console.WriteLine();        
            Console.WriteLine(  "1 - Emprestar livro.\n" +
                                "2 - Devolver livro.\n" +
                                "3 - Opções de Usuário.\n" +
                                "4 - Opções de Livro\n" +
                                "5 - Configurações do Sistema.\n" +
                                "6 - Rodar teste do projeto\n"+
                                "7 - Sair\n");
            
            input = int.Parse(Console.ReadLine().ToString());
            Console.WriteLine();
            Console.WriteLine();
            
            switch(input){

                case 1: // Emprestar livro
                    Console.WriteLine("Digite o código do livro que o usuário deseja emprestar:\n");
                    var livroc = int.Parse(Console.ReadLine().ToString());
                    Console.WriteLine();
                    Console.WriteLine("Digite o código do usuário que deseja emprestar o livro:\n");
                    var userc = Console.ReadLine().ToString();
                    Console.WriteLine();
                    
                    facade.emprestaLivro(livroc,userc);
                    break;

                case 2: // Devolver livro
                    Console.WriteLine("Digite o código do livro que o usuário deseja devolver:\n");
                    var livrocod = int.Parse(Console.ReadLine().ToString());
                    Console.WriteLine();

                    Console.WriteLine("Digite o código do usuário que deseja devolver o livro:\n");
                    var usercod = Console.ReadLine().ToString();
                    Console.WriteLine();

                    facade.devolveLivro(livrocod,usercod);
                    break;

                case 3: // Opções de Usuario
                    var a = 0;
                    while(a != 4){
                        Thread.Sleep(1500);
                        Console.WriteLine();        
                        Console.WriteLine(  "1 - Buscar usuário.\n" +
                                            "2 - Adicionar usuário.\n" +
                                            "3 - Remover usuário.\n" +
                                            "4 - Dar advertência à um aluno.\n" + 
                                            "5 - Voltar.\n");
                        a = int.Parse(Console.ReadLine().ToString());
                        Console.WriteLine();

                        switch(a){
                            case 1: // Buscar usuário

                                Console.WriteLine("Digite o código do usuário que você deseja observar:");
                                var code = Console.ReadLine().ToString();
                                Console.WriteLine();
                                facade.buscarUser(code);

                                break;

                            case 2: // Adicionar usuário

                                Console.WriteLine("Digite seu nome");
                                var nome = Console.ReadLine().ToString();
                                Console.WriteLine();

                                Console.WriteLine("Digite seu código");
                                var codigo = Console.ReadLine().ToString();
                                Console.WriteLine();

                                Console.WriteLine("Digite sua idade");
                                var idade = Convert.ToInt32(Console.ReadLine());
                                Console.WriteLine();

                                Console.WriteLine("Você é:\n1 - Aluno\n2 - Professor\n3 - Funcionário da Biblioteca\n");
                                var n = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine();

                                switch(n){
                                    case 1: //ALUNO
                                        facade.registrarAluno(nome,codigo,idade);
                                        Console.WriteLine("Aluno registrado com sucesso!\n");
                                        break;
                                    case 2: //PROFESSOR
                                        facade.registrarProfessor(nome,codigo,idade);
                                        Console.WriteLine("Professor registrado com sucesso!\n");
                                        break;
                                    case 3: //FUNCIONARIO
                                        facade.registrarFuncionario(nome,codigo,idade);
                                        Console.WriteLine("Funcionário registrado com sucesso!\n");
                                        break;
                                }

                                break;
                            
                            case 3: // Remover usuário

                                Console.WriteLine("Digite o código do usuário a ser removido: \n");
                                var cod = Console.ReadLine().ToString();
                                Console.WriteLine();

                                facade.removerUser(cod);

                                break;

                            case 4: // dar advertência
                                Console.Write("Digite o código do user que levará advertência: ");
                                facade.aplicarAdvert(Console.ReadLine().ToString());
                                break;
                            
                            case 5: // Voltar
                                break;
                        }

                    }

                    break;

                case 4: // Opções de livro
                    var b = 0;
                    while(b != 9){
                        Thread.Sleep(1500);
                        Console.WriteLine();        
                        Console.WriteLine(  "1 - Buscar livro.\n" +
                                            "2 - Adicionar livro.\n" +
                                            "3 - Remover livro.\n" +
                                            "4 - Adicionar gênero à um livro.\n"+
                                            "5 - Remover gênero de um livro.\n"+
                                            "6 - Adicionar subgênero à um livro.\n"+
                                            "7 - Remover subgênero de um livro.\n"+
                                            "8 - Alterar o número de cópias na biblioteca.\n"+
                                            "9 - Voltar.\n");

                        b = int.Parse(Console.ReadLine().ToString());
                        Console.WriteLine();

                        switch(b){
                            case 1: // Buscar livro
                            Console.WriteLine("Digite a opção de busca: ");
                                Console.WriteLine(  "1 - Por código.\n" +
                                                    "2 - Por nome.\n" +
                                                    "3 - Por autor.\n" +
                                                    "4 - Por gênero.\n");

                                var str = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine();

                                switch(str){
                                    case 1:
                                        Console.Write("Digite o código do livro: ");
                                        var cod = int.Parse(Console.ReadLine().ToString());
                                        Console.WriteLine();

                                        facade.buscaLivroCod(cod);
                                        break;
                                    
                                    case 2:
                                        Console.Write("Digite o nome do livro: ");
                                        var name = Console.ReadLine().ToString();
                                        Console.WriteLine();
                                        facade.buscaLivroNome(name);
                                        break;
                                    
                                    case 3:
                                        Console.Write("Digite o(s) autor(es) do livro: ");
                                        var author = Console.ReadLine().ToString();
                                        Console.WriteLine();

                                        facade.buscaLivroAuthor(author);
                                        break;

                                    case 4: 
                                        Console.Write("Digite o(s) gênero(s) do livro: ");
                                        var gene = Console.ReadLine().ToString();
                                        Console.WriteLine();

                                        facade.buscaLivroGenre(gene);
                                        break;
                                }
                                break;

                            case 2: // Adicionar livro
                                var x = "S";
                                string aux;
                                List<string> autore = new List<string>();

                                Console.Write("Digite o nome do livro que deseja adicionar: ");
                                string titulo = Console.ReadLine().ToString();
                                Console.WriteLine();

                                while(x != "n"){
                                    Console.Write("Digite o autor que deseja adicionar: ");
                                    aux = Console.ReadLine().ToString();
                                    Console.WriteLine();
                                    
                                    autore.Add(aux);

                                    Console.WriteLine("Deseja adicionar mais autores? (S/N)");
                                    x = Console.ReadLine().ToString().ToLower();
                                    Console.WriteLine();
                                    
                                }

                                facade.registraLivro(titulo,autore);
                                break;

                            case 3: // Remover livro
                                Console.Write("Digite o código do livro que será removido: ");
                                int codigo = int.Parse(Console.ReadLine().ToString());
                                
                                
                                facade.removeLivro(codigo);
                                Console.WriteLine("Livro removido com sucesso!\n");
                                break;

                            case 4: // Adicionar gênero de livro
                                Console.Write("Digite o código do livro que você vai adicionar o gênero: ");
                                int code = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine();

                                Console.Write("Digite o gênero que será inserido: ");
                                var genre = Console.ReadLine().ToString();
                                Console.WriteLine();

                                facade.adicionaGenero(code,genre);
                                break;

                            case 5: // Remover gênero de livro
                                Console.Write("Digite o código do livro que você vai remover o gênero: ");
                                int codi = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine();

                                Console.Write("Digite o gênero que será removido: ");
                                var genr = Console.ReadLine().ToString();
                                Console.WriteLine();

                                facade.removeGenero(codi,genr);
                                break;

                            case 6: // Adicionar subgênero de livro
                                Console.Write("Digite o código do livro que você vai adicionar o subgênero: ");
                                int scode = int.Parse(Console.ReadLine().ToString());
                                Console.Write("Digite o gênero em que será inserido subgênero: ");
                                var ger = Console.ReadLine().ToString();
                                Console.Write("Digite o subgênero que será inserido: ");
                                var sgenre = Console.ReadLine().ToString();
                                facade.adicionaSubGenero(scode,ger,sgenre);
                                break;

                            case 7: // Remover subgênero de livro
                                Console.Write("Digite o código do livro que você vai remover o subgênero: ");
                                int sco = int.Parse(Console.ReadLine().ToString());
                                Console.Write("Digite o gênero que será removido o subgênero: ");
                                var gener = Console.ReadLine().ToString();
                                Console.Write("Digite o subgênero que será removido: ");
                                var sgen = Console.ReadLine().ToString();
                                facade.removeSubGenero(sco,gener,sgen);
                                break;

                            case 8: // Alterar o número de cópias na biblioteca
                                Console.Write("Digite o código do livro que você deseja alterar o número de cópias: ");
                                var livreto = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine("Qual o novo número de copias do livro?");
                                var copias = int.Parse(Console.ReadLine().ToString());
                                facade.mudaNumeroCopias(livreto,copias);
                                break;

                            case 9:
                                break;

                        }
                    }    
                    break;

                case 5: // Opções do Sistema
                    var c = 0;
                    while(c != 8){
                        Thread.Sleep(1500);
                        Console.WriteLine();
                         Console.WriteLine( "1 - Configurar o número máximo de advertências.\n" +
                                            "2 - Configurar o número máximo de livros emprestados.\n" +
                                            "3 - Voltar");
                        c = int.Parse(Console.ReadLine().ToString());
                        Console.WriteLine();

                        switch(c){
                            case 1: // Configura maximo de advertências
                                Console.Write("Digite o número máximo de advertências que cada aluno pode receber: ");
                                int nAdvert = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine();
                                facade.configMaxAdvert(nAdvert);
                                Console.WriteLine("Número máximo de advertências alterado!\n");
                                break;
                            case 2: // Configura maximo de livros emprestados
                                Console.Write("Digite o número máximo de livros que cada aluno pode emprestar:");
                                int nBooks = int.Parse(Console.ReadLine().ToString());
                                Console.WriteLine();
                                facade.configMaxBook(nBooks);
                                Console.WriteLine("Número máximo de livros que pode emprestar alterado!\n");
                                break;
                            case 3: // Voltar
                                break;

                        }
                    }

                    break;

                case 6: // Rodar teste do projeto
                    Console.WriteLine("Criados 5 IUsers, 3 alunos, 1 professor e 1 funcionário.\n");
                    facade.registrarAluno("Evandro","1",23);
                    facade.registrarAluno("Thiago","2",21);
                    facade.registrarAluno("Guilherme","3",20);
                    facade.registrarProfessor("Fábio","4",28);
                    facade.registrarFuncionario("Lucas","5",27);
                    
                    Console.WriteLine("Criado um livro e notificação de novo livro registrado para todos os users.\n");
                    List<String> autores = ["J.K. Rolling"];
                    facade.registraLivro("Harry Potter e a Pedra Filosofal",autores);

                    Console.WriteLine("Adicionando gêneros e subgêneros ao livro.\n");
                    facade.adicionaGenero(1,"Ficção");
                    facade.adicionaGenero(1,"Aventura");
                    facade.adicionaSubGenero(1,"Ficção","Magia");


                    Console.WriteLine("Busca do livro.\n");
                    facade.buscaLivroCod(1);
                    
                    Console.WriteLine("Busca do user.\n");
                    facade.buscarUser("4");

                    Console.WriteLine("Empréstimo das 3 copias do livro \"Harry Potter e a Pedra Filosofal\".\n");
                    facade.emprestaLivro(1,"1");
                    facade.emprestaLivro(1,"2");
                    facade.emprestaLivro(1,"3");

                    Console.WriteLine("Como é registrado o user com livro emprestado.\n");
                    facade.buscarUser("1");

                    Console.WriteLine("Caso um user tente pegar emprestado um livro que não tem mais na biblioteca.\n");
                    facade.emprestaLivro(1,"5");

                    Console.WriteLine("Devolução do livro pelo user 1");
                    facade.devolveLivro(1,"1");

                    Console.WriteLine("Como é registrado o user após devolver o livro.\n");
                    facade.buscarUser("1");


                    break;

                case 7:
                    break;       

            }

        }
    }
}

