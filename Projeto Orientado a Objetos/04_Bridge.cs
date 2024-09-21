//Thiago Corso Capuano  163996

using System;
using System.Collections.Generic;

public interface Queue {
  public void queue ();
  public void dequeue ();
  public void enqueue (TestClass obj);
  public bool isEmpty ();
  public int size();
}

public class FIFO : Queue {
  private ListType lst;

  public FIFO (ListType lst) {
    this.lst = lst;
  }
  public void queue () {
    this.lst.PrintQueue();
  }
  public void enqueue(TestClass obj) {
    this.lst.Add(obj, -1);
  }
  public void dequeue () {
    this.lst.Remove(0);
  }
  public bool isEmpty () {
    return this.lst.isEmpty();
  }
  public int size() {
    return this.lst.size();
  }
}

public class LIFO : Queue {
  private ListType lst;

  public LIFO (ListType lst) {
    this.lst = lst;
  }
  public void queue () {
    this.lst.PrintQueue();
  }
  public void enqueue(TestClass obj) {
    this.lst.Add(obj, 0);
  }
  public void dequeue () {
    this.lst.Remove(-1);
  }
  public bool isEmpty () {
    return this.lst.isEmpty();
  }
  public int size() {
    return this.lst.size();
  }
}

public interface ListType {
  public void PrintQueue();
  public void Add(TestClass obj, int index);
  public void Remove(int index);
  public bool isEmpty();
  public int size();
}

public class ListTypeList : ListType {
  private List<TestClass> lst;

  public ListTypeList (int maxSize) {
    lst = new List<TestClass>(maxSize);
  } 

  
  public void PrintQueue() {
    foreach (TestClass obj in lst) {
      Console.WriteLine("Achei o objeto "+obj.getNumber());
    }
  }
  public void Add(TestClass obj, int index) {
    if (index == -1) index = lst.Count-1;
    lst.Insert(index, obj);
  }
  public void Remove (int index) {
    if (index == -1) index = lst.Count-1;
    lst.RemoveAt(index);
  }
  public bool isEmpty () {
    return lst.Count == 0;
  }
  public int size () {
    return lst.Count;
  }
}

public class ListTypeArray : ListType {
  private TestClass[] lst;

  public ListTypeArray (int maxSize) {
    lst = new TestClass[maxSize];
  }
  
  public void PrintQueue() {
    foreach (TestClass obj in lst) {
      Console.WriteLine("Achei o objeto "+obj.getNumber());
    }
  }
  public void Add(TestClass obj, int index) {
    int last = lst.Length - 1;
    if (index == -1) index = last;
    if (lst[index] == null) lst[index] = obj;
    else {
      for (int i = last; i >= index; i--) lst[i+1] = lst[i];
    }
    lst[index] = obj;
  }
  public void Remove (int index) {
    int last = lst.Length - 1;
    if (index == -1) lst[last] = null;
    else {
      for (int i = index; i < last; i++) lst[i] = lst[i+1];
    }
    lst[last] = null;
  }
  public bool isEmpty () {
    return lst.Length == 0;
  }
  public int size () {
    return lst.Length;
  }
}

public class TestClass {
  private int number;
  public TestClass (int num) {
    this.number = num;
  }
  public int getNumber() {
    return this.number;
  }
}

class Program {
  public void Main() {
    FIFO frst = new FIFO(new ListTypeList(10));
    LIFO last = new LIFO(new ListTypeArray(10));
    TestClass teste1 = new TestClass(1);
    TestClass teste2 = new TestClass(2);
    TestClass teste3 = new TestClass(3);
    TestClass teste4 = new TestClass(4);

    Console.WriteLine(frst.isEmpty());
    frst.enqueue(teste1);
    frst.enqueue(teste2);
    last.enqueue(teste3);
    last.enqueue(teste4);
    frst.queue();
    last.queue();
    frst.dequeue();
    last.dequeue();
    frst.queue();
    last.queue();
  }
}