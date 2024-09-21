using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class BookReg {

    private Book livro;
    private DateTime emprestado;
    private DateTime? devolvido;

    public BookReg (Book liv) {
        this.livro = liv;
        this.emprestado = DateTime.Now;
    }

    public Book getLivro() {
        return this.livro;
    }

    public DateTime getEmprestado() {
        return this.emprestado;
    }

    public DateTime? getDevolvido() {
        return this.devolvido;
    }

    public void setDevolvido() {
        this.devolvido = DateTime.Now;
    }

}