using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public abstract class IUser
{
    private string name;
    private string cod;
    private int idade;
    private int numLivrosEmprestados;
    private int advert;
    private string tipoUser;
    private List<BookReg> history;

    public IUser (string nome, string codg, int age, string tipo) {
        this.name = nome;
        this.cod = codg;
        this.idade = age;
        this.advert = 0;
        this.numLivrosEmprestados = 0;
        this.tipoUser = tipo;
        this.history = new List<BookReg>();
    }

    public string getName() { return this.name; }
    public string getCod() { return this.cod; }
    public int getIdade() { return this.idade; }
    public void birthday() { this.idade++; }
    public int getAdvert() { return this.advert; }
    public void giveAdvert() { this.advert += 1; }
    public int getNumLivros() { return this.numLivrosEmprestados; }
    public string getTipoUser() { return this.tipoUser; }
    public List<BookReg> getHistory() { return this.history; }
    public void empresta(BookReg reg) { 
        this.history.Add(reg);
        this.numLivrosEmprestados++;
    }
    public int devolve(Book livro) { 
        BookReg? aux = this.history.Find(x => x.getLivro() == livro && x.getDevolvido() == null);
        if (aux != null) {
            aux.setDevolvido();
            this.numLivrosEmprestados--;
            return 0;
        }
        return -3;
    }
    public void notify(string message) {
        Console.WriteLine(message);
    }

}
