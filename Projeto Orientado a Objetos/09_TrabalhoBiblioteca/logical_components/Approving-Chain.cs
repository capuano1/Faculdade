using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public interface IHandler {
    IHandler setNext (IHandler handler);
    int handle(Book livro, IUser user);
}

public abstract class abstractHandler : IHandler {

    protected IHandler? next;

    public IHandler setNext (IHandler handler) {
        this.next = handler;
        return handler;
    }

    public abstract int handle(Book livro, IUser user);
}

public class availableCheck : abstractHandler {

    public override int handle(Book livro, IUser user) {
        if (livro.getCopAvailable() < 1) return 1;
        if (this.next != null) return this.next.handle(livro, user);
        return 0;
    }
}

public class advertCheck : abstractHandler {

    private int maxAdvert;

    public advertCheck(int value) {
        this.maxAdvert = value;
    }

    public override int handle(Book livro, IUser user) {
        if (user.getAdvert() >= this.maxAdvert) return 2;
        if (this.next != null) return this.next.handle(livro, user);
        return 0;
    }
}

public class maxBookCheck : abstractHandler {

    private int maxBook;

    public maxBookCheck(int value) {
        this.maxBook = value;
    }

    public override int handle(Book livro, IUser user) {
        if (user.getNumLivros() >= this.maxBook) return 3;
        if (this.next != null) return this.next.handle(livro, user);
        return 0;
    }
}