using System;
using System.Collections.Generic;

//Thiago Corso Capuano - 163996

public class Carrinho {
  
  private List<Produto> ListaCarrinho = new List<Produto>();
  
  public void Adicionar(Produto p) {
    this.ListaCarrinho.Add(p);
  }
  public double getTotal() {
    double total = 0;
    foreach(Produto produto in this.ListaCarrinho) {
      total += produto.getPreco();
    }
    return total;
  }
}

public class Cliente {

  private String nome;
  private int id;
  private Carrinho carrinho;

  public Cliente (String name, int ClientId) {
    nome = name;
    id = ClientId;
  }
  public void adicionarCarrinho(Carrinho c) {
    this.carrinho = c;
  }
  public Carrinho getCarrinho() {
    return this.carrinho;
  }
  public String getName() {
    return this.nome;
  }
  public int getID() {
    return this.id;
  }
}

public class Produto {

  private String nome;
  private int id;
  private double preco;

  public Produto (String name, int id, double preco) {
    this.nome = name;
    this.id = id;
    this.preco = preco;
  }
  public double getPreco() {
    return preco;
  }
  public String getName() {
    return nome;
  }
  public int getID() {
    return this.id;
  }
}

public class BancoDeDados {
  private List<Cliente> ClientList = new List<Cliente>();
  private List<Produto> ProductList = new List<Produto>();
  
  public Cliente selectCliente(int id) {
    return this.ClientList.Find(c => c.getID() == id);
  }
  public Produto selectProduto(int id) {
    return this.ProductList.Find(p => p.getID() == id);
  }
  //Para fins de teste:
  public void addProduto(String nome, int id, double preco) {
    Produto produto = new Produto(nome, id, preco);
    this.ProductList.Add(produto);
  }
  public void processarPagamento() {
    Console.WriteLine("Pagamento sendo processado");
  }
}

public class Facade {
  BancoDeDados banco = new BancoDeDados();
  public void begin() {
    this.banco.addProduto("Arroz", 123, 10);
    this.banco.addProduto("Feijão", 456, 15);
  }
  public void registrar(String nome, int id) {
    Cliente c = new Cliente(nome, id);
    Carrinho car = new Carrinho();
    c.adicionarCarrinho(car);
    Console.WriteLine("O cliente " + c.getName() + " foi criado com ID " + c.getID() + "\n");
  }
  public void comprar(int prodID, int clienteID) {
    Cliente c = banco.selectCliente(clienteID);
    Produto p = banco.selectProduto(prodID);
    c.getCarrinho().Adicionar(p);
    Console.WriteLine("Produto " + p.getName() + " adicionado ao carrinho do cliente " + c.getName() + "\n");
  }
  public void fecharCompra(int clienteID) {
    Cliente c = banco.selectCliente(clienteID);
    double valor = c.getCarrinho().getTotal();
    Console.WriteLine("Valor final: " + valor + "\n");
    banco.processarPagamento();
  }
}

class Program {
  public static void Main () {
    Facade f = new Facade();

    f.begin(); //Para adicionar produtos teste
    
    f.registrar("Thiago", 123);
    f.registrar("Fábio", 456);
    f.registrar("Otávio", 789);
    f.comprar(123, 123);
    f.comprar(456, 456);
    f.comprar(123, 789);
    f.comprar(456, 789);
    f.fecharCompra(123);
    f.fecharCompra(456);
    f.fecharCompra(789);
    
  }
}