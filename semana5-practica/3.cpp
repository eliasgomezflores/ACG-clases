#include <GL/glut.h>
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

 GLfloat angleSegund = 0.0;
 GLfloat angleMinut = 0.0;
 GLfloat angleHours = -210.0;
 int hours = 7, mint = 0, seconds = 0;

void lines2f( float x0, float y0, float x1, float y1, GLfloat red, GLfloat green, GLfloat blue ){
    
    glBegin( GL_LINES );
    glColor3f( red, green, blue );
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

void rotateLines2f( GLfloat angulo,  float x0, float y0, float x1, float y1, GLfloat red, GLfloat green, GLfloat blue){
    glPushMatrix();
    glRotatef( angulo, .0, .0, .1 );
    lines2f( x0 , y0, x1, y1, red, green, blue);
    glPopMatrix();
}

void watch(double radio, double a, double b){
    circle( radio, a, b );
    lines2f( .0, .45, .0, .55, .5,.5,.5 );
    lines2f( .0, -.45, .0, -.55, .5,.5,.5 );
    lines2f( .45, 0, .55, .0, .5,.5,.5 );
    lines2f( -.45, 0, -.55, .0, .5,.5,.5 );
    rotateLines2f( -30,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( -60,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( -120,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( -150,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( 30,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( 60,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( 120,  .0, .45, .0, .55, .8, .8, .8);
    rotateLines2f( 150,  .0, .45, .0, .55, .8, .8, .8);

    for ( int i = 6; i < 360; i += 6 ){
        if( (i % 30) != 0 ){
            rotateLines2f( (float) i,  .0, .48, .0, .52, .8, .0, .8);
        }
    }


}

void rotateLines2f(){
        // glRotatef( angleHours, .0, .0, .1 );
        // lines2f(.0, .0, .0, .3);//horario
        // glRotatef( angleMinut, .0, .0, .1 );
        // lines2f(.0, .0, .0, .5);//minutero
        // glRotatef( angleSegund, .0, .0, .1 );
        // lines2f(.0, .0, .0, .5);//segundero

        rotateLines2f( angleHours, .0, .0, .0, .3, 1, .0, .0);
        rotateLines2f( angleMinut, .0, .0, .0, .5, .0, 1, .0 );
        rotateLines2f( angleSegund, .0, .0, .0, .5, .0, .0, 1 );

}

void display(){
    glClear( GL_COLOR_BUFFER_BIT );
    watch( 0.5, .0, .0);
    rotateLines2f();
    glFlush();
    // glutSwapBuffers();
}

void idleFunc(){

    angleSegund --;
    seconds ++;
    if ( angleSegund == -360 ){
        
        angleSegund = 0;
        angleMinut += -6;
        angleHours += -0.5;

    }

    // if ( seconds == 60 ){
    //     mint ++;
    //     seconds = 0;
    // }

    // if ( mint == 60 ){
    //     hours ++;
    //     mint = 0;
    // }

    // if ( hours == 12 ){
    //     hours = 0;
    // }

    // cout<<"TIME --> "<< hours <<" : "<<mint<<" : " <<seconds<<endl;

    // if ( angleSegund == -360 ){
    //     angleMinut --;
    //     angleSegund = 0;
    // }

    // if ( angleMinut == 360 ){
    //     angleHours ++;
    //     angleMinut = 0;
    // }

    // if ( angleHours == 12 ){
    //     angleHours = 0;
    // }

    // seconds++;

    

    // angleMinut = -1;
    // angleHours = -0.083;

    // if ( angleMinut <= -360 )
    //     angleMinut = 0.0;
    
    // if ( angleHours <= -360 )
    //     angleHours = 0.0;

    // Sleep( 10 );
    glutPostRedisplay();
    // display();
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