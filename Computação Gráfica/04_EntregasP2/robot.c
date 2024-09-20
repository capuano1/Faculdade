#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.141592654


float armr=0.0;
float arml=0.0;
float legr = 0.0;
float legl = 0.0;

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 4

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "surface1.bmp",
        "surface2.bmp",
        "surface3.bmp",
        "surface5.bmp"
};

void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                /* texture_id = vetor que guardas os números das texturas */

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas();

}

void circulo(){
    int i;
    float angulo = 0.0;
    glBegin(GL_POLYGON);
        for (i=0;i<=7;i++) {
            angulo= 2 * PI * i / 7.0;
            glVertex2f(0.05*cos(angulo), 0.05*sin(angulo));
        }
    glEnd ();
}
void retangulo(){
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.12, 0.4);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.12, 0.4);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.09, 0.04);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-0.09, 0.04);
    glEnd();
}
void arms(){
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.03, 0.3);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.03, 0.3);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.03, 0.02);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-0.03, 0.02);
    glEnd();
}

void head(){
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.07, 0.5);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.07, 0.5);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.07, 0.4);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-0.07, 0.4);
    glEnd();
}

void desenha(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 1); //Branco
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    //glColor3f(0.7,0.5,0.0);
    head();
    glPopMatrix();


    glPushMatrix();
    //glColor3f(0.0,0.0,0.0);
    glTranslatef(-0.07,0.09,0.0);
    glRotatef(-180,0.0,0.0,1.0);
    glRotatef(legl,0.0,0.0,-1.0);
    arms();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.0,0.0,0.0);
    glTranslatef(0.07,0.09,0.0);
    glRotatef(-180,0.0,0.0,1.0);
    glRotatef(legr,0.0,0.0,-1.0);
    arms();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.0,0.0,0.0);
    glTranslatef(0.09,0.35,0.0);
    glRotatef(-30,0.0,0.0,1.0);
    glRotatef(armr,0.0,0.0,1.0);
    arms();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.0,0.0,0.0);
    glTranslatef(-0.09,0.35,0.0);
    glRotatef(30,0.0,0.0,1.0);
    glRotatef(arml,0.0,0.0,1.0);
    arms();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0,0.0,0.0);
    retangulo();
    glPopMatrix();

    glFlush();

}

void teclado(unsigned char tecla, int x, int y){
    switch (tecla){
        case 't' :
            arml += 0.5;
            break;
        case 'y' :
            armr -= 0.5;
            break;
        case 'g' :
            legl += 0.5;
            break;
        case 'h' :
            legr -= 0.5;
            break;
    }
    glutPostRedisplay();
}

void lightning(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    //Atenuação radial
    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);   //define a0
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);    //define a1
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);  //define a2

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {0.0f, 0.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {0.0f, 0.0f, -1.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);               //espalhamento angular
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);              //atenuação angular

    //Parâmetros definidos globalmente
    //GLfloat global_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    ////Reflexão especular definida como a posição de visão corrente
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    ////Habilitar cálculos de iluminação para ambas as faces dos polígonos
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void)
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    /*gluLookAt(4.0, 2.0, 1.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  *///vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 8.0); //define uma projeção ortogonal
    //gluPerspective(45.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva
    //glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    //glViewport(0, 0, 500, 500);

    lightning();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (1000 ,600);
    glutCreateWindow ("Robot");
    glutDisplayFunc (desenha);
    glutKeyboardFunc(teclado);
    init();
    initTexture();
    glutMainLoop ();
    return 0;
}

