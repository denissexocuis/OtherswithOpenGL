#include <GL/glut.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_SPHERES 50
#define SPHERE_RADIUS 0.3

typedef struct {
    float maxpos;
    float pos[3];
    float dir[3];
    float speed;
} TSphere;

TSphere sphere[NUM_SPHERES];

void initSphere(TSphere *s, float maxpos, float speed) {
    s->maxpos = maxpos;
    s->pos[0] = (rand() % (int)maxpos) - maxpos / 2;
    s->pos[1] = (rand() % (int)maxpos) - maxpos / 2;
    s->pos[2] = (rand() % (int)maxpos) - maxpos / 2;

    s->dir[0] = (float)rand() / RAND_MAX;
    s->dir[1] = (float)rand() / RAND_MAX;
    s->dir[2] = (float)rand() / RAND_MAX;

    float dirmod = sqrt(s->dir[0] * s->dir[0] + s->dir[1] * s->dir[1] + s->dir[2] * s->dir[2]);

    s->dir[0] /= dirmod;
    s->dir[1] /= dirmod;
    s->dir[2] /= dirmod;
    s->dir[0] *= speed;
    s->dir[1] *= speed;
    s->dir[2] *= speed;
}

void testSphere(TSphere *s) {
    if (s->pos[0] < -s->maxpos || s->pos[0] > s->maxpos) s->dir[0] *= -1;
    if (s->pos[1] < -s->maxpos || s->pos[1] > s->maxpos) s->dir[1] *= -1;
    if (s->pos[2] < -s->maxpos || s->pos[2] > s->maxpos) s->dir[2] *= -1;

    s->pos[0] += s->dir[0];
    s->pos[1] += s->dir[1];
    s->pos[2] += s->dir[2];
}

float *getPosv(TSphere *s) {
    return s->pos;
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0);
    for (int i = 0; i < NUM_SPHERES; i++) {
        initSphere(&sphere[i], 5, ((rand() % 10) / (float)20) + 0.1);
    }
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(3, 3, 14, 0, 0, 0, 0, 1, 0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(10);
    for (int i = 0; i < NUM_SPHERES; i++) {
        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        float *pos = getPosv(&sphere[i]);
        glTranslatef(pos[0], pos[1], pos[2]);
        glutSolidSphere(SPHERE_RADIUS, 10, 10);
        glPopMatrix();
        testSphere(&sphere[i]);
    }
    glFlush();
    glutSwapBuffers();
}

void idle(void) {
    usleep(33);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    initGL();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
