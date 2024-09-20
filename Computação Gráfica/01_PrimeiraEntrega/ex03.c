#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float drawx[100];
float drawy[100];
int count=0;

void line (float x[], float y[], int strt) {
  int i;
  glPointSize(5.0);
  glBegin(GL_LINES);
    for (i=0; i<2; i++) {
      glVertex2f(x[strt+i], y[strt+i]);
    }
  glEnd();
  glFlush();
}

void begin () {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  float x[2] = {0, 0};
  float y[2] = {0, 0};
  line(x, y, 0);
}

void MouseInt (int botao, int estado, int x, int y) {
  if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
    float mousex = (float)x; drawx[count] = (mousex/250)-1;
    float mousey = (float)y; drawy[count] = ((mousey/250)-1)*(-1);
    count++;
    if (count % 2 == 0) {
      line(drawx, drawy, count-2);
    }
  }
}

void KeyboardInt (unsigned char key, int x, int y) {
  switch (key) {
    case '0': glColor3f(0.0, 0.0, 1.0); break;
    case '1': glColor3f(0.0, 1.0, 0.0); break;
    case '2': glColor3f(1.0, 0.0, 0.0); break;
    case '3': glColor3f(0.0, 1.0, 1.0); break;
    case '4': glColor3f(1.0, 0.0, 1.0); break;
    case '5': glColor3f(1.0, 1.0, 0.0); break;
    case '6': glColor3f(1.0, 1.0, 1.0); break;
    case '7': glColor3f(0.0, 0.5, 0.5); break;
    case '8': glColor3f(0.5, 0.5, 0.5); break;
    case '9': glColor3f(1.0, 0.5, 0.0); break;
  }
}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Ex01");
  glutDisplayFunc(begin);
  glutMouseFunc(MouseInt);
  glutKeyboardFunc(KeyboardInt);
  glutMainLoop();
}