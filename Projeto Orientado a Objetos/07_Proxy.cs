// Thiago Corso Capuano  163996

using System;

public interface ImageIcon {
  public int getIconHeight();
  public int getIconWidth();
  public void paintIcon(int x, int y, string icone, string comp);
}

public class ImageIconIntermediary : ImageIcon {
  private ImageIconReal img;
  public ImageIconIntermediary () {
    this.img = new ImageIconReal();
  }

  public int getIconHeight () {
    return this.img.getIconHeight();
  }
  public int getIconWidth () {
    return this.img.getIconWidth();
  }
  public void paintIcon (int x, int y, string icone, string comp) {
    this.img.paintIcon(x, y, icone, comp);
  }
}

public class ImageIconReal : ImageIcon {
  private int height, width;

  public int getIconHeight () {
    return this.height;
  }
  public int getIconWidth () {
    return this.width;
  }
  public void paintIcon (int x, int y, string icone, string comp) {
    Console.WriteLine("Icone "+icone+" desenhado no componente "+comp+" em "+x+"x"+y);
  }
}

class Program {
  public static void Main () {
    ImageIconIntermediary window = new ImageIconIntermediary();
  }
}