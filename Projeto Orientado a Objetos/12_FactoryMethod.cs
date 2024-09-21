using System;
using System.Collections.Generic;

public interface Figura {
  public double getArea();
}

public interface Construtor {
  public void construir();
  public Figura getResultado();
}

public class Fachada {
  private static Dictionary<int, Construtor> dico = new Dictionary<int, Construtor>();

  public Fachada() {
    dico.Add(1, new CircConstr());
    dico.Add(2, new QuadrConstr());
    dico.Add(3, new EqTrianConstr());
  }
  
  public static Figura GetFigura(int type) {
    if (!dico.ContainsKey(1)) dico.Add(1, new CircConstr());
    if (!dico.ContainsKey(2)) dico.Add(2, new QuadrConstr());
    if (!dico.ContainsKey(3)) dico.Add(3, new EqTrianConstr());
    Construtor c = dico[type];
    c.construir();
    return c.getResultado();
  }
}

public class CircConstr : Construtor {
  private Circulo c;

  public void construir() {
    this.c = new Circulo();
  }
  public Figura getResultado() {
    return this.c;
  }
}

public class QuadrConstr : Construtor {
  private Quadrado q;

  public void construir() {
    this.q = new Quadrado();
  }
  public Figura getResultado() {
    return this.q;
  }
}

public class EqTrianConstr : Construtor {
  private TrEqui t;

  public void construir() {
    this.t = new TrEqui();
  }
  public Figura getResultado() {
    return this.t;
  }
}

public class Circulo : Figura {
  private double r = 0;
  
  public double getArea() {
    return r*3.14;
  }
  public void setSize(double sz) {
    this.r = sz;
  }
}
public class Quadrado : Figura {
  private double r = 0;

  public double getArea() {
    return r*r;
  }
  public void setSize(double sz) {
    this.r = sz;
  }
}
public class TrEqui : Figura {
  private double r = 0;

  public double getArea() {
    return ((r*r)*Math.Sqrt(3))/4;
  }
  public void setSize(double sz) {
    this.r = sz;
  }
}


class Program {
  public static void Main () {
    Circulo c = (Circulo) Fachada.GetFigura(1);
    Circulo c2 = (Circulo) Fachada.GetFigura(1);
    Quadrado q = (Quadrado) Fachada.GetFigura(2);
    TrEqui t = (TrEqui) Fachada.GetFigura(3);
  }
}