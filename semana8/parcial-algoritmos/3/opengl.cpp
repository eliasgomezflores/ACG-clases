#include <iostream>
#include <fstream>
#include <windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

static float u = 0.0;
static char theStringBuffer[10];
static long font = (long)GLUT_BITMAP_8_BY_13;

static float ctrlpoints[4][3] =
    {
        {-40.0, -20.0, 0.0}, {0.0, 40.0, 0.0}, {40.0, -20.0, 0.0}, {0.0, -40.0, 0.0}};

void writeBitmapString(void *font, char *string)
{
    char *c;

    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void floatToString(char *destStr, int precision, float val)
{
    sprintf(destStr, "%f", val);
    destStr[precision] = '\0';
}

void setup(void)
{
    glClearColor(0.83f, 0.913f, 0.839f, 0.0);
}

void drawScene(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    floatToString(theStringBuffer, 4, u);
    glRasterPos3f(-40.0, 40.0, 0.0);
    writeBitmapString((void *)font, "u = ");
    writeBitmapString((void *)font, theStringBuffer);
    writeBitmapString((void *)font, " mover con las fechas del teclado");

    glColor3f(1.0, 0.8, .4);
    glLineWidth(2.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glMapGrid1f(100, 0.0, 1.0);
    glEvalMesh1(GL_LINE, 0, (int)(u * 100));
    glLineWidth(1.0);

    glPointSize(5.0);
    glColor3f(0.07, 0.188, 0.07);
    //los puntos verdes
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    //dibujar las lineas
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();

    //start son los puntos rojos
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 2, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glEvalCoord1f(u);
    glEnd();

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 2, &ctrlpoints[1][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glEvalCoord1f(u);
    glEnd();

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 2, &ctrlpoints[2][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glEvalCoord1f(u);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f((1 - u) * ctrlpoints[0][0] + u * ctrlpoints[1][0],
               (1 - u) * ctrlpoints[0][1] + u * ctrlpoints[1][1]);

    glVertex2f((1 - u) * ctrlpoints[1][0] + u * ctrlpoints[2][0],
               (1 - u) * ctrlpoints[1][1] + u * ctrlpoints[2][1]);

    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f((1 - u) * ctrlpoints[1][0] + u * ctrlpoints[2][0],
               (1 - u) * ctrlpoints[1][1] + u * ctrlpoints[2][1]);

    glVertex2f((1 - u) * ctrlpoints[2][0] + u * ctrlpoints[3][0],
               (1 - u) * ctrlpoints[2][1] + u * ctrlpoints[3][1]);

    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f((1 - u) * ctrlpoints[1][0] + u * ctrlpoints[2][0],
               (1 - u) * ctrlpoints[1][1] + u * ctrlpoints[2][1]);

    glVertex2f((1 - u) * ctrlpoints[2][0] + u * ctrlpoints[3][0],
               (1 - u) * ctrlpoints[2][1] + u * ctrlpoints[3][1]);

    glEnd();

    //aqui estan lospuntos medios

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f((1 - u) * ((1 - u) * ctrlpoints[0][0] - u * ctrlpoints[1][0]) + u * ((1 - u) * ctrlpoints[1][0] + u * ctrlpoints[2][0]),
               (1 - u) * ((1 - u) * ctrlpoints[0][1] + u * ctrlpoints[1][1]) + u * ((1 - u) * ctrlpoints[1][1] + u * ctrlpoints[2][1]));

    glVertex2f((1 - u) * ((1 - u) * ctrlpoints[1][0] + u * ctrlpoints[2][0]) + u * ((1 - u) * ctrlpoints[2][0] + u * ctrlpoints[3][0]),
               (1 - u) * ((1 - u) * ctrlpoints[1][1] + u * ctrlpoints[2][1]) + u * ((1 - u) * ctrlpoints[2][1] + u * ctrlpoints[3][1]));

    glEnd();

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(0.0, 0.0, 0.4); // es la u
    glBegin(GL_POINTS);
    glEvalCoord1f(u);
    glEnd();

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[1][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(0.0, 0.0, 0.4); // es la u
    glBegin(GL_POINTS);
    glEvalCoord1f(u);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(.0, 1.0, 0.4); // es la u
    glBegin(GL_POINTS);
    glEvalCoord1f(u);
    glEnd();
    glutSwapBuffers();
}

void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{

    if (key == GLUT_KEY_LEFT)
        if (u > 0.02)
            u -= 0.02;
    if (key == GLUT_KEY_RIGHT)
        if (u < 0.98)
            u += 0.02;

    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press the left/right arrows to decrease/increase the curve parameter u." << endl;
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("deCasteljau3.cpp");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();

    return 0;
}
// g++ -m32 -Wall -o opengl.out opengl.cpp -L"C:\MinGW\lib" -lglu32 -lglut32 -lopengl32 -lstdc++