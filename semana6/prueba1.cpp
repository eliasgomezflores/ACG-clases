//------------------------------------------------------------
/// breve Este es un ejemplo muy simple de una curva de hermite.
/// Esta curva contiene 2 puntos finales y 2 tangentes
/// vectores que describen la forma de la curva.
//------------------------------------------------------------
#include <stdlib.h>
#include <GL/glut.h>
float Geometry[4][3] = {
{ 10,10,0 }, // Punto1
{-10,5,-2 }, // Punto2
{ 5,-5,0 }, // Tangente1
{ 5,10,0 } // Tangente2
};
unsigned int LOD=20;
void OnReshape(int w, int h)
{
// evita una divisi�n por cero cuando se minimiza
if (h==0)
h=1;
	
// establece la regi�n dibujable de la ventana
glViewport(0,0,w,h);
// configurar la matriz de proyecci�n
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
//solo usa una proyecci�n en perspectiva
gluPerspective(45,(float)w/h,0.1,100);
//volver a la matriz modelview para que podamos mover sobre los objetos
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
void OnDraw() {
// borra la pantalla y el b�fer de profundidad
glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
// borra la transformaci�n anterior
glLoadIdentity();
// establece la posici�n de la c�mara
gluLookAt( 1,10,30, // posici�n del ojo
0,5,0, // punto de punter�a
0,1,0); // hacia arriba
glColor3f(0.5,0.5,1);
glBegin(GL_LINE_STRIP);
// usa el valor de tiempo param�trico 0 a 1
for(int i=0;i!=LOD;++i) {
float t = (float)i/(LOD-1);
// calcular funciones de fusi�n
float b0 = 2*t*t*t - 3*t*t + 1;
float b1 = -2*t*t*t + 3*t*t;
float b2 = t*t*t - 2*t*t + t;
float b3 = t*t*t - t*t;
// calcule las x, y y z del punto de curva
float x = b0*Geometry[0][0] +
 b1*Geometry[1][0] +
 b2*Geometry[2][0] +
 b3*Geometry[3][0] ;
float y = b0*Geometry[0][1] +
 b1*Geometry[1][1] +
 b2*Geometry[2][1] +
 b3*Geometry[3][1] ;
float z = b0*Geometry[0][2] +
 b1*Geometry[1][2] +
 b2*Geometry[2][2] +
 b3*Geometry[3][2] ;
// especificar el punto
glVertex3f( x,y,z );
}
glEnd();
glColor3f(0,1,0.5);
glPointSize(3);
glBegin(GL_POINTS);
glVertex3fv( Geometry[0] );
glVertex3fv( Geometry[1] );
glEnd();
glColor3f(0.5,1,0.5);
glPushMatrix();
glTranslatef(Geometry[0][0],Geometry[0][1],Geometry[0][2]);
glBegin(GL_LINES);
glVertex3f( 0,0,0 );
glVertex3fv( Geometry[2] );
glEnd();
glPopMatrix();
glPushMatrix();
glTranslatef(Geometry[1][0],Geometry[1][1],Geometry[1][2]);
glBegin(GL_LINES);
glVertex3f( 0,0,0 );
glVertex3fv( Geometry[3] );
glEnd();
glPopMatrix();
// actualmente hemos estado dibujando en el b�fer posterior, necesitamos
// para intercambiar el b�fer posterior con el frontal para que la imagen sea visible
glutSwapBuffers();
}
void OnInit() {
// habilitar pruebas de profundidad
glEnable(GL_DEPTH_TEST);
}
void OnExit() {
}
void OnKeyPress(unsigned char key,int,int) {
switch(key) {
// Aumentar el LOD
case '+':
++LOD;
break;
// disminuye el LOD
case '-':
--LOD;
// tiene un valor m�nimo de LOD
if (LOD<3)
LOD=3;
break;
default:
break;
}
// Pide a Glut que vuelva a dibujar la pantalla para nosotros ...
glutPostRedisplay();
}
int main(int argc,char** argv) {
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
glutInitWindowSize(640,480);
glutCreateWindow("Curva Hermite : +/- para cambiar nivel de Detalle");
 // establece la funci�n a usar para dibujar nuestra escena
glutDisplayFunc(OnDraw);
// establece la funci�n para manejar los cambios en el tama�o de la pantalla
glutReshapeFunc(OnReshape);
 // establece la funci�n para presionar las teclas
glutKeyboardFunc(OnKeyPress);
OnInit();
// establece la funci�n que se llamar� cuando salgamos
atexit(OnExit);
glutMainLoop();
return 0;
}
