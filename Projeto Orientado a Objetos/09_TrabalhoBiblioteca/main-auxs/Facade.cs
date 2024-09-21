using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

public class Facade {
    
    private UBD userBD;
    private BBD bookBD;
    private BuscaLivro instanciaBuscaLivro() {
        BuscaLivro busc = new BuscaLivro();
        ConcMediator med = new ConcMediator(bookBD, null, busc);
        busc.setMediator(med);
        return busc;
    }

    private BuscaUser instanciaBuscaUser() {
        BuscaUser busc = new BuscaUser();
        ConcMediator med = new ConcMediator(null, userBD, busc);
        busc.setMediator(med);
        return busc;
    }

    private EmprestaLivro instanciaEmprestaLivro() {
        EmprestaLivro emp = new EmprestaLivro();
        ConcMediator med = new ConcMediator(bookBD, userBD, emp);
        emp.setMediator(med);
        return emp;
    }

    private DevolveLivro instanciaDevolveLivro() {
        DevolveLivro dev = new DevolveLivro();
        ConcMediator med = new ConcMediator(bookBD, userBD, dev);
        dev.setMediator(med);
        return dev;
    }

    public Facade() {
        this.userBD = UserBD_static.iniciaBD();
        this.bookBD = BookBD_static.iniciaBD();
    }
    public void registrarAluno(string name, string cod, int idade) {
        userBD.registraUsuario(new userEstudante(name, cod, idade));
    }
    public void registrarFuncionario(string name, string cod, int idade) {
        userBD.registraUsuario(new userFuncionario(name, cod, idade));
    }
    public void registrarProfessor(string name, string cod, int idade) {
        userBD.registraUsuario(new userProfessor(name, cod, idade));
    }
    public void buscarUser(string codigo) {
        BuscaUser buscar = instanciaBuscaUser();
        buscar.buscarUser(codigo);
    }
    public bool codExiste(string codigo) {
        if (userBD.buscaUser(codigo) != null) return true;
        return false;
    }
    public void removerUser(string codigo){
        var user = userBD.buscaUser(codigo);
        if(user != null){
            userBD.removeUsuario( user );
        }
        else{
            Console.WriteLine("Usuário não encontrado.\n");
        }
    }

    public void buscaLivroCod (int cod) {
        BuscaLivro buscar = instanciaBuscaLivro();
        buscar.buscaLivroCod(cod);
    }

    public void buscaLivroNome (string name) {
        BuscaLivro buscar = instanciaBuscaLivro();
        buscar.buscaLivroNome(name);
    }

    public void buscaLivroAuthor (string author) {
        BuscaLivro buscar = instanciaBuscaLivro();
        buscar.buscaLivroAuthor(author);
    }

    public void buscaLivroGenre (string genre) {
        BuscaLivro buscar = instanciaBuscaLivro();
        buscar.buscaLivroGenre(genre);
    }

    public void registraLivro(String nome, List<String> authors){
        ConcMediator med = new ConcMediator(this.bookBD, this.userBD, null);
        med.registraLivro(nome,authors);
        Console.WriteLine("\nLivro adicionado com sucesso!");
    }

    public void removeLivro(int codigo){
        bookBD.eliminaLivro(codigo);
    }
    public void emprestaLivro (int codLivro, string codUser) {
        EmprestaLivro emp = instanciaEmprestaLivro();
        emp.emprestarLivro(codLivro, codUser);
    }

    public void devolveLivro (int codLivro, string codUser) {
        DevolveLivro dev = instanciaDevolveLivro();
        dev.devolverLivro(codLivro, codUser);
    }

    public void adicionaGenero(int codigo, String genero){
        Book livro = bookBD.getLivroCod(codigo)[0];
        livro.addGenre(genero);
    }
    public void removeGenero(int codigo, String genero){
        Book livro = bookBD.getLivroCod(codigo)[0];
        livro.removeGenre(genero);
    }
    public void adicionaSubGenero(int codigo, String genero,String subgenero){
        Book livro = bookBD.getLivroCod(codigo)[0];
        livro.addSubgenre(genero,subgenero);
    }
    public void removeSubGenero(int codigo, String genero,String subgenero){
        Book livro = bookBD.getLivroCod(codigo)[0];
        livro.removeSubgenre(genero,subgenero);
    }

    public void configMaxAdvert (int value) {
        ConcMediator mediator = new ConcMediator(null, null, null);
        mediator.changeConfig("maxAdvert", value);
    }

    public void configMaxBook (int value) {
        ConcMediator mediator = new ConcMediator(null, null, null);
        mediator.changeConfig("maxBook", value);
    }

    public void mudaNumeroCopias(int codLivro, int copias){
        var livro = bookBD.getLivroCod(codLivro);
        livro[0].setCopOwned(copias);
    }

    public void aplicarAdvert(string codUser){
        var usuario = userBD.buscaUser(codUser);
        usuario.giveAdvert();
    }

}