#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
// declaracion de variables
// GLfloat ...;
// theta[] me indica los �ngulos iniciales en los 3 ejes
static GLfloat theta[] = {0.0,0.0,0.0};
// eje es el �ngulo a rotar
static GLint eje = 2;
// construya su poligono base
void cara()
{
 glBegin(GL_POLYGON);
 // ... escriba su c�digo
 glEnd();
}
// construya su objeto geom�trico mediante cubo()
void cubo(void)
{
 cara();
 // ... escriba su c�digo
}
// dibujamos nuestra escena
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
// composicion de rotaciones
 glRotatef(theta[0],1.0,0.0,0.0);
 glRotatef(theta[1],0.0,1.0,0.0);
 glRotatef(theta[2],0.0,0.0,1.0);
 cubo();
 glFlush();
// intercambiamos los buffers, el que se muestra y el que esta oculto
 glutSwapBuffers();
} 
// esta funci�n controla el angulo de rotaci�n seg�n el eje de giro
void girar_objeto_geometrico ()
{
 theta[eje] += 2.0;
 if(theta[eje]>360) theta[eje] -= 360.0;
 display();
}
void teclado(unsigned char tecla,int x,int y)
{
 switch(tecla){
 case 'a' : eje = 0; break;
 case 's' : eje = 1; break;
 case 'd' : eje = 2; break;
 case 'f' : exit(0) ; break;
 }
}
// control de ventana (recuerde el volumen de visualizaci�n)
// modifique dicho volumen seg�n su conveniencia
void myReshape(int w, int h)
{
 glViewport(0,0,w,h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if(w <=h)
 glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
 2.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
 else
 glOrtho(-2.0*(GLfloat)w/(GLfloat)h,
 2.0*(GLfloat)w/(GLfloat)h, -2.0,2.0,-10.0,10.0);
 glMatrixMode(GL_MODELVIEW);
}
void main(int argc,char** argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500,500);
 glutCreateWindow("mi objeto bajo rotaciones");
 glutReshapeFunc(myReshape);
 // invocamos a display() para dibujar nuestra escena
 glutDisplayFunc(display);
 // esta funcion llama a girar_objeto_geom�trico() mientras no haya evento //alguno
ocasionado por el usuario
 glutIdleFunc(girar_objeto_geometrico);
 glutKeyboardFunc(teclado);
 /*glutMouseFunc(mouse);*/ 
 glEnable(GL_DEPTH_TEST);
 glutMainLoop();
} 
