#include <GL/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
GLfloat angulo = 0.0;
void init(void){
GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv (GL_LIGHT0, GL_POSITION, light_position);
glEnable (GL_LIGHTING);
glEnable (GL_LIGHT0);
glShadeModel(GL_SMOOTH);
glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
glClearDepth(1.0f);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void display(void)
{
GLfloat mat_ambient[] = {0.2, 0.05, 0.05, 1.0f};
GLfloat mat_diffuse[] = { 0.7, 0.0, 0.0, 1.0f};
GLfloat mat_specular[] = {0.9, 0.4, 0.4, 1.0f};
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glTranslatef(0.0f,0.0f,-6.0f);
glRotatef(angulo, 0.0f, 1.0f, 0.0f);
glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
glutSolidIcosahedron();
glFlush ();
glutSwapBuffers();
}
void reshape (int width, int height)
{
if (height==0)
{
height=1;
}
glViewport(0,0,width,height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
switch (key)
 {
 case 27: exit(0);
 break;
 }
}
void Idle(void)
{
angulo += 5.0;
display();
}
int main(int argc, char** argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize (300, 300);
 glutInitWindowPosition (0, 0);
 glutCreateWindow ("Rotacion 3D");
 init ();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutIdleFunc(Idle);
 glutMainLoop();
 return 0;
}
