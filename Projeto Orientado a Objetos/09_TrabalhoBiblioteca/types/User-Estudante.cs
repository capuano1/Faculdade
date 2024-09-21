using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class userEstudante : IUser {
    
    public userEstudante (string nome, string codg, int age) : base(nome, codg, age, "Estudante") {}
}