using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class BuscaLivro : BaseMedClass {

    private void imprimeLivros (List<Book> list) {
        if (list == null || list.Count == 0) Console.WriteLine("Nenhum livro encontrado");
        foreach (Book liv in list) {
            Console.WriteLine("Nome: " + liv.getName());
            Console.WriteLine("Código: " + liv.getCod());
            Console.WriteLine("Autores: ");
            foreach (string aut in liv.getAuthors()) Console.Write(aut + " | ");
            Console.WriteLine("\nGêneros: ");
            HashSet<string>[] aux = liv.getSubgenres();
            int i = 0;
            foreach (string gen in liv.getGenres()){
                Console.Write(gen + " - ");
                foreach(string subgen in aux[i]) {
                    Console.Write(subgen + " | ");
                }
                i++;
                Console.WriteLine();
            }
            Console.WriteLine("Cópias no acervo | Cópias disponíveis: " + liv.getCopOwned() + " | " + liv.getCopAvailable());
            Console.WriteLine();
        }
    }

    public void buscaLivroCod (int cod) {
        imprimeLivros(this.mediator.buscaLivro("Código", cod.ToString()));
    }

    public void buscaLivroNome (string name) {
        imprimeLivros(this.mediator.buscaLivro("Nome", name));
    }

    public void buscaLivroAuthor (string author) {
        imprimeLivros(this.mediator.buscaLivro("Autor", author));
    }

    public void buscaLivroGenre (string genre) {
        imprimeLivros(this.mediator.buscaLivro("Genre", genre));
    }

}