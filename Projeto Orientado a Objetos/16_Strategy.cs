using System;

public class Calendar {
  Strategy day;

  public void defineDay() {
    int date = (int)DateTime.Now.DayOfWeek;
    switch (date) {
      case 0:
        day = new Sunday();
        break;
      case 1:
        day = new Monday();
        break;
      case 2:
        day = new Tuesday();
        break;
      case 3:
        day = new Wednesday();
        break;
      case 4:
        day = new Thursday();
        break;
      case 5:
        day = new Friday();
        break;
      case 6:
        day = new Saturday();
        break;
      default:
        day = new Nullday();
        break;
    }
  }

  public void printDay() {
    if (day == null) day = new Nullday();
    day.printDay();
  }
  
}

public interface Strategy {
  public void printDay();
}

public class Sunday : Strategy {
  public void printDay() {
    Console.WriteLine("Sunday");
  }
}
public class Monday : Strategy {
  public void printDay() {
    Console.WriteLine("Monday");
  }
}
public class Tuesday : Strategy {
  public void printDay() {
    Console.WriteLine("Tuesday");
  }
}
public class Wednesday : Strategy {
  public void printDay() {
    Console.WriteLine("Wednesday");
  }
}
public class Thursday : Strategy {
  public void printDay() {
    Console.WriteLine("Thursday");
  }
}
public class Friday : Strategy {
  public void printDay() {
    Console.WriteLine("Friday");
  }
}
public class Saturday : Strategy {
  public void printDay() {
    Console.WriteLine("Saturday");
  }
}
public class Nullday : Strategy {
  public void printDay() {}
}

class Program1 {
  public static void Main () {
    Calendar cal = new Calendar();
    cal.printDay();
    cal.defineDay();
    cal.printDay();
  }
}