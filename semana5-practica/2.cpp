#include <GL/glut.h>
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

 GLfloat angleMinut = 0.0;
 GLfloat angleHours = 0.0;

void lines2f( float x0, float y0, float x1, float y1 ){
    
    glBegin( GL_LINES );
    glVertex2f( x0, y0 );
    glVertex2f( x1, y1 );
    glEnd();

}

void point(double x, double y)
{
	glBegin(GL_POINTS);
	glVertex2f ( x, y);
	glEnd();
}

void circle(double radio, double a, double b)
{
	//radio = sqrt( pow(( 0. - a ),2) + pow(( 0.5 - b ),2) ) ;
	double x;
	double y;
	for(double t = 0 ; t < 360; t+=0.01){
		
		x = a + radio * cos(t*3.14159265/180.0);
		y = b + radio * sin(t*3.14159265/180.0);
		
		point( x, y );
		
	}
}

void rotateLines2f(){
    // glPushMatrix();
        glRotatef( angleMinut, .0, .0, .1 );
        lines2f(.0, .0, .0, .5);
        glRotatef( angleHours, .0, .0, .1 );
        lines2f(.0, .0, .0, .3);
    // glPopMatrix();
}

void display(){
    glClear( GL_COLOR_BUFFER_BIT );
    circle( 0.5, .0, .0);
    rotateLines2f();
    glFlush();
    glutSwapBuffers();
}

void idleFunc(){
    
    angleMinut -= 6;
    angleHours -= 10;

    if( angleMinut >= 60 ){
        angleHours = 0.0;
    }

    Sleep( 2000 );
    display();
}
// void keyInput(unsigned char key, int x, int y){
//     cout<<key<<" "<<x<<" "<<y<<" "<< GLUT_KEY_LEFT<<"\n";
// }
// void specialKeyInput(int key, int x, int y){

//     // cout<<key<<" "<<x<<" "<<y<<" "<<GLUT_KEY_LEFT<<" "<<GLUT_KEY_RIGHT<<"\n";
    

//     if(key == GLUT_KEY_LEFT)
//       angle += 5.0;
//     // if(key == GLUT_KEY_RIGHT)
//     //   angle -= 5.0;
// cout<<angle<<"\n";
//     glutPostRedisplay();

// }

int main( int argc, char **argv ){
    glutInit( &argc, argv );
    // glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("practica");
    glutDisplayFunc(display);
    // glutKeyboardFunc(keyInput);

    glutIdleFunc( idleFunc );
    // glutSpecialFunc(specialKeyInput);
    glutMainLoop();
    return 0;
}
