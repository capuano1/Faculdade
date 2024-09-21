using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class EmprestaLivro : BaseMedClass {

    public void emprestarLivro(int codLivro, string codUser) {
        int res = this.mediator.emprestaLivro(codLivro, codUser);
        switch (res) {
            case -2:
                Console.WriteLine("Usuário não encontrado!");
                break;
            case -1:
                Console.WriteLine("Livro não encontrado!");
                break;
            case 0:
                Console.WriteLine("Sucesso!");
                break;
            case 2:
                Console.WriteLine("Usuário com limite de advertências!");
                break;
            case 3:
                Console.WriteLine("Usuário com limite de livros emprestados!");
                break;
        }
    }







}