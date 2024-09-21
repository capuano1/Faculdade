using System;

public class FakeBD {
  private string nomePessoa = "Thiago";
  private string identidadePessoa = "163996";
  private string nomeEmpresa = "Tenbu";

  public string getNomePessoa() { return this.nomePessoa; }
  public string getIdentidadePessoa() { return this.identidadePessoa; }
  public string getNomeEmpresa() { return this.nomeEmpresa; }
}

public interface Cliente {
  public void setNome(string n);
  public void print();
}

public class Pessoa : Cliente {
  private string nome;
  private string identidade;

  public void setNome(string n) {
    this.nome = n;
  }
  public void setIdentidade(string i) {
    this.identidade = i;
  }
  public void print() {
    Console.WriteLine("Nome: " + this.nome);
    Console.WriteLine("Identidade: " + this.identidade);
  }
}

public class Empresa : Cliente {
  private string nomeEmpresa;
  private Pessoa responsible;

  public void setNome(string n) {
    this.nomeEmpresa = n;
  }
  public void setPessoa(Pessoa p) {
    this.responsible = p;
  }
  public void print() {
    Console.WriteLine("Nome da Empresa: " + this.nomeEmpresa);
    Console.WriteLine("Dados do Responsável:");
    responsible.print();
  }
}

public interface IBuilder {
  public int Verifica();
  public void criaNecessidade();
  public void build();
  public Cliente getResultado();
}

public class PessoaBuilder : IBuilder {
  private FakeBD bd = new FakeBD();
  private Pessoa result = new Pessoa();
  
  public int Verifica() {
    if (bd.getNomePessoa() != null && bd.getIdentidadePessoa() != null) return 1;
    return 0;
  }

  public void criaNecessidade() {}

  public void build() {
    result.setNome(bd.getNomePessoa());
    result.setIdentidade(bd.getIdentidadePessoa());
  }

  public Cliente getResultado() {
    return this.result;
  }
  
}

public class EmpresaBuilder : IBuilder {
  private FakeBD bd = new FakeBD();
  private Empresa result = new Empresa();
  private PessoaBuilder respons = new PessoaBuilder();

  public int Verifica() {
    if (bd.getNomePessoa() != null && bd.getIdentidadePessoa() != null && bd.getNomeEmpresa() != null) return 1;
    return 0;
  }

  public void criaNecessidade() {
    if (respons.Verifica() == 1) {
      respons.build();
    }
  }

  public void build() {
    result.setNome(bd.getNomeEmpresa());
    result.setPessoa((Pessoa)respons.getResultado());
  }

  public Cliente getResultado() {
    return this.result;
  }
}

public class Diretor {
  private PessoaBuilder pessoaBuild;
  private EmpresaBuilder empresaBuild;

  public void setPessoaBuild (PessoaBuilder p) {
    this.pessoaBuild = p;
  }
  public void setEmpresaBuild (EmpresaBuilder e) {
    this.empresaBuild = e;
  }

  public void buildPessoa() {
    if (pessoaBuild.Verifica() == 1) {
      pessoaBuild.build();
    }
  }

  public void buildEmpresa() {
    if (empresaBuild.Verifica() == 1) {
      empresaBuild.criaNecessidade();
      empresaBuild.build();
    }
  }
  
}

class Program {
  public static void Main () {
    Diretor d = new Diretor();
    PessoaBuilder p = new PessoaBuilder();
    EmpresaBuilder e = new EmpresaBuilder();
    d.setEmpresaBuild(e);
    d.setPessoaBuild(p);
    d.buildEmpresa();
    d.buildPessoa();
    Pessoa pessoa = (Pessoa)p.getResultado();
    Empresa empresa = (Empresa)e.getResultado();
    Console.WriteLine ("Cliente Pessoa:");
    pessoa.print();
    Console.WriteLine ("Cliente Empresa:");
    empresa.print();
  }
}