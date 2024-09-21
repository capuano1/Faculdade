using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class BuscaUser : BaseMedClass {

    public void buscarUser(string cod) {
        IUser? user = this.mediator.buscaUser(cod);
        if (user != null) {
            Console.WriteLine("Nome: " + user.getName());
            Console.WriteLine("Código: " + user.getCod());
            Console.WriteLine("Vínculo: " + user.getTipoUser());
            Console.WriteLine("Idade: " + user.getIdade());
            Console.WriteLine("Advertências: " + user.getAdvert());
            Console.WriteLine("Nº de livros emprestados no momento: " + user.getNumLivros());
            Console.WriteLine("Histórico (Livro | Data Emprestado | Data Devolução): ");
            foreach (BookReg liv in user.getHistory()) {
                if (liv.getDevolvido() != null) {
                    DateTime aux = liv.getDevolvido() ?? DateTime.MinValue;
                    Console.WriteLine(liv.getLivro().getName() + " | " + liv.getEmprestado().ToString("dd/MM/yyyy") + " | " + aux.ToString("dd/MM/yyyy"));
                }
                else Console.WriteLine(liv.getLivro().getName() + " | " + liv.getEmprestado().ToString("dd/MM/yyyy"));
            }
            Console.WriteLine();
        }
        else Console.WriteLine("Usuário não encontrado");
    }
}