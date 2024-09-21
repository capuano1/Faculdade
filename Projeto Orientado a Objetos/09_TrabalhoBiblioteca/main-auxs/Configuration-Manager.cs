using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class ConfigManager {

    private int maxAdvert;
    private int maxBook;
    private static ConfigManager instancia;

    private ConfigManager() {
        maxAdvert = 3;
        maxBook = 3;
    }

    public static ConfigManager instanciaConfig() {
        if (instancia == null) instancia = new ConfigManager();
        return instancia; 
    }

    public int getMaxAdvert() { return this.maxAdvert; }
    public int getMaxBook() { return this.maxBook; }
    public void setMaxAdvert(int value) { this.maxAdvert = value; }
    public void setMaxBook(int value) { this.maxBook = value; }

}