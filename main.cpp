#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <windows.h>
#include <C:\Users\victor\Documents\CodeBlocs\GLUT\GLUT\include\GL\glut.h>

using namespace std;

#define N 20

void cargaMatriz(int matriz[N][N]);
void pared(int x, int y, int r, int g, int b);
void estado(int x, int y, int tX, int tY);
int matriz[N][N];
int inicio[2] = {0,0};
int salida[2] = {N-1,N-1};
int tx = 0;
int ty = 0;
int v[N][N];
bool Primera_Pasada = true;
GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;

void display(){
	int i;
	int j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (matriz[i][j] == 1)
				pared(j,i,0,0,0);
				else
					pared(j,i,1,1,1);
		}

	}
	estado(inicio[0],inicio[1],tx,ty);
	glFlush();
}

void init(){
	glClearColor(1.0,1.0,1.0,0.0);
}

void cargaMatriz(int matriz[N][N]){
	int i = 0 ;
	int j = 0 ;
	int matriz1[N][N] = {
		    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,1},
			{1,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,1,1,1},
			{1,1,1,0,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0,1},
			{1,1,0,0,0,1,0,1,0,0,1,1,1,1,1,1,1,0,1,1},
			{1,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,1,0,1,1},
			{1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}
	};
	for (i=0;i<N;i++)
		for (j=0;j<N;j++){
			matriz[j][i]=matriz1[j][i];
		}
}

void pared(int x, int y, int r, int g, int b){
	glBegin(GL_QUADS);
	glColor3f(r,g, b);
	glVertex3f(x,y,0.0);
	glVertex3f(x + 1,y,0.0);
	glVertex3f(x + 1,y + 1,0.0);
	glVertex3f(x,y + 1,0.0);
	glEnd();
}


void estado(int x, int y, int tX, int tY){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(X, Y, Z);
	glColor3f(1.0,0.0,0.0);
	glPointSize(15.0f);
	glBegin(GL_POINTS);
	glVertex2f(x +0.5 + tX,y + 0.5 +tY);
	glEnd();
	glTranslatef(tX,tY,0.0f);
	glPopMatrix();
}


void keyboard(unsigned char key, int x, int y){
    //control de teclas que hacen referencia a Escalar y transladar la tetera en los ejes X,Y,Z.
    switch (key){
    case 'x' :
        X += 0.1f;
        break;
    case 'X' :
        X -= 0.1f;
        break;
    case 'y' :
        Y += 0.1f;
        break;
    case 'Y' :
        Y -= 0.1f;
        break;
    case 'z':
        Z += 0.1f;
        break;
    case 'Z':
        Z -= 0.1f;
        break;
    case 'q':
        exit(0);//Exit.
    }
    glutPostRedisplay();
}


void reshape(int width, int height){
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,N,0.0,N,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char ** argv){
	for(int i = 0; i < N; i++){
		for( int j = 0; j < N; j++){
			v[i][j] = 0;
			}
	}
	cargaMatriz(matriz);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow(" Laberinto");
	glutDisplayFunc(display);
	 glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

