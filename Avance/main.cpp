#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
//#incldue <cmath.h>
#include <bits/stdc++.h>
using namespace std;
typedef float Matrix4x4 [4][4];
typedef float Matrix4x3 [4][3];
Matrix4x4 matrizTransformacion;
GLint X=150,Y=150,Z=150;
                            //  0           1           2           3
//float matrizPuntosI[4][4]={{50,25,0,1},{50,50,0,1},{25,50,0,1},{25,25,0,1}};

float matrizPuntosI[5][3]={{15,15,30},
                          {10,10,10},
                          {10,20,10},
                          {20,20,10},
                          {20,10,10}};
float matrizPuntosF[5][3];

float translacionX=0, translacionY=0, translacionZ=20;
/*
float escalacionX,escalacionY,escalacionZ;
float angulo1,angulo2,angulo3;
float A,B,C;
*/

void matrixSetIdentity(Matrix4x4 m){
    int i,j;
    for(i=0; i<4 ; i++){
        for(j=0; j<4; j++){
            m[i][j] = (i == j);
        }
    }
}


void matrixPreMultiply(Matrix4x4 a, Matrix4x4 b){
    int i, j;
    Matrix4x4 tmp;
    for(i=0; i<4; i++){
        for(j=0; j<4 ;j++ ){
            tmp[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j];
        }
    }
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            matrizTransformacion[i][j] = tmp[i][j];
}

void Traslacion(int tx, int ty, int tz){

    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][3]=tx;
    m[1][3]=ty;
    m[2][3]=tz;
    matrixPreMultiply(m,matrizTransformacion);
}


//1.ESCALADO DESDE EL ORIGEN

void Escalado(int x, int y, int z){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=x;
    m[1][1]=y;
    m[2][2]=z;
    matrixPreMultiply(m,matrizTransformacion);

}

//2.ESCALADO DESDE UN PUNTO CUALQUIERA

void Escalado2(float x, float y, float z, float refx, float refy, float refz){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=x;
    m[1][1]=y;
    m[2][2]=z;
    m[0][3]=refx*(1-x);
    m[1][3]=refy*(1-y);
    m[2][3]=refz*(1-z);
    matrixPreMultiply(m,matrizTransformacion);
}

//3.REFLEXION XY

void ReflexionXY(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[2][2]=-1;
    matrixPreMultiply(m,matrizTransformacion);

}

//4.REFLEXION YZ

void ReflexionYZ(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=-1;
    matrixPreMultiply(m,matrizTransformacion);

}

//5.REFLEXION XZ

void ReflexionXZ(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[1][1]=-1;
    matrixPreMultiply(m,matrizTransformacion);

}

//6.REFLEXION SOBRE EL ORIGEN

void ReflexionXYZ(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=-1;
    m[1][1]=-1;
    m[2][2]=-1;
    matrixPreMultiply(m,matrizTransformacion);
}

//7.ROTACION EN EL EJE X

void Rotacionx(float x){
    x = x * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[1][1]=cos(x);
    m[1][2]=-sin(x);
    m[2][1]=sin(x);
    m[2][2]=cos(x);
    matrixPreMultiply(m,matrizTransformacion);
}

//8.ROTACION EN EL EJE Y

void Rotaciony(float y){
    y = y * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=cos(y);
    m[0][2]=sin(y);
    m[2][0]=-sin(y);
    m[2][2]=cos(y);
    matrixPreMultiply(m,matrizTransformacion);
}

//9.ROTACION EN EL EJE Z

void Rotacionz(float z){
    z = z * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=cos(z);
    m[0][1]=-sin(z);
    m[1][0]=sin(z);
    m[1][1]=cos(z);
    matrixPreMultiply(m,matrizTransformacion);
}


//10.ROTACION INVERSA EN EL EJE X


void Rotacionix(float x){
    x = x * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[1][1]=cos(x);
    m[1][2]=sin(x);
    m[2][1]=-sin(x);
    m[2][2]=cos(x);
    matrixPreMultiply(m,matrizTransformacion);
}

//11.ROTACION INVERSA EN EL EJE Y


void Rotacioniy(float y){
    y = y * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=cos(y);
    m[0][2]=-sin(y);
    m[2][0]=sin(y);
    m[2][2]=cos(y);
    matrixPreMultiply(m,matrizTransformacion);
}


//12.ROTACION INVERSA EN EL EJE Z

void Rotacioniz(float z){
    z = z * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=cos(z);
    m[0][1]=sin(z);
    m[1][0]=-sin(z);
    m[1][1]=cos(z);
    matrixPreMultiply(m,matrizTransformacion);
}

//13.PROYECCION SUPERIOR

void ProyeccionS(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[2][2]=0;
    matrixPreMultiply(m,matrizTransformacion);
}

//14.PROYECCION LATERAL

void ProyeccionL(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[1][1]=0;
    matrixPreMultiply(m,matrizTransformacion);
}

//15.PROYECCION FRONTAL

void ProyeccionF(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=0;
    matrixPreMultiply(m,matrizTransformacion);
}

//16.PROYECCION AXONOMETRICA

void MProyAxo(float a, float b){
    Matrix4x4 m;
    matrixSetIdentity(m);
    a = a * 0.0174533;
    b = b * 0.0174533;
    m[0][0]=-sin(a);
    m[0][1]=cos(a);
    m[1][0]=-sin(b)*cos(a);
    m[1][1]=-sin(b)*sin(a);
    m[1][2]=cos(b);
    m[2][0]=-cos(b)*cos(a);
    m[2][1]=-cos(b)*sin(a);
    m[2][2]=-sin(b);
    matrixPreMultiply(m,matrizTransformacion);
}

//17.PROYECCION AXONOMETRICA

void MProyIso(){
    Matrix4x4 m;
    matrixSetIdentity(m);
    float a = 45 * 0.0174533;
    float b = 45 * 0.0174533;
    m[0][0]=-sin(a);
    m[0][1]=cos(a);
    m[1][0]=-sin(b)*cos(a);
    m[1][1]=-sin(b)*sin(a);
    m[1][2]=cos(b);
    m[2][0]=-cos(b)*cos(a);
    m[2][1]=-cos(b)*sin(a);
    m[2][2]=-sin(b);
    matrixPreMultiply(m,matrizTransformacion);
}

//18.PROYECCION OBLICUA SUPERIOR

void ProyOblS(float a, float b){
    Matrix4x4 m;
    matrixSetIdentity(m);
    a = a * 0.0174533;
    b = b * 0.0174533;
    m[0][2]=cos(b)*tan(a);
    m[1][2]=sin(b)*tan(a);
    m[2][2]=0;

    matrixPreMultiply(m,matrizTransformacion);
}
//19.PROYECCION OBLICUA LATEREAL


void ProyOblL(float a, float b){
    a = a * 0.0174533;
    b = b * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[1][1]=0;
    m[0][2]=cos(b)*tan(a);
    m[2][2]=sin(b)*tan(a);
    matrixPreMultiply(m,matrizTransformacion);
}


//20.PROYECCION OBLICUA FRONTAL

void ProyOblF(float a, float b){
    a = a * 0.0174533;
    b = b * 0.0174533;
    Matrix4x4 m;
    matrixSetIdentity(m);
    m[0][0]=0;
    m[1][2]=cos(b)*tan(a);
    m[2][2]=sin(b)*tan(a);
    matrixPreMultiply(m,matrizTransformacion);
}

//21.PROYECCION OBLICUA SUPERIOR CABALLERA

void ProyOblSupCa( float b){
    Matrix4x4 m;
    matrixSetIdentity(m);
    float a = 45 * 0.0174533;
    b = b * 0.0174533;
    m[0][2]=cos(b)*tan(a);
    m[1][2]=sin(b)*tan(a);
    m[2][2]=0;

    matrixPreMultiply(m,matrizTransformacion);
}

//22.PROYECCION OBLICUA SUPERIOR DE GABINETE

void ProyOblSupGab( float b){
    Matrix4x4 m;
    matrixSetIdentity(m);
    float a = 63.4 * 0.0174533;
    b = b * 0.0174533;
    m[0][2]=cos(b)*tan(a);
    m[1][2]=sin(b)*tan(a);
    m[2][2]=0;

    matrixPreMultiply(m,matrizTransformacion);
}

void TransformarPuntos(void)
{
    int i,k;
    float tmp;
    for(k=0;k<5;k++)
        for(i=0;i<3;i++)
            matrizPuntosF[k][i] = matrizTransformacion[i][0]*matrizPuntosI[k][0] +
                                  matrizTransformacion[i][1]*matrizPuntosI[k][1] +
                                  matrizTransformacion[i][2]*matrizPuntosI[k][2] +
                                  matrizTransformacion[i][3];
}




void ejes3D(void)
{
    glBegin(GL_LINES);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,Z);

    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,Y,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(X,0,0);

    glEnd();
    glFlush();
}

void Dibujar(float a[5][3]){
	glColor3f (0.7, 0.4, 0.7);
	glBegin(GL_POLYGON);
	glVertex3fv(a[0]);
	glVertex3fv(a[1]);
	glVertex3fv(a[2]);
	glEnd();

	glColor3f (0.8, 0.6, 0.5);
	glBegin(GL_POLYGON);
	glVertex3fv(a[0]);
	glVertex3fv(a[2]);
	glVertex3fv(a[3]);
	glEnd();

	glColor3f (0.2, 0.4, 0.7);
	glBegin(GL_POLYGON);
	glVertex3fv(a[0]);
	glVertex3fv(a[3]);
	glVertex3fv(a[4]);
	glEnd();

	glColor3f (0.5, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex3fv(a[0]);
	glVertex3fv(a[4]);
	glVertex3fv(a[1]);
	glEnd();

    glColor3f (0.5, 0.6, 0.2);
	glBegin(GL_POLYGON);
	glVertex3fv(a[1]);
	glVertex3fv(a[2]);
	glVertex3fv(a[3]);
	glVertex3fv(a[4]);
	glEnd();
}

void dibujo(void)
{
    glColor3f(1.0,0.0,0.0);

    Dibujar(matrizPuntosI);
    matrixSetIdentity(matrizTransformacion);

    glFlush();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0,0,0,0);
  ejes3D();
  //dibujo();
  Dibujar(matrizPuntosI);//Dibuja la priamide
  matrixSetIdentity(matrizTransformacion);
  //EJEMPLO ESCALACION
  //Escalado(3,3,3);
  //---------------------------------------------------------------------------------
  //EJEMPLO TRASLACION Y ESCALACION
  //Traslacion(0,0,60);
  //Escalado2(2.5,2.5,2.5,20,70,70);
  //---------------------------------------------------------------------------------
  //EJEMPLO ROTACION EN X
  //Rotacionx(45);
  //---------------------------------------------------------------------------------
  //EJEMPLO ROTACION EN Y
  //Rotaciony(45);
  //---------------------------------------------------------------------------------
  //EJEMPLO ROTACION EN Z
  //Rotacionz(45);
  //EJEMPLO ROTACION INVERSA EN X
  //Rotacionix(45);
  //---------------------------------------------------------------------------------
  //EJEMPLO ROTACION INVERSA EN Y
  //Rotacioniy(45);
  //---------------------------------------------------------------------------------
  //EJEMPLO ROTACION INVERSA EN Z
  //Rotacioniz(45);
  //--------------------------------------------------------------------------------
  //EJEMPLO DE REFLEXION XY
  //ReflexionXY();
  //---------------------------------------------------------------------------------
  //EJEMPLO DE REFLEXION YZ
  //ReflexionYZ();
  //---------------------------------------------------------------------------------
  //EJEMPLO DE REFLEXION XZ
  //ReflexionXZ();
  //---------------------------------------------------------------------------------
  //EJEMPLO DE REFLEXION XYZ
  //ReflexionXYZ();
  //EJEMPLO DE PROYECION SUPERIOR
  //ProyeccionS();
  //EJEMPLO DE PROYECCION LATERAL
  //ProyeccionL();
  //EJEMPLO DE PROYECCION FRONTAL
  //ProyeccionF();
  //EJEMPLO DE PROYECCION AXONOMETRICA
  //MProyAxo(30,60);
  //EJEMPLO DE PROYECCION AXONOMETRICA
  //MProyIso();
  //EJEMPLO DE PROYECCION OBLICUA SUPERIOR
  //ProyOblS(30,30);
  //EJEMPLO DE PROYECCION OBLICUA LATERAL
  //ProyOblL(30,30);
  //EJEMPLO DE PROYECCION OBLICUA FRONTAL
  //ProyOblF(30,30);
  TransformarPuntos();
  Dibujar(matrizPuntosF);
  glutSwapBuffers();
}

void inicio(void)
{
   /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  glOrtho(-X, X, -Y, Y, -Z, Z);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(5.0, 5.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 0.0, 1.0);      /* up is in positive Y direction */
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("escena 3D");
  glutDisplayFunc(display);
  inicio();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
