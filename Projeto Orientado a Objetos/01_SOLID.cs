//Thiago Corso Capuano - 163996
//Evandro Kayano - 163707

using System;

public interface Client {
  string getDocument();
  string getName();
  string getEmail();
}

public interface Car {
  int getRate();
  string getBrand();
  string getModel();
  string getColor();
  string getPlate();
}

/* Interface Segregation Principle
O princípio da segregação de interface foi aplicado aqui,
já que um cliente pessoa jurídica não possui uma birthDate
(ainda que possuísse, como por exemplo a data da criação da
empresa, esta seria uma informação desnecessária para a
implementação e para a empresa de aluguel de carro), desta
forma, separamos Pessoa Física e Pessoa Jurídica, já que
getBirthDate jamais seria usada por um cliente pessoa jurídica.
*/

public interface ClientPessoaFisica : Client {
  DateTime getBirthDate();
}

public interface ClientPessoaJuridica : Client {
}

/* Liskov Substitution Principle
Tanto a classe ClientBR como a classe ClientTurist podem
explicar este princípio. Nenhuma das duas "faz menos" do que
sua classe pai (Client), isto é, ambas implementam
completamente a interface e seus métodos. Com isso, podemos
ter a classe Rent dependendo da interface Client, ainda que
utilizando objetos do tipo ClientBR e ClientTurist em 
implementações que estejam esperando o tipo Client (classe
pai)
*/

public class ClientBR : ClientPessoaFisica {
  private string cpf;
  private DateTime birthDate;
  private string name;
  private string email;

  public ClientBR (string cpfNumber, DateTime birth, string nameClient, string emailClient) {
    cpf = cpfNumber;
    birthDate = birth;
    name = nameClient;
    email = emailClient;
  }

  public string getDocument() {
    return cpf;
  }
  public string getName() {
    return name;
  }
  public string getEmail() {
    return email;
  }
  public DateTime getBirthDate() {
    return birthDate;
  }
}

public class ClientTurist : ClientPessoaFisica {
  private string passport;
  private DateTime birthDate;
  private string name;
  private string email;

  public ClientTurist (string passportNumber, DateTime birth, string nameClient, string emailClient) {
    passport = passportNumber;
    birthDate = birth;
    name = nameClient;
    email = emailClient;
  }

  public string getDocument() {
    return passport;
  }
  public string getName() {
    return name;
  }
  public string getEmail() {
    return email;
  }
  public DateTime getBirthDate() {
    return birthDate;
  }
}

public class ClientCompany : ClientPessoaJuridica {
  private string cnpj;
  private string name;
  private string email;

  public ClientCompany (string cnpjNumber, string nameClient, string emailClient) {
    cnpj = cnpjNumber;
    name = nameClient;
    email = emailClient;
  }

  public string getDocument() {
    return cnpj;
  }
  public string getName() {
    return name;
  }
  public string getEmail() {
    return email;
  }
}

/* Single Responsibility Principle:
A classe DailyCar (que implementa a interface Car) possui
como única responsabilidade possuir os detalhes do carro
sendo alugado e, mais especificamente, apenas dos carros
que são alugados seguindo a modalidade de day-use, isto é,
o carro está sendo alugado por dia, geralmente usado por
turistas.
*/

public class DailyCar : Car {
  private int dailyRate;
  private string brand;
  private string model;
  private string color;
  private string plate;

  public DailyCar (int rate, string brandCar, string modelCar, string colorCar, string plateCar) {
    dailyRate = rate;
    brand = brandCar;
    model = modelCar;
    color = colorCar;
    plate = plateCar;
  }

  public int getRate() {
    return dailyRate;
  }
  public string getBrand() {
    return brand;
  }
  public string getModel() {
    return model;
  }
  public string getColor() {
    return color;
  }
  public string getPlate() {
    return plate;
  }
}

public class MonthlyCar : Car {
  private int monthlyRate;
  private string brand;
  private string model;
  private string color;
  private string plate;

  public MonthlyCar (int rate, string brandCar, string modelCar, string colorCar, string plateCar) {
    monthlyRate = rate;
    brand = brandCar;
    model = modelCar;
    color = colorCar;
    plate = plateCar;
  }

  public int getRate() {
    return monthlyRate;
  }
  public string getBrand() {
    return brand;
  }
  public string getModel() {
    return model;
  }
  public string getColor() {
    return color;
  }
  public string getPlate() {
    return plate;
  }
}

/* Dependency Inversion Principle
Temos a classe Rent dependendo das interfaces Client e Car,
ao invés de suas subclasses. Desta forma, a classe Rent
depende de um tipo de abstração, ao invés de depender de
classes com implementação. Isto também traz a vantagem
de simplificar o código, já que caso tivéssemos uma interface
com 10 subclasses, poderíamos ter de fazer 10 implementações
diferentes dependendo do caso. Com a dependência apenas da
interface, podemos usar qualquer uma das subclasses em uma
mesma implementação que dependa da interface, além de
abstrair as diferentes subclasses e suas implementações.
*/

/* Open / Closed Principle
Novamente na classe Rent, podemos identificar o Open / Closed
Principle. A classe Rent está aberta para extensão pois ainda
que criemos futuramente um novo tipo de subclasse de Car que
possua uma cobrança semanal por exemplo, o nosso método
getFinalValue ainda assim é capaz de funcionar normalmente.
*/


public class Rent {
  private int time;
  private Client cliente;
  private Car carro;

  public Rent (int timeRent, Client client, Car car) {
    time = timeRent;
    cliente = client;
    carro = car;
  }
  
  public int getFinalValue() {
    return time * carro.getRate();
  }
  public Client getClientDetails() {
    return cliente;
  }
  public Car getCarDetails() {
    return carro;
  }
}