#include <GL/glut.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_SPHERES 75
#define SPHERE_RADIUS 0.3

typedef struct TSphere {
    float maxpos;
    float pos[3];
    float dir[3];
    float color[3];
    float speed;
} TSphere;

int pass = 0;

void TSphere_init(TSphere* sphere, float maxpos, float speed) {
    sphere->maxpos = maxpos;
    if (!pass) {
        srandom(time(NULL));
        pass = 1;
    }
    sphere->pos[0] = (random() % (int)maxpos) - maxpos / 2;
    sphere->pos[1] = (random() % (int)maxpos) - maxpos / 2;
    sphere->pos[2] = (random() % (int)maxpos) - maxpos / 2;
    sphere->dir[0] = random();
    sphere->dir[1] = random();
    sphere->dir[2] = random();
    sphere->color[0] = (random() % 1001) / 1000.0;
    sphere->color[1] = (random() % 1001) / 1000.0;
    sphere->color[2] = (random() % 1001) / 1000.0;

    float dirmod = sqrt(sphere->dir[0] * sphere->dir[0] + sphere->dir[1] * sphere->dir[1] + sphere->dir[2] * sphere->dir[2]);
    sphere->dir[0] /= dirmod;
    sphere->dir[1] /= dirmod;
    sphere->dir[2] /= dirmod;

    sphere->dir[0] *= speed;
    sphere->dir[1] *= speed;
    sphere->dir[2] *= speed;
}

void TSphere_test(TSphere* sphere) {
    if (sphere->pos[0] < -sphere->maxpos || sphere->pos[0] > sphere->maxpos) sphere->dir[0] *= -1;
    if (sphere->pos[1] < -sphere->maxpos || sphere->pos[1] > sphere->maxpos) sphere->dir[1] *= -1;
    if (sphere->pos[2] < -sphere->maxpos || sphere->pos[2] > sphere->maxpos) sphere->dir[2] *= -1;

    sphere->pos[0] += sphere->dir[0];
    sphere->pos[1] += sphere->dir[1];
    sphere->pos[2] += sphere->dir[2];
}

float* TSphere_getPosv(TSphere* sphere) {
    return sphere->pos;
}

float* TSphere_getColor(TSphere* sphere) {
    return sphere->color;
}

float light_color[] = {1.0, 1.0, 1.0, 1.0};
float light_pos[] = {1.0, 1.0, 1.0, 0.0};
TSphere spheres[NUM_SPHERES];

void initgl() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0);

    for (int i = 0; i < NUM_SPHERES; i++) {
        float speed = ((random() % 10) / (float)20) + 0.1;
        TSphere_init(&spheres[i], 5, speed);
    }

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(3, 3, 14, 0, 0, 0, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void idle(void) {
    usleep(33);
    glutPostRedisplay();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(10);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    for (int i = 0; i < NUM_SPHERES; i++) {
        glPushMatrix();
        glColor4fv(TSphere_getColor(&spheres[i]));
        float* pos = TSphere_getPosv(&spheres[i]);
        glTranslatef(pos[0], pos[1], pos[2]);
        glutSolidSphere(SPHERE_RADIUS, 10, 10);
        glPopMatrix();
        TSphere_test(&spheres[i]);
    }

    glDisable(GL_COLOR_MATERIAL);
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);
    initgl();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
