#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void point (float x, float y) {
  glPointSize(5.0);
  glBegin(GL_POINTS);
    glVertex2f(x, y);
  glEnd();
  glFlush();
}

void begin () {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  point(0, 0);
}

void MouseInt (int botao, int estado, int x, int y) {
  if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
    float mousex = (float)x;
    float mousey = (float)y;
    point((mousex/250)-1, ((mousey/250)-1)*(-1));
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