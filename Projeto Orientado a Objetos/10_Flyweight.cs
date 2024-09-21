using System;
using System.Collections.Generic;

public class FlyweightFactory {
  private List<FlyweightNum> numList;

  public FlyweightFactory () {
    this.numList = new List<FlyweightNum>();
  }

  public FlyweightNum getFlyweight (int n) {
    FlyweightNum aux = this.numList.Find(x => x.getKey() == n);
    if (aux != null) return aux;
    else {
      FlyweightNum fly = new FlyweightNum(n);
      numList.Add(fly);
      return fly;
    }
  }
}

public class FlyweightNum {
  private int key;
  
  public FlyweightNum (int n) {
    this.key = n;
  }

  public int getKey() {
    return this.key;
  }
}

class Program {
  public static void Main () {
    Random rand = new Random();
    FlyweightFactory fly = new FlyweightFactory();
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        Console.Write(fly.getFlyweight(rand.Next(9)).getKey());
      }
    Console.WriteLine();
    }
  }
}