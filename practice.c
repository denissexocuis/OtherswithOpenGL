#include <GL/glut.h>

void init() {
    glEnable(GL_DEPTH_TEST); // Habilitar el test de profundidad
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 35.0); // Campo de visión, aspecto, cerca, lejos
    glMatrixMode(GL_MODELVIEW);
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Reiniciar la matriz

    // Mover la cámara hacia atrás
    glTranslatef(0.0, 0.0, -2.0); // 0.5f en Y para estar sobre el cubo    
    // Escalar el objeto
    glScalef(2.0f, 1.0f, 1.0f);
    
    // Dibujar un cubo
    glutWireCube(1.0); // Dibuja un cubo de tamaño 1.0

    glFlush(); // Mostrar el resultado
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ejemplo de glScalef");
    init(); // Llamar a la función de inicialización
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
