using System;

public class Light {
  public readonly State Green = new GreenLight();
  public readonly State Yellow = new YellowLight();
  public readonly State Red = new RedLight();

  private State estado;

  public void setEstado(State st) {
    this.estado = st;
  }

  public void seeLight() {
    if (this.estado == null) this.estado = new NullLight();
    this.estado.showLight();
  }
}

public interface State {
  public void showLight();
}

public class GreenLight : State {
  public void showLight() {
    Console.WriteLine("Green Light");
  }
}

public class YellowLight : State {
  public void showLight() {
    Console.WriteLine("Yellow Light");
  }
}

public class RedLight : State {
  public void showLight() {
    Console.WriteLine("Red Light");
  }
}

public class NullLight : State {
  public void showLight() {}
}

class Program {
  public static void Main () {
    Light semaforo = new Light();
    semaforo.seeLight();
    semaforo.setEstado(semaforo.Green);
    semaforo.seeLight();
    semaforo.setEstado(semaforo.Red);
    semaforo.seeLight();
  }
}