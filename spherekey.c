#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h>
#define ROT_INC 1.0
float rot_angle_y = 0.0;
float rot_angle_x = 0.0;
int windowed = 1;
void specialKeys(int key, int x, int y)
{
switch (key)
{
case GLUT_KEY_UP: rot_angle_x--;
break;
case GLUT_KEY_DOWN: rot_angle_x++;
break;
case GLUT_KEY_RIGHT: rot_angle_y++;
break;
case GLUT_KEY_LEFT: rot_angle_y--;
break;
}
glutPostRedisplay();
}
static void keys(unsigned char key, int x, int y)
{
switch (key)
{
case 27: exit(0);
break;
case 'f': if (windowed == 1)
{glutFullScreen(); windowed = 0;}
else{
glutPositionWindow(20,20);
glutReshapeWindow(350,350);
windowed = 0;
}
break;
}
glutPostRedisplay();
}
static void display(void)
{
float light_pos [] = {0.0,0.0,2.0,1.0};
float spot_dir [] = {0.0,0.0,-1.0};
float mat_emission [] = {0.0,0.0,0.0,1.0};
float focus_emission [] = {0.8,0.8,0.8,1.0};
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glRotatef(rot_angle_y,0.0,1.0,0.0);
glRotatef(rot_angle_x,1.0,0.0,0.0);
glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_dir);
glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
glColorMaterial(GL_FRONT,GL_EMISSION);
glEnable(GL_COLOR_MATERIAL);
glColor4fv(focus_emission);
glutSolidCone(0.2,0.5,7,7);
glColor4fv(mat_emission);
glDisable(GL_COLOR_MATERIAL);
glPopMatrix();
glutSolidSphere(1.0,20,20);
glFlush();
glutSwapBuffers();
}
void glInit()
{
float light_ambient [] = {0.0,0.2,0.0,1.0};
float light_diffuse_specular [] = {0.8,0.8,0.8,1.0};
float spot_cutoff = 30.0;
float spot_exponent = 1.0;
float mat_ambient_diffuse [] = {0.0,0.8,1.0,1.0};
float mat_specular [] = {0.7,0.0,0.0,1.0};
float mat_shininess = 0.4;
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
glLoadIdentity();
glTranslatef(0.0,0.0,-5.0);
}
void reshape(int width, int height)
{
GLfloat h = (GLfloat) height / (GLfloat) width;
glViewport(0, 0, (GLint) width, (GLint) height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0,1.0,1.0,100.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0.0,0.0,-5.0);
glutPostRedisplay();
}
int main(int argc, char ** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowPosition(20,20);
glutInitWindowSize(350,350);
glutCreateWindow(argv[0]);
glInit();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutSpecialFunc(specialKeys);
glutKeyboardFunc(keys);
glutMainLoop();
return 0;
}