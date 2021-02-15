#include <GL\glut.h> 
#include <Math.h> 

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( 0, 250, 0, 250);
}

void lines3f(){

    glBegin( GL_LINE_LOOP );
    glColor3f (0.0, 0.0, 0.0);

        glVertex2f( 10, 10 );
        glVertex2f( 10, 100 );
        glVertex2f( 210, 100 );
        glVertex2f( 210, 10 );

    glEnd();

    glBegin( GL_LINE_LOOP );

        glVertex2f( 10, 80 );
        glVertex2f( 50, 80 );
        glVertex2f( 50, 20 );
        glVertex2f( 10, 20 );

    glEnd();

    glBegin( GL_LINE_LOOP );

        glVertex2f( 10, 70 );
        glVertex2f( 30, 70 );
        glVertex2f( 30, 30 );
        glVertex2f( 10, 30 );

    glEnd();

    glBegin( GL_LINES );

        glVertex2f( 110, 100 );
        glVertex2f( 110, 10 );

    glEnd();

    //derecha

    glBegin( GL_LINE_LOOP );

        glVertex2f( 210, 20 );
        glVertex2f( 210, 80 );
        glVertex2f( 170, 80 );
        glVertex2f( 170, 20 );

    glEnd();

    glBegin( GL_LINE_LOOP );

        glVertex2f( 210, 30 );
        glVertex2f( 210, 70 );
        glVertex2f( 190, 70 );
        glVertex2f( 190, 30 );

    glEnd();



}

void guads2f(  float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3,  float red, float green, float blue  ){

    glColor3f( red, green, blue );
	glBegin( GL_QUADS );

	glVertex2f( x0, y0 );
	glVertex2f( x1, y1 );
	glVertex2f( x2, y2 );
	glVertex2f( x3, y3 );

	glEnd();

}

void point2f( float x0, float y0 ){

    glColor3f (0.0, 0.0, 0.0);
    glPointSize(5);
    glBegin( GL_POINTS );

        glVertex2f( x0, y0 );

    glEnd();

}
void point2d(double x, double y)
{
    glColor3f (0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f ( x, y);
	glEnd();
}

void circle360(double radio, double a, double b)
{
	//radio = sqrt( pow(( 0. - a ),2) + pow(( 0.5 - b ),2) ) ;
	double x;
	double y;
	for(double t = 0 ; t < 360; t+=0.01){
		
		x = a + radio * cos(t*3.14159265/180.0);
		y = b + radio * sin(t*3.14159265/180.0);
		
		//x = a + radio * cos(t);
		//y = b + radio * sin(t);
		
		point2d( x, y );
		
	}
}
void circle180(double radio, double a, double b)
{
	//radio = sqrt( pow(( 0. - a ),2) + pow(( 0.5 - b ),2) ) ;
	double x;
	double y;
	for(double t = 0 ; t < 180; t+=0.01){
		
		x = a + radio * cos(t*3.14159265/180.0);
		y = b + radio * sin(t*3.14159265/180.0);
		
		//x = a + radio * cos(t);
		//y = b + radio * sin(t);
		
		point2d( x, y );
		
	}
}
void display(void){

	glClear (GL_COLOR_BUFFER_BIT);
	
	// lines3f();
    guads2f( 10, 10, 10, 100, 210, 100, 210, 10, 0, 1, 0 );
    guads2f( 10, 30, 30, 30, 30, 70, 10, 70, 1, 1, 1 );
    guads2f( 210, 30, 210, 70, 190, 70, 190, 30, 1, 1, 1 );
    lines3f();
    circle360(10, 110, 50);
    glPushMatrix();
        glRotatef(-90, 0, 0, 1);
        glTranslatef( -100, 0, 0);
        circle180(8, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glTranslatef( 50, -170, 0);
        circle180(8, 0, 0);
    glPopMatrix();
    point2f( 180, 50 );
    point2f( 40, 50 );

	glFlush ();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize (600, 500);
	glutInitWindowPosition (200, 100);
	glutCreateWindow ("PRACTICA 1");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
// g++ -m32 -Wall -o primitivasgraficas.out primitivasgraficas.cpp -L"C:\MinGW\lib" -lglu32 -lglut32 -lopengl32 -lstdc++