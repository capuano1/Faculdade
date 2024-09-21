using System;
using System.Collections.Generic;

public interface Operation {
  public void visit(Numbers num);
}

public class Addition : Operation {
  public void visit (Numbers num) {
    int val = num.getVal1() + num.getVal2();
    Console.WriteLine(val);
  }
}

public class Multiply : Operation {
  public void visit (Numbers num) {
    int val = num.getVal1() * num.getVal2();
    Console.WriteLine(val);
  }
}

public interface Data {
  public void setVal1(int n1);
  public void setVal2(int n2);
  public void accept(Operation op);
}

public class Numbers : Data {
  private int val1;
  private int val2;

  public Numbers() {
    this.val1 = 0;
    this.val2 = 0;
  }

  public int getVal1() {return this.val1;}
  public void setVal1(int n1) {this.val1 = n1;}
  public int getVal2() {return this.val2;}
  public void setVal2(int n2) {this.val2 = n2;}
  public void accept(Operation op) {
    op.visit(this);
  }
}

class Program {
  public static void Main () {
    Numbers num = new Numbers();
    Addition add = new Addition();
    Multiply mult = new Multiply();
    num.setVal1(10);
    num.setVal2(30);
    num.accept(add);
    num.accept(mult);
  }
}