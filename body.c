//#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <math.h>

#define BODY_HEIGHT 5.0
#define BODY_WIDTH 3.0
#define BODY_LENGTH 3.0

#define ARM_HEIGHT 3.5
#define ARM_WIDTH 1.0
#define ARM_LENGTH 1.0

/*
AMBAS FUNCIONAN
FreeGLUT es una librería que surgió en un principio para mejorar 
algunos aspectos de GLUT. Actualmente es un reemplazo total de esta. 
El último update de GLUT fue hace más de 10 años! Por otro lado, FreeGLUT 
tiene una versión estable desde el 2009 y actualmente la versión 2.8.1 es 
Stable Release (Abril 2013).*/

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	/*Se agrega el GL_DEPTH_BUFFER_BIT, para inicializar
	el Z-Buffer*/
	glColor3f(1.0,0.0,0.0);

	//glTranslatef(0.0, 0.0, -1.0);
	/*Alejamos la figura del observador en una unidad en el eje Z-.
	Sirve para gluPerspective*/

	glTranslatef(0.0, 0.0, -12.0);
	//Alejamos la camará para dibujar un humanoide

	glTranslatef(0, BODY_HEIGHT/2,0);
	glPushMatrix();
		glScalef(BODY_WIDTH, BODY_HEIGHT, BODY_LENGTH);
		glColor3f(0.0,0.6,0.3);
		glutSolidCube(1);
	glPopMatrix();

	// Dibujamos el brazo derecho
  glPushMatrix();
     glTranslatef(-(BODY_WIDTH)/2,(BODY_HEIGHT-ARM_HEIGHT)/2,0);
     glTranslatef(0,ARM_HEIGHT/2,0);
     glRotatef(-30,0,0,1);
     glTranslatef(0,-ARM_HEIGHT/2,0);
     glPushMatrix();
       glScalef(ARM_WIDTH,ARM_HEIGHT,ARM_LENGTH);
       glutSolidCube(1);
     glPopMatrix();
     // ya tenemos el brazo... la mano
     glTranslatef(0,-(ARM_HEIGHT+ARM_WIDTH)/2,0);
     glColor3f(1,0.6,0.6);
     glScalef(ARM_WIDTH,ARM_WIDTH,ARM_LENGTH);
     glutSolidCube(1);
  glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(600,600);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Jugando con GLUT");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0,0,500,500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	/*Proyección ortográfica, dentro del cubo señalado
		Normalmente la parte superior de la figura esta más
		alejada del observador, que la inferior. Sin embargo
		en la proyección ortográfica no lo muestra.  Es por
		eso que si queremos observar esto, debemos cambiar 
		a perspective.

		Cuando visualizamos un espacio, podemos usar:

		-Proyección ortográfica
			Visualizamos todo lo que se encuentra dentro del 
			cubo, el mismo está delimitado en los parámetros 
			de glOrtho.

		-Proyección perspectiva
			Esta proyección delimita un volúmen de visualización
			dado por un ángulo de cámara, y una relación ancho/alto.

	*/
	

	gluPerspective(80.0, 1.0, 1.0, 100.00);
	/*Y... no se verá nada, a menos que tomemos en cuenta al
	observador.  Cuando usamos perspective, es la posición del
	observador la que determina cómo se ven las cosas.  Por
	defaul está en la posición (0,0.0).  Entonce debemos alejar
	la figura del observador, sino se dibujara en el mismo lugar
	y no verá nada xD, para esto usamos glTranslate*/
	//gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	//glMatrixMode(GL_MODELVIEW);
     // Modo de modelado
	//glShadeModel(GL_FLAT); //Aparece el último color asignado a la figura.
	glShadeModel(GL_SMOOTH); //Así se mezclan los colores.

	glDepthFunc(GL_LEQUAL);
	/*Habilita la comprobaciób de la profundidad en el dibujado*/
	glEnable(GL_DEPTH_TEST); 
	/*Habilita la comprobación de la profundidad en el dibujado*/
	glClearDepth(1.0);
	/*Indicamos que cada vez que se borre el buffer, inicialice las
	posiciones al valor 1.0*/

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}