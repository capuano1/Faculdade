using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

public interface BBD {

    public void registraLivro(string bname, List<string> authorl);
    public void eliminaLivro(int cod);
    public void novaCopiaLivro(int cod, int copias);
    public void copiaPerdidaLivro(int cod, int copias);
    public void empresta(int cod);
    public void devolve(int cod);
    public List<Book> getLivroNome(string name);
    public List<Book> getLivroCod(int cod);
    public List<Book> getLivrosAutor(string author);
    public List<Book> getLivrosGenre(string genre);

}