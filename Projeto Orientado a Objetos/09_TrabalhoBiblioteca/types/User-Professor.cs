using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class userProfessor : IUser {
    
    public userProfessor (string nome, string codg, int age) : base(nome, codg, age, "Professor") {}
}