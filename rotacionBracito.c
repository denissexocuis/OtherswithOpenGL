#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double VectorGlobal[4] = {100,100,0,1};
double center[2] = {250,250};


typedef struct  {
  double posicion[4];
  double matriz[4][4];
}body;

//Multiplicacion de una matrix 4x4 por un vector de longitud 4
//salida en vector c
void Matriz_X_Vector(double matrix[4][4],  double vector[4], double *c)
{
  int i;

  for (i = 0; i < 4; i++)
      c[i] = matrix[i][0] * vector[0] +
             matrix[i][1] * vector[1] +
             matrix[i][2] * vector[2] +
             matrix[i][3] * vector[3];
} 

//Funcion para Rotar el punto definido por el vector (X,Y,Z,1) en un angulo angle
void rotar(double *vector, double angle)
{
  int i;
  double seno = sin(angle);
  double coseno = cos(angle);
  
  double vectortemp[4]; 

  double matrizRot[4][4] = {{coseno, -seno, 0, 0},
			    {seno,  coseno, 0, 0},
			    {   0,       0, 1, 0},
			    {   0,       0, 0, 1}};

  Matriz_X_Vector(matrizRot,vector,vectortemp);
  
  for(i=0; i<4; i++)
    vector[i]=vectortemp[i];
}

// Funcion para transladar el vector con salida en el vector vectorout 
void transladar(double *vector, double *vectorout)
{

  double matrizTrans[4][4] = {{1, 0, 0, center[0]},
			      {0, 1, 0, center[1]},
			      {0, 0, 1, 0},
			      {0, 0, 0, 1}};

  Matriz_X_Vector(matrizTrans,vector,vectorout);
}

//Valores de inicio
static void init01(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0); 
   glShadeModel (GL_FLAT); 
}
//
static void display01(void)
{
  double vectortemp[4]; 
  transladar(VectorGlobal,vectortemp);
  glClear(GL_COLOR_BUFFER_BIT); //limpiar ventana en el color del clear color definido en glClearColor()
   //glColor3f(1.0,0.0,0.0); // Color del dibujo en rojo
  glColor3f(0.,0.,0.);//Negro
  
  
  glPushMatrix();
    //El primer segmento del brazo
    glBegin(GL_LINES); //se define que se dibujaran lineas
      glVertex3f(center[0], center[1], 0) ; //primer punto para dibujar
      //glVertex3f(0, 0, 0) ;
      //glVertex3f(VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
      glVertex3f(vectortemp[0], vectortemp[1], vectortemp[2]); // segundo punto de la linea
    glEnd();
    //el segundo segmento Tarea para ustedes.
    
   /*  glBegin(GL_LINES); 
      glVertex3f(vectortemp[0], vectortemp[1], vectortemp[2]); //primer punto donde termina el otro
      glVertex3f(200, 100, 0);//esto hay que cambiarlo
    glEnd(); */


  glPopMatrix();
   
  glFlush ();
  glutSwapBuffers();
  glutPostRedisplay();//refrescar la ventana
}



// se llama cuando la ventana cambia de tamaño
static void reshape01(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION); 
   glLoadIdentity (); 
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}



//Uso del teclado
static void keyboard01(unsigned char key, int x, int y)
{
   if((key == 0x1b)||(key == 'q')||(key == 'Q'))
      exit(0); // terminar programa
   else
     if ((key=='R') || (key == 'r'))//Rotar
       {
	       printf("Vector Inicial %f, %f, %f\n",VectorGlobal[0], VectorGlobal[1],VectorGlobal[2]);
	       rotar(VectorGlobal, -.1);
	       printf("Vector final %f, %f, %f\n",VectorGlobal[0], VectorGlobal[1],VectorGlobal[2]);
       }
   glutSwapBuffers();
   glutPostRedisplay();//refrescar
}


void displayCall();


int main(int argc, char *argv[]) {


  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(300, 200);
  glutCreateWindow("Rotar Bracito");

  init01();

  const GLubyte* renderer = glGetString(GL_RENDERER); // obtener la cadena de renderizado
  const GLubyte* version = glGetString(GL_VERSION); 

  /* printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version); */

  glutDisplayFunc(display01);
  glutReshapeFunc(reshape01);
  glutKeyboardFunc(keyboard01);
  glutMainLoop();
  return 0;
} 

void displayCall() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glutSwapBuffers();
} 

