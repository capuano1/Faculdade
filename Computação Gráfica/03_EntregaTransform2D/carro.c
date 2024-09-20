#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float up = 0.0;
float right = 0.0;
float theta = 0.0;

void rodas() {
  glBegin(GL_POLYGON);
  glVertex2f(-0.05, 0.05);
  glVertex2f(0.05, 0.05);
  glVertex2f(0.05, -0.05);
  glVertex2f(-0.05, -0.05);
  glEnd();
}

void carro() {
  glBegin(GL_QUADS);
  glVertex2f(-0.25, -0.10);
  glVertex2f(-0.25, 0.00);
  glVertex2f(0.25, 0.00);
  glVertex2f(0.25, -0.10);
  glEnd();
}

void desenha() {
  glClearColor(0, 0, 0, 0); // Preto
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(right, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-0.25, -0.25, 0.0);
  carro();

  glPopMatrix();
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(-0.40, -0.42, 0.0);
  glRotatef(-theta, 0.0, 0.0, 1.0);
  rodas();

  glPopMatrix();
  glTranslatef(-0.10, -0.42, 0.0);
  glRotatef(-theta, 0.0, 0.0, 1.0);
  rodas();
  
  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    theta += 5;
    right += 0.01;
    break;
  case GLUT_KEY_LEFT:
    theta -= 5;
    right -= 0.01;
    break;

  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Carro");
  glutDisplayFunc(desenha);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}