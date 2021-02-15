//Ejercicio 3. Ejercicios propuestos
//3. Genere el siguiente escalado:
#include<windows.h>
#include<GL/glut.h>

void inicio( ){
 glMatrixMode(GL_PROJECTION);//pantalla como una matriz	
 glColor3f(0.0 ,0.8 ,1.0 );
 glLoadIdentity();
 
 glOrtho(120,-120,120,-120,50,-50); //tama�o de la camARA, EL ANGULO, la lejania
 glClearColor(250.0,250.0,250.0,250.0); // color del fondo de la ventana 

 glMatrixMode(GL_MODELVIEW); 
 glLoadIdentity(); 

}

void pantalla(){
 glClear(GL_COLOR_BUFFER_BIT);//limpiar la ventana


glPushMatrix();
	//crear ala izquierda
	glBegin(GL_POLYGON);
	glColor3f(1.0 ,0.0 ,1.0);//color del punto
	glVertex2i(50, 20);
	glVertex2i(50,50);
	glVertex2i(80,50);
	glEnd();
	//crear ala derecha
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0, 0.0);//color del punto
	glVertex2i(47, 10);
	glVertex2i(17,50);
	glVertex2i(47,50);
	glEnd();
	
	//crear asta
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);//color del punto
	glVertex2i(47.5,5);
	glVertex2i(49,5);
	glVertex2i(49,54);
	glVertex2i(47.5,54);
	glVertex2i(47.5,5);
	glEnd();
	
	//crear barc8
	glBegin(GL_POLYGON);
	glColor3f(0.0 ,1.0, 1.0);//color del punto
	glVertex2i(27,75);
	glVertex2i(12,55);
	glVertex2i(85,55);
	glVertex2i(70,75);
	glVertex2i(27,75);
	glEnd();

glPopMatrix();


glPushMatrix();
glTranslatef(-100.7f,0.0f,0.0f); //X,Y,Z
//crear ala izquierda
	glBegin(GL_POLYGON);
	glColor3f(1.0 ,0.0 ,1.0);//color del punto
	glVertex2i(50, 20);
	glVertex2i(50,50);
	glVertex2i(80,50);
	glEnd();
	//crear ala derecha
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0, 0.0);//color del punto
	glVertex2i(47, 10);
	glVertex2i(17,50);
	glVertex2i(47,50);
	glEnd();
	
	//crear asta
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);//color del punto
	glVertex2i(47.5,5);
	glVertex2i(49,5);
	glVertex2i(49,54);
	glVertex2i(47.5,54);
	glVertex2i(47.5,5);
	glEnd();
	
	//crear barc8
	glBegin(GL_POLYGON);
	glColor3f(0.0 ,1.0, 1.0);//color del punto
	glVertex2i(27,75);
	glVertex2i(12,55);
	glVertex2i(85,55);
	glVertex2i(70,75);
	glVertex2i(27,75);
	glEnd();

glPopMatrix();

glFlush(); 
	
}

int main(int argc, char *argv[]){
 glutInit(&argc,argv); //inicializar GLUT
 glutCreateWindow("Escala de Ampliacion"); //crea ventana
 glutInitWindowSize(400,200); // tama�o de la ventana
 glutInitWindowPosition(300,100); // posiciona la ventana
 glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE); // colores RGB y Un solo Buffer
 inicio();
 glutDisplayFunc(pantalla);
 glutMainLoop(); // permite que el proceso se repita hasta que el usuario cierre ventana.	
 return EXIT_SUCCESS;
}
