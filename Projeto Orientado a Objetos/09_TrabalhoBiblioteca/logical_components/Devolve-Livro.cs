using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class DevolveLivro : BaseMedClass {

    public void devolverLivro(int codLivro, string codUser) {
        int res = this.mediator.devolveLivro(codLivro, codUser);
        switch (res) {
            case -3:
                Console.WriteLine("Registro de empréstimo não encontrado!");
                break;
            case -2:
                Console.WriteLine("Usuário não encontrado!");
                break;
            case -1:
                Console.WriteLine("Livro não encontrado!");
                break;
            case 0:
                Console.WriteLine("Sucesso!");
                break;
        }
    }









}