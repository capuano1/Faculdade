//Thiago Corso Capuano  163996

using System;

public interface Processador {
  public void stringProcess (string str);
  public void setNext(Processador proc);
}

public class ProcessadorSpace : Processador {
  private Processador next;
  
  public void stringProcess (string str) {
    int result = str.Length - str.Replace(" ", string.Empty).Length;
    Console.WriteLine("Número de espaços: "+result);
    if (next != null) next.stringProcess(str);
  }
  public void setNext (Processador proc) {
    if (this.next != null) next.setNext(proc);
    else this.next = proc;
  }
}

public class ProcessadorChara : Processador {
  private Processador next;

  public void stringProcess (string str) {
    int result = str.Length - str.Replace("a", string.Empty).Length;
    Console.WriteLine("Número de caracteres a: "+result);
    if (next != null) next.stringProcess(str);
  }
  public void setNext (Processador proc) {
    if (this.next != null) next.setNext(proc);
    else this.next = proc;
  }
}

public class ProcessadorDots : Processador {
  private Processador next;

  public void stringProcess (string str) {
    int result = str.Length - str.Replace(".", string.Empty).Length;
    Console.WriteLine("Número de pontos: "+result);
    if (next != null) next.stringProcess(str);
  }
  public void setNext (Processador proc) {
    if (this.next != null) next.setNext(proc);
    else this.next = proc;
  }
}

class Program {
  public static void Main () {
    ProcessadorSpace space = new ProcessadorSpace();
    ProcessadorChara chara = new ProcessadorChara();
    ProcessadorDots dots = new ProcessadorDots();
    space.setNext(chara);
    space.setNext(dots);
    
    Console.WriteLine ("Digite uma string: ");
    string str = Console.ReadLine();
    space.stringProcess(str);
  }
}