#include <GL/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);

	glTranslatef(0.0, 0.0, -1.0);

	//glTranslatef(0.0, 0.0, -0.5);
	
	glBegin(GL_QUADS);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
	glEnd();
	

	glBegin(GL_TRIANGLES);
     // Dibujamos un triángulo
		glColor3f(0.0, 1.0, 0.0);
       	glVertex3f(0.0,0.8,0.0);
       	// Coordenadas del primer vértice
       	glColor3f(0.0,0.0,1.0);
       	glVertex3f(-0.6,-0.2,0.0);
       	// Coordenadas del  segundo vértice
       	glColor3f(1.0,0.0,0.0);
       	glVertex3f(0.6,-0.2,0.0);
       	// Coordenadas del  tercer vértice
     glEnd();
     // Terminamos de dibujar

     /*glBegin(GL_QUADS);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
	glEnd();*/

	/*
	GL_POLYGON
	
	GL_TRIANGLE_FAN
	GL_TRIANGLE_STRIP

	*/

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(600,600);
	glutInitWindowPosition(300,200);
	glutCreateWindow("Mi ventanota");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0,0,500,500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//
	//glOrtho(1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	gluPerspective(80.0, 1.0, 1.0, 100.00);
	//gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
     // Modo de modelado
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}












