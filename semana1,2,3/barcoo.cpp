//Ejercicio 3. Ejercicios propuestos
//3. Genere el siguiente escalado:
#include<windows.h>
#include<GL/glut.h>

void inicio( ){
 glMatrixMode(GL_PROJECTION);//pantalla como una matriz	
 glColor3f(0.0 ,0.8 ,1.0 );
 glLoadIdentity();
 
 glOrtho(120,-120,120,-120,50,-50); //tamaño de la camARA, EL ANGULO, la lejania
 glClearColor(250.0,250.0,250.0,250.0); // color del fondo de la ventana 

 glMatrixMode(GL_MODELVIEW); 
 glLoadIdentity(); 

}

void pantalla(){
	int angulo=0;
for(angulo=0;angulo<360;angulo++){
	
 glClear(GL_COLOR_BUFFER_BIT);//limpiar la ventana
glPushMatrix();
	glRotated(angulo,0,0,1);
	//crear ala izquierda
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);//color del punto
	glVertex2i(50, 20);
	glVertex2i(50,50);
	glVertex2i(80,50);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);//color del punto
	glVertex2i(50, 20);
	glVertex2i(50,50);
	glVertex2i(80,50);
	glEnd();
glPopMatrix();
glFlush();
if(angulo==359){
	angulo=-1;
} 
}	
}

int main(int argc, char *argv[]){
 glutInit(&argc,argv); //inicializar GLUT
 glutCreateWindow("Escala de Ampliacion"); //crea ventana
 glutInitWindowSize(400,200); // tamaño de la ventana
 glutInitWindowPosition(300,100); // posiciona la ventana
 glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE); // colores RGB y Un solo Buffer
 inicio();
 glutDisplayFunc(pantalla);
 glutMainLoop(); // permite que el proceso se repita hasta que el usuario cierre ventana.	
 return EXIT_SUCCESS;
}
