#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// Variables globales
double rotate_y=0;
double rotate_x=0;

void display()
{
	// Borrar pantalla y Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// Resetear transformaciones
	glLoadIdentity();

	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );

	//LADO FRONTAL: lado multicolor
	glBegin(GL_POLYGON);

		glColor3f( 1.0, 0.0, 0.0 ); 
		glVertex3f( 0.5, -0.5, -0.5 ); // P1 es rojo
		
		glColor3f( 0.0, 1.0, 0.0 ); 
		glVertex3f( 0.5, 0.5, -0.5 ); // P2 es verde
		
		glColor3f( 0.0, 0.0, 1.0 ); 
		glVertex3f( -0.5, 0.5, -0.5 ); // P3 es azul
		
		glColor3f( 1.0, 0.0, 1.0 ); 
		glVertex3f( -0.5, -0.5, -0.5 ); // P4 es morado

	glEnd();

	// LADO TRASERO: 
	glBegin(GL_POLYGON);

		glColor3f( -1.0, 1.0, -1.6 ); // color de la cara o tapa
		glVertex3f( 0.5, -0.5, 0.5 );
		glVertex3f( 0.5, 0.5, 0.5 );
		glVertex3f( -0.5, 0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );

	glEnd();

	// LADO DERECHO:
	glBegin(GL_POLYGON);
		glColor3f( 1.0, 0.5, 0.1 ); // color de la cara o tapa
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5, 0.5, -0.5 );
		glVertex3f( 0.5, 0.5, 0.5 );
		glVertex3f( 0.5, -0.5, 0.5 );
	glEnd();

	// LADO IZQUIERDO: 
	glBegin(GL_POLYGON);
		glColor3f( 1.0, -2.8, 1.0 ); // color de la cara o tapa
		glVertex3f( -0.5, -0.5, 0.5 );
		glVertex3f( -0.5, 0.5, 0.5 );
		glVertex3f( -0.5, 0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	// LADO SUPERIOR: 
	glBegin(GL_POLYGON);
		glColor3f( 1.0, -4.0, -1.0 ); // color de la cara o tapa
		glVertex3f( 0.5, 0.5, 0.5 );
		glVertex3f( 0.5, 0.5, -0.5 );
		glVertex3f( -0.5, 0.5, -0.5 );
		glVertex3f( -0.5, 0.5, 0.5 );
	glEnd();
	// LADO INFERIOR: 
	glBegin(GL_POLYGON);
		glColor3f( 1.0, -3.8, -1.0); // color de la cara o tapa
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5, -0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	//glFlush(); 
	glutSwapBuffers(); 
}


void keyboard01( int key, int x, int y )
{
	// La flecha derecha: incrementa su rotación en 5 grados
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;
	// La flecha izquierda: disminuye su rotación en 5 grados
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;
	else if (key == GLUT_KEY_UP)
		rotate_x += 5;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
  	glutInitWindowPosition(300, 200);
	glutCreateWindow("Cubito");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display); 
	glutSpecialFunc(keyboard01);
	glutMainLoop();
	return 0;
}

