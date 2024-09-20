#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float drawx[3];
float drawy[3];
int count = 0;
int size = 2;

float normalizeX(float x) { return (x / 250) - 1; }

float normalizeY(float y) { return ((y / 250) - 1) * (-1); }

void bresenham(int x1, int x2, int y1, int y2) {
  int dx, dy, incSup, incInf, p, x, y, m;
  int valor;
  if (x1 > x2) {
    int xaux, yaux;
    xaux = x1;
    yaux = y1;
    x1 = x2;
    y1 = y2;
    x2 = xaux;
    y2 = yaux;
  }
  dx = x2 - x1;
  dy = y2 - y1;
  int incx = 1, incy = 1;
  if (dx < 0) {
    dx = -dx;
    incx = -incx;
  }
  if (dy < 0) {
    dy = -dy;
    incy = -incy;
  }

  if (dy == 0) {
    if (x1 > x2) {
      int aux = x1;
      x1 = x2;
      x2 = aux;
    }
    for (;dx>0;x1+=incx, dx--) {
      glVertex2f(normalizeX(x1), normalizeY(y1));
    }
    return;
  }
  else if (dx == 0) {
    if (y1 > y2) {
      int aux = y1;
      y1 = y2;
      y2 = aux;
    }
    for (;dy>0;y1+=incy, dy--) {
      glVertex2f(normalizeX(x1), normalizeY(y1));
    }
    return;
  }
  else if (dx == dy) {
    for (;dx>0;x1+=incx, y1+=incy, dx--) {
      glVertex2f(normalizeX(x1), normalizeY(y1));
    }
    return;
  }
  m = dy / dx;
  if (dx > dy) {
    p = 2 * dy - dx;
    incInf = 2 * dy;
    incSup = 2 * (dy - dx);
    x = x1;
    y = y1;
    glVertex2f(normalizeX(x), normalizeY(y));
    while (x < x2) {
      if (p < 0)
        p = p + incInf;
      else {
        p = p + incSup;
        y += incy;
      }
      x += incx;
      glVertex2f(normalizeX(x), normalizeY(y));
    }
  }
  else {
    p = 2 * dx - dy;
    incInf = 2 * dx;
    incSup = 2 * (dx - dy);
    x = x1;
    y = y1;
    glVertex2f(normalizeX(x), normalizeY(y));
    while (x < x2) {
      if (p < 0)
        p = p + incInf;
      else {
        p = p + incSup;
        x += incx;
      }
      y += incy;
      glVertex2f(normalizeX(x), normalizeY(y));
    }
  }
}

void draw(float x[], float y[]) {
  glPointSize(5.0);
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  bresenham(drawx[0], drawx[1], drawy[0], drawy[1]);
  glEnd();
  glFlush();
}

void begin() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POINTS);
  glVertex2f(0, 0);
  glEnd();
}

void MouseInt(int botao, int estado, int x, int y) {
  if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
    drawx[count] = x;
    drawy[count] = y;
    count++;
    if (count % 2 == 0) {
      count = 0;
      draw(drawx, drawy);
    }
  }
}

void KeyboardInt(unsigned char key, int x, int y) {
  switch (key) {
  case '0':
    glColor3f(0.0, 0.0, 1.0);
    break;
  case '1':
    glColor3f(0.0, 1.0, 0.0);
    break;
  case '2':
    glColor3f(1.0, 0.0, 0.0);
    break;
  case '3':
    glColor3f(0.0, 1.0, 1.0);
    break;
  case '4':
    glColor3f(1.0, 0.0, 1.0);
    break;
  case '5':
    glColor3f(1.0, 1.0, 0.0);
    break;
  case '6':
    glColor3f(1.0, 1.0, 1.0);
    break;
  case '7':
    glColor3f(0.0, 0.5, 0.5);
    break;
  case '8':
    glColor3f(0.5, 0.5, 0.5);
    break;
  case '9':
    glColor3f(1.0, 0.5, 0.0);
    break;
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Bresenham");
  glutDisplayFunc(begin);
  glutMouseFunc(MouseInt);
  glutKeyboardFunc(KeyboardInt);
  glutMainLoop();
}