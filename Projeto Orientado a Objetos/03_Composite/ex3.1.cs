//Thiago Corso Capuano  163996
//Padrão: Composite

using System;
using System.Collections.Generic;

public class Congresso {
  private List<Participante> listParticipantes = new List<Participante>();
  private int assentos = 500;
  private int free = 1;

  public int getParticipantes () {
    int count = 0;
    foreach (Participante p in listParticipantes) {
      count += p.getMembros();
    }
    return count;
  }
  public int getAssentos () {
    return assentos;
  }
  public void setAssentos (int ass) {
    this.assentos = ass;
  }
  public void addParticipante (Participante participante) {
    if (this.getParticipantes() < this.getAssentos()) {
      setIndAssento(participante);
      this.listParticipantes.Add(participante);
    }
    else Console.WriteLine("Congresso cheio!");
  }
  public void removeParticipante (Participante participante) {
    if (this.listParticipantes.IndexOf(participante) != -1) {
      this.listParticipantes.Remove(participante);
      return;
    }
    foreach (Participante p in listParticipantes) {
      p.removeMembro(participante);
    }
  }
  private void setIndAssento (Participante participante) {
    if (!participante.isComposite()) {
      participante.setAssento(free);
      free++;
      return;
    }
  }
}

public abstract class Participante {
  public abstract int getMembros ();
  public abstract void addMembro (Participante participante);
  public abstract void removeMembro(Participante participante);
  public abstract bool isComposite();
  public abstract void setAssento(int num);
}

public class Individuo : Participante {
  private int assento;
  
  public override int getMembros() {
    return 1;
  }
  public override void addMembro (Participante participante) {}
  public override void removeMembro (Participante participante) {}
  public override bool isComposite() {return false;}
  public override void setAssento(int num) {
    this.assento = num;
  }
}

public class Grupo : Participante {
  private List<Participante> listParticipante = new List<Participante>();

  public override int getMembros() {
    int count = 0;
    foreach(Participante p in listParticipante) {
      count += p.getMembros();
    }
    return count;
  }
  public override void addMembro (Participante participante) {
    this.listParticipante.Add(participante);
  }
  public override void removeMembro (Participante participante) {
    if (this.listParticipante.IndexOf(participante) != -1) {
      this.listParticipante.Remove(participante);
      return;
    }
    foreach (Participante p in listParticipante) {
      p.removeMembro(participante);
    }
  }
  public override bool isComposite () {return true;}
  public override void setAssento (int num) {}
}

class Program1 {
  public static void Main () {
    Congresso congresso = new Congresso();
    Individuo Thiago = new Individuo();
    Individuo Fabio = new Individuo();
    Grupo Unifesp = new Grupo();
    Individuo Sergio = new Individuo();
    Individuo Carla = new Individuo();
    Unifesp.addMembro(Thiago);
    Unifesp.addMembro(Fabio);
    congresso.addParticipante(Unifesp);
    congresso.addParticipante(Sergio);
    congresso.addParticipante(Carla);
    int count = congresso.getParticipantes();
    Console.WriteLine(count);
  }
}