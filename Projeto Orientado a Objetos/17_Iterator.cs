using System;
using System.Collections.Generic;

public class Figura {
  private string figura;

  public Figura (string fig) {
    this.figura = fig;
  }

  public void printFig() {
    Console.WriteLine(this.figura);
  }
}

public interface FigIterator {
  public void next();
  public bool hasNext();
}

public class ConcFigIterator : FigIterator {
  private FigAggregate aggregate;
  private int iteratorStatus;

  public ConcFigIterator(FigAggregate fig) {
    this.aggregate = fig;
    this.iteratorStatus = -1;
  }
  
  public void next() {
    this.iteratorStatus++;
    if (this.aggregate.getSize() == 0) {
      Console.WriteLine("Lista Vazia");
    }
    if (!hasNext()) {
      this.iteratorStatus = 0;
    }
    this.aggregate.getFigura(this.iteratorStatus).printFig();
  }

  public bool hasNext() {
    if (this.iteratorStatus <= aggregate.getSize() - 1) {
      return true;
    }
    else {
      return false;
    }
  }
}

public class FigAggregate {
  private List<Figura> figList;

  public FigAggregate () {
  this.figList = new List<Figura>();
  }

  public void Add(Figura fig) {
    this.figList.Add(fig);
  }
  public void Remove(Figura fig) {
    this.figList.Remove(fig);
  }
  public Figura getFigura (int index) {
    return this.figList[index];
  }
  public int getSize() {
    return this.figList.Count;
  }

  public ConcFigIterator getIterator() {
    ConcFigIterator fig = new ConcFigIterator(this);
    return fig;
  }
}

class Program2 {
  public static void Main () {
    FigAggregate lista = new FigAggregate();
    lista.Add(new Figura("Círculo"));
    lista.Add(new Figura("Quadrado"));
    lista.Add(new Figura("Triângulo"));
    ConcFigIterator iterator = lista.getIterator();
    iterator.next();
    iterator.next();
    iterator.next();
    iterator.next();
  }
}