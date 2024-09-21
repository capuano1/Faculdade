//Thiago Corso Capuano  163996

using System;
using System.Collections.Generic;

public abstract class Publicacao {
  public abstract int NumPubs();
  public abstract int NumArts();
  public abstract void toString();
  public abstract bool IsComposite();
  public abstract void RemovePub(Publicacao Pub);
  public abstract void AddPub(Publicacao Pub);
}

public class Artigo : Publicacao {
  private String Article;
  private String Author;

  public Artigo (String art, string author) {
    this.Article = art;
    this.Author = author;
  }
  
  public override int NumPubs() {
    return 0;
  }
  public override int NumArts() {
    return 1;
  }
  public override void toString() {
    Console.WriteLine("Artigo: "+this.Article+" | Autor: "+this.Author);
  }
  public override bool IsComposite() {
    return false;
  }
  public override void RemovePub (Publicacao pub) {}
  public override void AddPub (Publicacao pub) {}
}

public class Jornal : Publicacao {
  private String Name;
  private List<Publicacao> Artigos = new List<Publicacao>();

  public Jornal (String name) {
    this.Name = name;
  }
  
  public override int NumPubs() {
    int count = 1;
    foreach(Publicacao pub in Artigos) {
      count += pub.NumPubs();
    }
    return count;
  }
  public override int NumArts() {
    int count = 0;
    foreach(Publicacao art in Artigos) {
      count += art.NumArts();
    }
    return count;
  }
  public override void toString() {
    Console.WriteLine("Jornal: "+Name);
    foreach(Publicacao pub in Artigos) {
      pub.toString();
    }
  }
  public override bool IsComposite() {
    return true;
  }
  public override void AddPub(Publicacao pub) {
    this.Artigos.Add(pub);
  }
  public override void RemovePub(Publicacao pub) {
    if (this.Artigos.IndexOf(pub) != -1) {
      this.Artigos.Remove(pub);
      return;
    }
    foreach (Publicacao p in Artigos) {
      p.RemovePub(pub);
    }
  }
}

public class Caderno : Publicacao {
  private String Name;
  private List<Publicacao> Artigos = new List<Publicacao>();

  public Caderno (String name) {
    this.Name = name;
  }

  public override int NumPubs() {
    int count = 1;
    foreach(Publicacao pub in Artigos) {
      count += pub.NumPubs();
    }
    return count;
  }
  public override int NumArts() {
    int count = 0;
    foreach(Publicacao art in Artigos) {
      count += art.NumArts();
    }
    return count;
  }
  public override void toString() {
    Console.WriteLine("Caderno: "+Name);
    foreach(Publicacao pub in Artigos) {
      pub.toString();
    }
  }
  public override bool IsComposite() {
    return true;
  }
  public override void AddPub(Publicacao pub) {
    this.Artigos.Add(pub);
  }
  public override void RemovePub(Publicacao pub) {
    if (this.Artigos.IndexOf(pub) != -1) {
      this.Artigos.Remove(pub);
      return;
    }
    foreach (Publicacao p in Artigos) {
      p.RemovePub(pub);
    }
  }
}

public class Revista : Publicacao {
  private String Name;
  private List<Publicacao> Artigos = new List<Publicacao>();

  public Revista (String name) {
    this.Name = name;
  }

  public override int NumPubs() {
    int count = 1;
    foreach(Publicacao pub in Artigos) {
      count += pub.NumPubs();
    }
    return count;
  }
  public override int NumArts() {
    int count = 0;
    foreach(Publicacao art in Artigos) {
      count += art.NumArts();
    }
    return count;
  }
  public override void toString() {
    Console.WriteLine("Revista: "+Name);
    foreach(Publicacao pub in Artigos) {
      pub.toString();
    }
  }
  public override bool IsComposite() {
    return true;
  }
  public override void AddPub(Publicacao pub) {
    this.Artigos.Add(pub);
  }
  public override void RemovePub(Publicacao pub) {
    if (this.Artigos.IndexOf(pub) != -1) {
      this.Artigos.Remove(pub);
      return;
    }
    foreach (Publicacao p in Artigos) {
      p.RemovePub(pub);
    }
  }
}

public class Colecao {
  private List<Publicacao> colecao = new List<Publicacao>();

  public int GetPubs() {
    int count = 0;
    foreach (Publicacao pub in colecao) {
      count += pub.NumPubs();
    }
    return count;
  }
  public int GetArticles() {
    int count = 0;
    foreach (Publicacao art in colecao) {
      count += art.NumArts();
    }
    return count;
  }
  public void AddPub(Publicacao pub) {
    colecao.Add(pub);
  }
  public void RemovePub(Publicacao pub) {
    if (this.colecao.IndexOf(pub) != -1) {
      this.colecao.Remove(pub);
      return;
    }
    foreach (Publicacao pubs in colecao) {
      pubs.RemovePub(pub);
    }
  }
  public void printColecao() {
    foreach (Publicacao p in colecao) {
      p.toString();
    }
  }
}

class Program {
  public static void Main() {
    Colecao inverno = new Colecao();
    Artigo art1 = new Artigo("Art1", "Author1");
    Artigo art2 = new Artigo("Art2", "Author2");
    Artigo art3 = new Artigo("Art3", "Author3");
    Artigo art4 = new Artigo("Art4", "Author4");
    Artigo art5 = new Artigo("Art5", "Author5");
    Artigo art6 = new Artigo("Art6", "Author6");
    Artigo art7 = new Artigo("Art7", "Author7");
    Artigo art8 = new Artigo("Art8", "Author8");
    Jornal j1 = new Jornal("Jor1");
    Caderno c1 = new Caderno("C1");
    Revista r1 = new Revista("R1");
    inverno.AddPub(art1);
    inverno.AddPub(art2);
    j1.AddPub(art3);
    j1.AddPub(art4);
    c1.AddPub(art5);
    c1.AddPub(art6);
    r1.AddPub(art7);
    r1.AddPub(art8);
    c1.AddPub(r1);
    j1.AddPub(c1);
    inverno.AddPub(j1);
    Console.WriteLine("Número de Publicações: "+inverno.GetPubs());
    Console.WriteLine("Número de Artigos: "+inverno.GetArticles());
    inverno.printColecao();
  }
}