//Thiago Corso Capuano  163996

using System;
using System.Collections.Generic;

public interface Observer {
  public void update(ObserverManager mng);
}

public class Researcher : Observer {
  private double temp, pressure, pH;
  private Mediator mediator;
  
  public Researcher () {
    this.mediator = Mediator.instanciaMediator();
    mediator.addResearcher(this);
  }
  
  public void update(ObserverManager mng) {
    PCD pcd = (PCD) mng;
    this.temp = pcd.getTemp();
    this.pressure = pcd.getPressure();
    this.pH = pcd.getpH();
  }
  
  public void printData() {
    Console.WriteLine("Temperatura: " + this.temp);
    Console.WriteLine("Pressão: " + this.pressure);
    Console.WriteLine("pH: " + this.pH);
  }

  public void printWarningMessage (String message) {
    Console.WriteLine(message);
  }
}

public class ObserverManager {
  List<Observer> observers = new List<Observer>();

  public void add (Observer obs) {
    this.observers.Add(obs);
    notify();
  }

  public void remove (Observer obs) {
    this.observers.Remove(obs);
  }

  public void notify () {
    foreach (Observer obs in this.observers) {
      obs.update(this);
    }
  }
}

public class PCD : ObserverManager {
  private double temp, pressure, pH;
  private Mediator mediator;
  private String name;

  public PCD (String pcdName) {
    this.mediator = Mediator.instanciaMediator();
    this.name = pcdName;
  }

  public double getTemp() {
    return this.temp;
  }
  public double getPressure() {
    return this.pressure;
  }
  public double getpH() {
    return this.pH;
  }
  public void setTemp(double t) {
    if (Math.Abs(this.temp - t) > 10) {
      mediator.warningMessage("Alerta de Temperatura no sensor "+this.name+"!");
    }
    this.temp = t;
    notify();
  }
  public void setPressure(double p) {
    if (Math.Abs(this.pressure - p) > this.pressure*1.1) {
      mediator.warningMessage("Alerta de Pressão no sensor "+this.name+"!");
    }
    this.pressure = p;
    notify();
  }
  public void setpH(double pH) {
    if (Math.Abs(this.pH - pH) > 2) {
      mediator.warningMessage("Alerta de pH no sensor "+this.name+"!");
    }
    this.pH = pH;
    notify();
  }
}

//Fiz o mediator ser um Singleton para facilitar as coisas nesta implementação
public class Mediator {
  private List<Researcher> researcherList;
  private static Mediator mediator;
  private Mediator () {
    this.researcherList = new List<Researcher>();
  }

  public void addResearcher (Researcher res) {
    researcherList.Add(res);
  }

  public void warningMessage (String mes) {
    foreach (Researcher res in researcherList) {
      res.printWarningMessage(mes);
    }
  }
  
  public static Mediator instanciaMediator () {
    if (mediator == null) {
      mediator = new Mediator();
    }
    return mediator;
  }
}

class Program {
  public static void Main () {
    PCD Amazonia = new PCD("Amazonia");
    Amazonia.setPressure(1);
    Amazonia.setTemp(130.5);
    Amazonia.setpH(3);
    Researcher Fagundes = new Researcher();
    Researcher Thiago = new Researcher();
    Amazonia.add(Fagundes);
    Fagundes.printData();
    Amazonia.setTemp(150.3);
    Fagundes.printData();
  }
}