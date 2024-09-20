#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void point (float x, float y) {
  glPointSize(5.0);
  glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(x, y);
  glEnd();
  glFlush();
}

void begin () {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  point(0, 0);
}

void MouseInt (int botao, int estado, int x, int y) {
  if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
    float mousex = (float)x;
    float mousey = (float)y;
    point((mousex/250)-1, ((mousey/250)-1)*(-1));
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
  glutMainLoop();
}