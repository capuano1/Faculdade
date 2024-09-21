using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

public class BookBD_static : BaseMedClass, BBD
{
    
    private static BookBD_static? bookBD;
    private static int maiorCod;
    private List<Book> BookList;
    
    private BookBD_static() {
        this.BookList = new List<Book>();
        maiorCod = 0;
        this.setMediator(new ConcMediator(this, null, null));
    }

    private void incrementaMaiorCod() { maiorCod++; }
    private Book? getLivro(int cod) { return this.BookList.Find(liv => liv.getCod() == cod);}
    
    public static BookBD_static iniciaBD() {
        if (bookBD == null) bookBD = new BookBD_static();
        return bookBD;
    }
    
    public void copiaPerdidaLivro(int cod, int copias) {
        Book? aux = getLivro(cod);
        if (aux != null) aux.setCopOwned(aux.getCopOwned() - copias);
    }

    public void devolve(int cod) {
        Book? aux = getLivro(cod);
        if (aux != null) aux.devolve();
    }

    public void eliminaLivro(int cod) {
        Book? aux = getLivro(cod);
        if (aux != null) this.BookList.Remove(aux);
    }

    public void empresta(int cod) {
        Book? aux = getLivro(cod);
        if (aux != null) aux.empresta();
    }

    public List<Book> getLivroNome(string name) {
        return this.BookList.FindAll(liv => liv.getName() == name);
    }

    public List<Book> getLivroCod(int cod) {
        List<Book> aux = new List<Book>();
        Book? aux2 = BookList.Find(liv => liv.getCod() == cod);
        if (aux2 != null) aux.Add(aux2);
        return aux;
    }

    public List<Book> getLivrosAutor(string author) {
        return this.BookList.FindAll(liv => liv.getAuthors().Contains(author));
    }

    public List<Book> getLivrosGenre(string genre) {
        return this.BookList.FindAll(liv => liv.getGenres().Contains(genre));
    }

    public void novaCopiaLivro(int cod, int copias) {
        Book? aux = getLivro(cod);
        if (aux != null) aux.setCopOwned(aux.getCopOwned() + copias);
    }

    public void registraLivro(string bname, List<string> authorl) {
        incrementaMaiorCod();
        Book aux = new Book(bname, authorl, maiorCod);
        this.BookList.Add(aux);
        //this.mediator.notifyAllUsers("Novo livro disponível: " + bname);
    }

}