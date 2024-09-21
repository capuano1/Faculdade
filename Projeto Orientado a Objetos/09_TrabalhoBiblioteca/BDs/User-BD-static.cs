using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

public class UserBD_static : BaseMedClass, UBD {

    private static UserBD_static? BD;
    private List<IUser> UserList;

    private UserBD_static() {
        UserList = new List<IUser>();
    }

    public static UserBD_static iniciaBD() {
        if (BD == null) BD = new UserBD_static();
        return BD;
    }

    public void registraUsuario(IUser user) => UserList.Add(user); 

    public void removeUsuario(IUser user) => UserList.Remove(user);
    
    public List<IUser> getUsers() => UserList;

    public IUser? buscaUser(string cod) => this.UserList.Find(x => x.getCod() == cod);

}