/******* Inicio de las bibliotecas *******/

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/******* Fin de las bibliotecas *******/

/******Prototipos de función void display(); ***/

void specialKeys();
// Variables globales
double rotate_y=0;
double rotate_x=0;

/******* Fin de la función display *******/

/*****Función de retrollamada “display()” *****/

void display()
{
// Borrar pantalla y Z-buffer
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
// Resetear transformaciones
glLoadIdentity();

/******* Fin de la funcion  retrollamdo *******/

/*****  Rotar cuando el usuario cambie “rotate_x” y “rotate_y” *****/

glRotatef( rotate_x, 1.0, 0.0, 0.0 );
glRotatef( rotate_y, 0.0, 1.0, 0.0 );

/******* Fin de la función rotar  *******/

/*Inicio de la ubicación y pigmentación de las ras o tapas del cubo*/
//LADO FRONTAL: lado naranja

glBegin(GL_POLYGON);

glColor3f( 1.0 ,0.5, 0.0);
glVertex3f( 0.5, -0.5, -0.5 ); 
glVertex3f( 0.5, 0.5, -0.5 ); 
glVertex3f( -0.5, 0.5, -0.5 ); 
glVertex3f( -0.5, -0.5, -0.5 ); 

glEnd();

/* las función glColor3f() es para asignar el color y en cambio las función glVrtyix3f() es para asignar vértices, con las dos combinadas podemos generar un mosaico  de colores*/

/*FIN DE LA CARA 1*/
// LADO TRASERO: 
glBegin(GL_POLYGON);

glColor3f(  1.0 ,0.5, 0.0); // color de la cara o tapa
glVertex3f( 0.5, -0.5, 0.5 );
glVertex3f( 0.5, 0.5, 0.5 );
glVertex3f( -0.5, 0.5, 0.5 );
glVertex3f( -0.5, -0.5, 0.5 );

glEnd();

// LADO DERECHO:
glBegin(GL_POLYGON);
glColor3f( 1.0 ,0.0, 1.0 ); // color de la cara o tapa
glVertex3f( 0.5, -0.5, -0.5 );
glVertex3f( 0.5, 0.5, -0.5 );
glVertex3f( 0.5, 0.5, 0.5 );
glVertex3f( 0.5, -0.5, 0.5 );
glEnd();

// LADO IZQUIERDO: 
glBegin(GL_POLYGON);
glColor3f( 1.0 ,0.0, 1.0 ); // color de la cara o tapa
glVertex3f( -0.5, -0.5, 0.5 );
glVertex3f( -0.5, 0.5, 0.5 );
glVertex3f( -0.5, 0.5, -0.5 );
glVertex3f( -0.5, -0.5, -0.5 );
glEnd();
// LADO SUPERIOR: 
glBegin(GL_POLYGON);
glColor3f( 0.0 ,1.0, 1.0 ); // color de la cara o tapa
glVertex3f( 0.5, 0.5, 0.5 );
glVertex3f( 0.5, 0.5, -0.5 );
glVertex3f( -0.5, 0.5, -0.5 );
glVertex3f( -0.5, 0.5, 0.5 );
glEnd();
// LADO INFERIOR: 
glBegin(GL_POLYGON);
glColor3f( 0.0 ,1.0, 1.0); // color de la cara o tapa
glVertex3f( 0.5, -0.5, -0.5 );
glVertex3f( 0.5, -0.5, 0.5 );
glVertex3f( -0.5, -0.5, 0.5 );
glVertex3f( -0.5, -0.5, -0.5 );
glEnd();

glFlush(); //NOTA: dan el efecto de doble-buffer.
glutSwapBuffers(); //NOTA: dan el efecto de doble-buffer.
}

/*fin de la ubicación y pigmentación de las ras o tapas del cubo*/

// Función de retrollamada “specialKeys()”
void specialKeys( int key, int x, int y )
{
// La flecha derecha: incrementa su rotación en 5 grados
if (key == GLUT_KEY_RIGHT)
rotate_y += 5;
// La flecha izquierda: disminuye su rotación en 5 grados
else if (key == GLUT_KEY_LEFT)
rotate_y -= 5;

else if (key == GLUT_KEY_UP)
rotate_x += 5;

else if (key == GLUT_KEY_DOWN)
rotate_x -= 5;
// Solicitud para actualizar la pantalla
glutPostRedisplay();
}

// Función main()
int main(int argc, char* argv[])
{
// Inicializar los parámetros GLUT y de usuario proceso
glutInit(&argc,argv);
// Solicitar ventana con color real y doble buffer con Z-buffer
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// Crear ventana
glutCreateWindow("CUBO-PREGUNTA-1"); // titulo del cuadro de ejecución 
// Habilitar la prueba de profundidad de Z-buffer
glEnable(GL_DEPTH_TEST);
// Funciones de retrollamada
glutDisplayFunc(display); glutSpecialFunc(specialKeys);
// Pasar el control de eventos a GLUT
glutMainLoop();
// Regresar al sistema operativo
return 0;
}
