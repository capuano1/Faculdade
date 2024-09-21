using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public interface IMediator {
    public List<Book> buscaLivro (string type, string mes);
    public IUser? buscaUser (string cod);
    public void changeConfig(string configuration, int value);
    public int chainCheck (Book livro, IUser user);
    public int emprestaLivro (int codLivro, string codUser);
    public int devolveLivro (int codLivro, string codUser);
    public void notifyUser (IUser user, string message);
    public void notifyAllUsers (string message);
}

public class ConcMediator : IMediator {

    private BBD? BookBD;
    private UBD? UserBD;
    private BaseMedClass? Component;
    private IHandler? approvingChain;
    private ConfigManager config;

    public ConcMediator (BBD? book, UBD? user, BaseMedClass? comp) {
        this.BookBD = book;
        this.UserBD = user;
        this.Component = comp;
        this.config = ConfigManager.instanciaConfig();
    }

    public List<Book> buscaLivro (string type, string mes) {
        switch (type) {
            case "Código":
                return BookBD.getLivroCod(Convert.ToInt32(mes));

            case "Nome":
                return BookBD.getLivroNome(mes);

            case "Autor":
                return BookBD.getLivrosAutor(mes);

            case "Genre":
                return BookBD.getLivrosGenre(mes);
        }
    return null;
    }

    public IUser? buscaUser (string cod) {
        return UserBD.buscaUser(cod);
    }

    public void changeConfig(string configuration, int value) {
        switch (configuration) {
            case "maxAdvert":
                config.setMaxAdvert(value);
                break;
            case "maxBook":
                config.setMaxBook(value);
                break;
        }
    }

    public int chainCheck (Book livro, IUser user) {
        approvingChain = new availableCheck();
        approvingChain.setNext(new advertCheck(config.getMaxAdvert())).setNext(new maxBookCheck(config.getMaxBook()));
        return approvingChain.handle(livro, user);
    }

    public int emprestaLivro (int codLivro, string codUser) {
        List<Book> aux = buscaLivro("Código", codLivro.ToString());
        if (aux.Count == 0) return -1;
        Book livro = aux[0];
        IUser user;
        if (buscaUser(codUser) == null) return -2;
        user = buscaUser(codUser);
        int check = chainCheck(livro, user);
        // como não há livros para emprestar, user reserva o livro
        if (check == 1){ 
            livro.getReservas().Add(user);
            notifyUser(user,"Livro indisponível, usuário adicionado à lista de reservas!");
        } 
        if (check != 0) return check;

        livro.empresta();
        user.empresta(new BookReg(livro));
        Console.WriteLine("Livro emprestado.");
        return 0;
    }

    public int devolveLivro (int codLivro, string codUser) {
        List<Book> aux = buscaLivro("Código", codLivro.ToString());
        if (aux.Count == 0) return -1;
        Book livro = aux[0];
        IUser user;
        if (buscaUser(codUser) == null) return -2;
        user = buscaUser(codUser);
        
        int result = user.devolve(livro);
        if (result == -3) return -3;
        livro.devolve();
        if(livro.getCopEmprestadas() == 1){ // quando devolveu, ficou disponivel uma cópia
            var reservas = livro.getReservas();
            notifyUser(reservas[0],$"{livro.getName} está disponível para empréstimo!");
            reservas.Remove(reservas[0]);
        }
        return 0;
    }

    public void notifyUser (IUser user, string message) {
        user.notify(message);
    }

    public void notifyAllUsers (string message) {
        List<IUser> users = this.UserBD.getUsers();
        foreach (IUser usuario in users) {
            Console.Write($"Nova mensagem para: {usuario.getName()}. ");
            usuario.notify(message);
        }
    }

    public void registraLivro(String nome, List<String> authors){
        BookBD.registraLivro(nome,authors);
        notifyAllUsers("Novo livro disponível: " + nome + " Código do livro: " + BookBD.getLivroNome(nome)[0].getCod());
    }   
}

public class BaseMedClass {
    protected IMediator? mediator;

    public BaseMedClass() {
        this.mediator = null;
    }

    public void setMediator(IMediator mediador) {
        this.mediator = mediador;
    }
}