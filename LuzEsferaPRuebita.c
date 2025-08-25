#include <GL/glut.h>

/*
	Definición de variables a fin de almacenar las 
	propiedades tanto de iluminación, como de materiales
	y rotación.

	light_ambient, light_diffuse_specular, light_pos, spot_dir, etc. 
	definen las características de la luz.

	mat_ambient_diffuse, mat_specular, etc. definen las propiedades 
	del material de la esfera.

	rot_angle_y y rot_angle_x controlan la rotación.
*/
#define ROT 1.0
float light_ambient [] = {0.0,0.2,0.0,1.0};
float light_diffuse_specular [] = {0.8,0.8,0.8,1.0};
float light_pos [] = {0.0,0.0,2.0,1.0};
float spot_dir [] = {0.0,0.0,-1.0};
float spot_cutoff = 30.0;
float spot_exponent = 1.0;
float mat_ambient_diffuse [] = {0.0,0.0,1.0,1.0};
float mat_specular [] = {0.7,0.0,0.0,1.0};
float mat_emission [] = {0.0,0.0,0.0,1.0};
float mat_shininess = 0.4;
float focus_emission [] = {0.8,0.8,0.8,1.0};
float rot_angle_y = 0.0;
float rot_angle_x = 0.0;

/*
  Inicializamos OpenGL, habilitando la prueba de profundidad
  (GL_DEPTH_TEST) a fin de renderizar de manera correcta en 3D.

  Establecemos el color de fondo, se configura el model de
  iluminación, se definen las priopiedades de la luz, del material.

  Se configura la matriz de proyección y la de vista.
*/
void iniciogl()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0,0.0,0.0,0.0);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse_specular);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light_diffuse_specular);
  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,spot_cutoff);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,spot_exponent);
  glEnable(GL_LIGHT0);
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_ambient_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT,GL_SHININESS,mat_shininess);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0,1.0,1.0,100.0);
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0,0.0,-5.0);
}

/*
  Función para crear la animación, en ella se incrementan los
  ángulos de rotacion, y se llama glutPostRedisplay() para 
  indicar que la escena debe ser redibujada.

*/
void redibujo(void)
{
  rot_angle_y = (rot_angle_y > 360.0)?0:rot_angle_y + ROT;
  rot_angle_x = (rot_angle_x > 360.0)?0:rot_angle_x + ROT/(2*3.1416);
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
    glRotatef(30.0,0.0,0.0,1.0);
    glRotatef(rot_angle_y,0.0,1.0,0.0);
    glRotatef(rot_angle_x,1.0,0.0,0.0);

    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_dir);

    glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
    glColorMaterial(GL_FRONT,GL_EMISSION);
    glEnable(GL_COLOR_MATERIAL);
    glColor4fv(focus_emission);
    glutSolidSphere(0.2,7,7);
    glColor4fv(mat_emission);
    glDisable(GL_COLOR_MATERIAL);
  glPopMatrix();
  glutSolidSphere(1.0,20,20);
  glFlush();
  glutSwapBuffers();
}

int main(int argc, char ** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(30,30);
  glutInitWindowSize(500,500);
  glutCreateWindow("Lunita");
  iniciogl();
  glutDisplayFunc(display);
  glutIdleFunc(redibujo);
  glutMainLoop();
  return 0; 
}