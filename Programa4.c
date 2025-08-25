#include <GL/glut.h>

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0,0.0,-1.0);

    glBegin(GL_QUADS);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    //GL_TRIANGLES_FAN
    //GL_TRIANGLES_STRIP
    //GL_TRIANGLES
    //polygon, quads

    glBegin(GL_TRIANGLES_FAN);
        //poniendo colorsito a los triangulos ;)
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0, 0.8, 0.0);

            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-0.6, -0.2, 0.0);

            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0.6, -0.2, 0.0);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); //porque ocupamos swap buffers

    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,200);
    glutCreateWindow("ventana");

    glClearColor(0.0, 0.0, 0.0, 0.0); 
    glViewport(0,0,500,500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-1.0,1.0,-1.0,1.0,-1.0, 1.0); //cámara
    gluPerspective(60.0, 1.0, 1.0, 100.00);
    glShadeModel(GL_SMOOTH); //GL_FLAT
    //glShadeModel(GL_FLAT);
    //glShadeModel(GL_POLYGON);
    //gluOrtho2D(0.0, 2.0, 0.0, 2.0);

    glutDisplayFunc(display);
    glutMainLoop();
}