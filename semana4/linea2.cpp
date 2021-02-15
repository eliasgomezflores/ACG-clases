#include<GL/gl.h>
#include<GL/glu.h>
#include<stdlib.h>
#include<GL/glut.h>
GLfloat ctrlpoints[4][4][3]={
{{-1.5,-1.5,4.0},{-0.5,-1.5,2.0},{0.5,-1.5,-1.0},{1.5,-1.5,2.0}},
{{-1.5,-0.5,1.0},{-0.5,-0.5,3.0},{0.5,-0.5,0.0},{1.5,-0.5,-1.0}},
{{-1.5,0.5,4.0},{-0.5,0.5,0.0},{0.5,0.5,3.0},{1.5,0.5,4.0}},
{{-1.5,1.5,-2.0},{-0.5,1.5,-2.0},{0.5,1.5,0.0},{1.5,1.5,-1.0}}
};
void pantalla(void){
int i,j;
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glColor3f(1.0,1.0,1.0);
glRotatef(60.0,1.0,1.0,1.0);
for(j=0;j<=9;j++){
glBegin(GL_LINE_STRIP);
for(i=0;i<=30;i++)
 glEvalCoord2f((GLfloat)i/30.0,(GLfloat)j/9.0);
 glColor3f(0.2,0.4,0.8);
glEnd();
glBegin(GL_LINE_STRIP);
for(i=0;i<=30;i++)
 glEvalCoord2f((GLfloat)j/9.0,(GLfloat)i/30.0);
 glColor3f(0.6,0.2,0.8);
glEnd();
}
glFlush();
}
void reestructura(int w,int h){
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if(w<=h)
 glOrtho(-5.0,5.0,-5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w,-5.0,5.0);
else
 glOrtho(-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h,-5.0,5.0,-5.0,5.0);
glMatrixMode(GL_MODELVIEW);
}
void inicio(void){
glClearColor(0.0,0.0,0.0,0.0);
glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,0,1,12,4,&ctrlpoints[0][0][0]);
glEnable(GL_MAP2_VERTEX_3);
glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
glEnable(GL_DEPTH_TEST);
glShadeModel(GL_FLAT);
}
int main(int argc, char** argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow(argv[0]);
inicio();
glutDisplayFunc(pantalla);
glutReshapeFunc(reestructura);
glutMainLoop();
return 0;
}
