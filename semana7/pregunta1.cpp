#include <GL\glut.h> 
#include <Math.h> 
void init (void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( 0, 100, 0, 100);
}
void lines3f(){

    glColor3f (1.0, 1.0, 0.0);
	glRotatef( 20, 0, 0, 1 );
    glBegin( GL_LINE_LOOP );

        glVertex2f(50, 18);
        glVertex2f(61, 37);
        glVertex2f(83, 43);
        glVertex2f(69, 60);
        glVertex2f(71, 82);
        glVertex2f(50, 73);
        glVertex2f(29, 82);
        glVertex2f(31, 60);
        glVertex2f(17, 43);
        glVertex2f(39, 37);
    glEnd();
}
void display(void){
	glClear (GL_COLOR_BUFFER_BIT);	
	lines3f();
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
