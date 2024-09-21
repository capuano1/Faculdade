using System;

public interface Ponto {
  public void desenha();
  public void setX(int x);
  public void setY(int y);
}

public interface Circulo {
  public void desenha();
  public void setRaio(int xp);
  public void setPonto(Ponto pp);
}

public interface Retangulo {
  public void desenha();
  public void setPonto1(Ponto pp1);
  public void setPonto2(Ponto pp2);
}

public interface Triangulo {
  public void desenha();
  public void setPonto1(Ponto pp1);
  public void setPonto2(Ponto pp2);
  public void setPonto3(Ponto pp3);
}

public interface AbsFactory {
  public Ponto criaPont(int x, int y);
  public Circulo criaCirc(int r, int x1, int y1);
  public Retangulo criaRet(int x1, int y1, int x2, int y2);
  public Triangulo criaTrian(int x1, int y1, int x2, int y2, int x3, int y3);
}

public class FactoryA : AbsFactory {
  public Ponto criaPont(int x, int y) {return new PontoConcretoA(x, y);}
  public Circulo criaCirc(int r, int x1, int y1) {return new CirculoConcretoA(r, criaPont(x1, y1));}
  public Retangulo criaRet(int x1, int y1, int x2, int y2) {return new RetanguloConcretoA(criaPont(x1, y1), criaPont(x2, y2));}
  public Triangulo criaTrian(int x1, int y1, int x2, int y2, int x3, int y3) {return new TrianguloConcretoA(criaPont(x1, y1), criaPont(x2, y2), criaPont(x3, y3));}
}

public class PontoConcretoA : Ponto {
  private int x, y;

  public PontoConcretoA (int xp, int yp) {
    this.x = xp;
    this.y = yp;
  }
  
  public void desenha() {
    Console.WriteLine("Ponto em " + this.x + " e " + this.y);
  }
  public void setX(int xp) {this.x = xp;}
  public void setY(int yp) {this.y = yp;}
}

public class CirculoConcretoA : Circulo {
  private int raio;
  private Ponto ponto;

  public CirculoConcretoA (int rp, Ponto pp) {
    this.raio = rp;
    this.ponto = pp;
  }

  public void desenha() {
    Console.WriteLine("Círculo: ");
    Console.WriteLine("Raio = " + this.raio);
    ponto.desenha();
  }
  public void setRaio(int xp) {this.raio = xp;}
  public void setPonto(Ponto pp) {this.ponto = pp;}
}

public class RetanguloConcretoA : Retangulo {
  private Ponto ponto1, ponto2;

  public RetanguloConcretoA (Ponto pp1, Ponto pp2) {
    this.ponto1 = pp1;
    this.ponto2 = pp2;
  }
  
  public void desenha() {
    Console.WriteLine("Retângulo: ");
    ponto1.desenha();
    ponto2.desenha();
  }
  public void setPonto1(Ponto pp1) {this.ponto1 = pp1;}
  public void setPonto2(Ponto pp2) {this.ponto2 = pp2;}
}

public class TrianguloConcretoA : Triangulo {
  private Ponto ponto1, ponto2, ponto3;

  public TrianguloConcretoA (Ponto pp1, Ponto pp2, Ponto pp3) {
    this.ponto1 = pp1;
    this.ponto2 = pp2;
    this.ponto3 = pp3;
  }
  
  public void desenha() {
    Console.WriteLine("Triângulo: ");
    ponto1.desenha();
    ponto2.desenha();
    ponto3.desenha();
  }
  public void setPonto1(Ponto pp1) {this.ponto1 = pp1;}
  public void setPonto2(Ponto pp2) {this.ponto2 = pp2;}
  public void setPonto3(Ponto pp3) {this.ponto3 = pp3;}
}

class Program {
  public static void Main () {
    FactoryA fab = new FactoryA();
    Ponto point = fab.criaPont(3, 3);
    Circulo cir = fab.criaCirc(10, 5, 5);
    Retangulo ret = fab.criaRet(10, 20, 10, 30);
    Triangulo tri = fab.criaTrian(10, 20, 10, 30, 15, 50);
    point.desenha();
    cir.desenha();
    ret.desenha();
    tri.desenha();
  }
}