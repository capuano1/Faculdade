using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

public interface UBD {

    public void registraUsuario(IUser user);
    public void removeUsuario(IUser user);
    public List<IUser> getUsers();
    public IUser? buscaUser(string cod);

}