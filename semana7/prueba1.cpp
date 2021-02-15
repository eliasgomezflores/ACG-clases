/**************************************************************************
************
* curves.cpp *
* Este programa ajusta un conjunto de datos con tres ajustes de curva diferentes *
* algoritmos: interpolación de Lagrange, curvas de Bezier y cubic uniforme B-splines.*
* *
* Author: Cary Laxer *
* *
***************************************************************************
***********/
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <GL/glut.h>
/* Dibujando constantes. */
#define WINDOW_SIZE 540 /* tamaño inicial de ventana */
#define BORDER 10 /* ancho del borde en cada ventana */
#define MAX_POINTS 100 /* número máximo de puntos de control */
#define MARK_FACTOR 0.35 /* factor de escala para 'x' que marca cada punto de control */
#define DELTA_T 0.05 /* factor de tiempo para dibujar cada curva */
/* Mostrar las constantes de la lista. */
#define MARK_LIST 1
#define LAGRANGE_LIST 2
#define BEZIER_LIST 3
#define SPLINE_LIST 4
#define LAGRANGE_TITLE_LIST 5
#define BEZIER_TITLE_LIST 6
#define SPLINE_TITLE_LIST 7
double px[MAX_POINTS], py[MAX_POINTS], minx, maxx, miny, maxy, markd;
int number_of_points = 0;
int WindowSizeX = WINDOW_SIZE, WindowSizeY = WINDOW_SIZE;
int WindowSizeY3 = WINDOW_SIZE / 3;
void interact ();
void mark_points ();
void Lagrange_interpolate ();
void Bezier ();
void spline ();
void gfxinit ();
void display (void);
void reshape (int width, int height);
using namespace std;
int main (int argc, char **argv){
 /* Obtenga datos de entrada. */
 interact ();
 /* Establecer parámetros de ventana gráfica.*/
 glutInit (&argc, argv);
 glutInitWindowSize (WindowSizeX, WindowSizeY);
 glutInitWindowPosition (100, 0);
 glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
 glutCreateWindow ("Curve Fitting");
 glutDisplayFunc (display);
 glutReshapeFunc (reshape);
 gfxinit ();
 glutMainLoop ();
 return 0;
}
void gfxinit ()
/* Esta es la rutina que genera la imagen que se mostrará. */
{
 glClearColor (1.0, 1.0, 1.0, 0.0); /* Hacer el fondo blanco. */
 /* Genere las tres curvas diferentes para mostrar. */
 mark_points (); /* Genere la lista de visualización de marcas de datos. */
 Lagrange_interpolate (); /* Genere las líneas para la interpolación de Lagrange. */
 Bezier (); /* Genere las líneas para la aproximación de Bezier. */
 spline (); /* Genere las líneas para la aproximación de spline. */
}
void reshape (int width, int height)
/* Esta es la función de devolución de llamada que se ejecuta cada vez que la pantalla
 El tamaño ha cambiado. */
{
 WindowSizeX = width;
 WindowSizeY = height;
 WindowSizeY3 = height / 3;
}
void display (void)
/* Esta es la función de devolución de llamada que se ejecuta cada vez que la pantalla
 necesita ser actualizado*/
{
 glClear (GL_COLOR_BUFFER_BIT);
 glViewport (0, 0, WindowSizeX, WindowSizeY);
 /* Dibuje separadores de línea entre ventanas gráficas. */
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 gluOrtho2D (0, WindowSizeX, 0, WindowSizeY);
 glColor3f (0.0, 0.0, 0.0); /* Dibuja líneas de separación en negro. */
 glBegin (GL_LINES);
 glVertex2i (0, WindowSizeY3);
 glVertex2i (WindowSizeX, WindowSizeY3);
 glVertex2i (0, 2*WindowSizeY3);
 glVertex2i (WindowSizeX, 2*WindowSizeY3);
 glEnd ();
 /* Colocar títulos. */
 glRasterPos2i (BORDER, 2*WindowSizeY3+BORDER);
 glCallList (LAGRANGE_TITLE_LIST);
 glRasterPos2i (BORDER, WindowSizeY3+BORDER);
 glCallList (BEZIER_TITLE_LIST);
 glRasterPos2i (BORDER, BORDER);
 glCallList (SPLINE_TITLE_LIST);
 /* Haga la interpolación de Lagrange en el tercio superior de la ventana. */
 glLoadIdentity ();
 gluOrtho2D (minx-markd, maxx+markd, miny-2.0*markd, maxy+2.0*markd);
 glViewport (BORDER, 2*WindowSizeY3+BORDER, WindowSizeX-2*BORDER,
WindowSizeY3-2*BORDER);
 glCallList (MARK_LIST);
 glCallList (LAGRANGE_LIST);
 /* Do Bezier curva en el tercio medio de la ventana.*/
 glViewport (BORDER, WindowSizeY3+BORDER, WindowSizeX-2*BORDER, WindowSizeY3-
2*BORDER);
 glCallList (MARK_LIST);
 glCallList (BEZIER_LIST);
 /* Hacer curva de spline en el tercio inferior de la ventana. */
 glViewport (BORDER, BORDER, WindowSizeX-2*BORDER, WindowSizeY3-2*BORDER);
 glCallList (MARK_LIST);
 glCallList (SPLINE_LIST);
 glutSwapBuffers ();
}
void interact (void)
/* Esta función obtiene los datos de entrada para que el programa los procese.*/
{
 ifstream points_file;

 /* Abrir archivo de datos. */

 points_file.open ("points.dat", ios::in);
 if (!points_file.is_open())
 {
 cerr << "Archivo de datos 'points.dat' no encontrado." << endl;
  exit (EXIT_FAILURE);
 }

 /* Lea el archivo en matrices, determinando los valores máximos y mínimos. */

 maxx = maxy = -1.0e38;
 minx = miny = 1.0e38;
 while (points_file >> px[number_of_points] >> py[number_of_points])
 {
 if (px[number_of_points] < minx) minx = px[number_of_points];
 if (px[number_of_points] > maxx) maxx = px[number_of_points];
 if (py[number_of_points] < miny) miny = py[number_of_points];
 if (py[number_of_points] > maxy) maxy = py[number_of_points];
 number_of_points++;
 if (number_of_points == MAX_POINTS)
 {
 cout << "Las matrices de datos están llenas. Si hay más datos presentes, no se trazarán."<<endl;
 break;
 }
 }
 points_file.close ();

 /* Determine la longitud de los segmentos de línea para hacer marcas 'x'.*/

 if (maxx-minx > maxy-miny)
 markd = (maxx-minx)/number_of_points * MARK_FACTOR;
 else
 markd = (maxy-miny)/number_of_points * MARK_FACTOR;
}
void mark_points ()
/* Esta rutina hace una marca para cada punto de datos en las matrices. */
{
 int i;

 glNewList(MARK_LIST, GL_COMPILE);
 glColor3f (1.0, 0.0, 0.0); /* Dibuja las marcas en rojo. */
 glBegin (GL_LINES);
 for (i=0; i<number_of_points; i++)
 {
 glVertex2d (px[i] - markd, py[i] - markd);
 glVertex2d (px[i] + markd, py[i] + markd);
 glVertex2d (px[i] - markd, py[i] + markd);
 glVertex2d (px[i] + markd, py[i] - markd);
 }
 glEnd ();
 glEndList ();
}
double B (int n, double t)
/* Evalúa las funciones de fusión para la interpolación de Lagrange. */
{
 switch (n)
 {
 case 1 : return -t*(t-1.0)*(t-2.0)/6.0;
 break;
 case 2 : return (t+1.0)*(t-1.0)*(t-2.0)/2.0;
 break;
 case 3 : return -(t+1.0)*t*(t-2.0)/2.0;
 break;
 case 4 : return (t+1.0)*t*(t-1.0)/6.0;
 break;
 }
 return 0.0; // caso predeterminado, nunca debería suceder
}
void Lagrange_interpolate ()
/* Este procedimiento hace la interpolación de Lagrange de los datos. */
{
 int i;
 double t, x, y, b1, b2, b3, b4;
 char title[] = "Lagrange Interpolation";

 glNewList (LAGRANGE_LIST, GL_COMPILE);
 glColor3f (0.0, 0.0, 0.0); /* Dibuja la curva en negro. */
 glBegin (GL_LINE_STRIP);
 /* Maneje el primer conjunto de 4 puntos entre t = -1 y t = 0 por separado. */

 for (t=-1.0; t<DELTA_T/2.0; t+=DELTA_T)
 {
 b1 = B(1,t);
 b2 = B(2,t);
 b3 = B(3,t);
 b4 = B(4,t);
 x = px[0]*b1 + px[1]*b2 + px[2]*b3 + px[3]*b4;
 y = py[0]*b1 + py[1]*b2 + py[2]*b3 + py[3]*b4;
 glVertex2d (x, y);
 }

 /* Manejar los segmentos medios. */

 for (i=1; i<=number_of_points-3; i++)
 {
 for (t=DELTA_T; t<1.0+DELTA_T/2.0; t+=DELTA_T)
 {
 b1 = B(1,t);
 b2 = B(2,t);
 b3 = B(3,t);
 b4 = B(4,t);
 x = px[i-1]*b1 + px[i]*b2 + px[i+1]*b3 + px[i+2]*b4;
 y = py[i-1]*b1 + py[i]*b2 + py[i+1]*b3 + py[i+2]*b4;
  glVertex2d (x, y);
 }
 }

 /* Maneja el último conjunto de 4 puntos entre t = 1.0 y t = 2.0 por separado. */
 for (t=1.0+DELTA_T; t<2.0+DELTA_T/2.0; t+=DELTA_T)
 {
 b1 = B(1,t);
 b2 = B(2,t);
 b3 = B(3,t);
 b4 = B(4,t);
 x = px[number_of_points-4]*b1 + px[number_of_points-3]*b2 +
 px[number_of_points-2]*b3 + px[number_of_points-1]*b4;
 y = py[number_of_points-4]*b1 + py[number_of_points-3]*b2 +
 py[number_of_points-2]*b3 + py[number_of_points-1]*b4;
 glVertex2d (x, y);
 }
 glEnd ();
 glEndList ();
 /* Representa el título en una lista de visualización. */
 glNewList (LAGRANGE_TITLE_LIST, GL_COMPILE);
 glColor3f (0.0, 0.0, 0.0); /* Draw title in black. */
 for (i=0; i<(int)strlen(title); i++)
 glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, title[i]);
 glEndList();
}
void Bezier ()
/* Esta función aproxima los datos con curvas de Bezier. */
{
 int i, n;
 double ax, bx, cx, dx, ay, by, dy, cy, t, x, y;
 double delta_t = DELTA_T/4.0;
 char title[] = "Bezier Approximation";

 /* Asegurar de que el número de puntos sea uno más que un múltiplo de 3. */

 switch (number_of_points % 3)
 {
 case 0 : px[number_of_points] = px[number_of_points - 1];
 py[number_of_points] = py[number_of_points - 1];
 n = number_of_points + 1;
 break;
 case 1 : n = number_of_points;
 break;
 case 2 : n = number_of_points + 2;
 px[n-1] = px[n-2] = px[number_of_points-1];
 py[n-1] = py[n-2] = py[number_of_points-1];
 break;
  }

 /* Construir curvas de Bezier para cada grupo de cuatro puntos. */

 glNewList (BEZIER_LIST, GL_COMPILE);
 glColor3f (0.0, 0.0, 0.0); /* Dibuja curva en negro. */
 glBegin (GL_LINE_STRIP);
 for (i=0; i<n-1; i+=3)
 {
 ax = -px[i] + 3.0*(px[i+1] - px[i+2]) + px[i+3];
 ay = -py[i] + 3.0*(py[i+1] - py[i+2]) + py[i+3];
 bx = 3.0*(px[i] - 2.0*px[i+1] + px[i+2]);
 by = 3.0*(py[i] - 2.0*py[i+1] + py[i+2]);
 cx = -3.0*(px[i] - px[i+1]);
 cy = -3.0*(py[i] - py[i+1]);
 x = dx = px[i];
 y = dy = py[i];
 glVertex2d (x, y);
 for (t=delta_t; t<1.0+delta_t/2.0; t+=delta_t)
 {
 x = ((ax*t + bx)*t + cx)*t + dx;
 y = ((ay*t + by)*t + cy)*t + dy;
 glVertex2d (x, y);
 }
 }
 glEnd ();
 glEndList ();
 /* Representa el título en una lista de visualización. */
 glNewList (BEZIER_TITLE_LIST, GL_COMPILE);
 glColor3f (0.0, 0.0, 0.0); /* Dibuja el título en negro. */
 for (i=0; i<(int)strlen(title); i++)
 glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, title[i]);
 glEndList();
}
double b (double t)
/* Esta función evalúa la B-spline cúbica uniforme. */
{
 double tp2, tp1, tm2, tm1;

 if (t <= -2.0)
 return 0.0;
 else if (t <= -1.0)
 {
 tp2 = t + 2.0;
 return tp2 * tp2 * tp2 / 6.0;
 }
 else if (t <= 0.0)
 {
 tp2 = t + 2.0;
  tp1 = t + 1.0;
 tp2 = tp2 * tp2 * tp2 / 6.0;
 tp1 = 2.0 * tp1 * tp1 * tp1 /3.0;
 return tp2 - tp1;
 }
 else if (t <= 1.0)
 {
 tm1 = 1.0 - t;
 tm2 = 2.0 - t;
 tm1 = 2.0 * tm1 * tm1 * tm1 / 3.0;
 tm2 = tm2 * tm2 * tm2 / 6.0;
 return tm2 - tm1;
 }
 else if (t <= 2.0)
 {
 tm2 = 2.0 - t;
 return tm2 * tm2 * tm2 / 6.0;
 }
 else
 return 0.0;
}
void spline ()
/* Esta función aproxima los datos con curvas spline. */
{
 double xs[MAX_POINTS+4], ys[MAX_POINTS+4];
 double x, y, t, bt1, bt2, bt3, bt4;
 int i;
 char title[] = "Aproximacion Spline";

 /* Cargar matrices locales con datos y haga que los dos puntos finales sean múltiples para
que
 * Están interpolados.*/

 xs[0] = xs[1] = px[0];
 ys[0] = ys[1] = py[0];
 for (i=0; i<number_of_points; i++)
 {
 xs[i+2] = px[i];
 ys[i+2] = py[i];
 }
 xs[number_of_points+2] = xs[number_of_points+3] = px[number_of_points-1];
 ys[number_of_points+2] = ys[number_of_points+3] = py[number_of_points-1];

 /* Calcule los valores para trazar. */

 glNewList (SPLINE_LIST, GL_COMPILE);
 glColor3f (0.0, 0.0, 0.0); /* Dibuja la curva en negro. */
 glBegin (GL_LINE_STRIP);
 glVertex2d (px[0], py[0]);
 for (i=0; i<=number_of_points; i++)
 for (t=DELTA_T; t<1.0+DELTA_T/2.0; t+=DELTA_T)
 {
 	 bt1 = b(t - 2.0);
 bt2 = b(t - 1.0);
 bt3 = b(t);
 bt4 = b(t + 1.0);
 x = xs[i]*bt4 + xs[i+1]*bt3 + xs[i+2]*bt2 + xs[i+3]*bt1;
 y = ys[i]*bt4 + ys[i+1]*bt3 + ys[i+2]*bt2 + ys[i+3]*bt1;
 glVertex2d (x, y);
 }
 glEnd ();
 glEndList ();
 /* Representa el título en una lista de visualización. */
 glNewList (SPLINE_TITLE_LIST, GL_COMPILE);
 glColor3f (0.0, 0.0, 0.0); /* Draw title in black. */
 for (i=0; i<(int)strlen(title); i++)
 glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, title[i]);
 glEndList();
}

