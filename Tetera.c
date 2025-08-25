#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

//Para la rotacion.
GLfloat rotate_y=0.0f;
GLfloat rotate_x=0.0f;
GLfloat rotate_z=0.0f;

//Para la traslación.
GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;

//Para el escalado.
GLfloat scale = 1.0f;

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Aqui llamamos para rotar los tres ejes.
    glRotatef( rotate_x, 1.0f, 0.0f, 0.0f );
    glRotatef( rotate_y, 0.0f, 1.0f, 0.0f );
    glRotatef( rotate_z, 0.0f, 0.0f, 1.0f );
    glTranslatef(X, Y, Z);//Transladar en los 3 ejes.
    glScalef(scale, scale, scale);
   
    int width, height;//Tamaño de la imagen.

    //Usamos la autogeneración de coordenadas.
    GLfloat plano_s[4] = {1, 0, 0, 0}; // Para el eje X.
    GLfloat plano_t[4] = {0, 1, 0, 0}; // Para el eje Y.



    glutSolidTeapot(1);//Dibujamos la tetera.
    glFlush();

}

//Funcion para hacer rodar el objeto.
void specialKeys( int key, int x, int y ){

    //  Flecha derecha: aumentar rotación.
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    //  Flecha izquierda: rotación en eje Y negativo.
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    //  Flecha arriba: rotación en eje X positivo.
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    //  Flecha abajo: rotación en eje X negativo.
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    //  Tecla especial F2 : rotación en eje Z positivo.
    else if (key == GLUT_KEY_F2)
        rotate_z += 5;
    //  Tecla especial F2 : rotación en eje Z negativo.
    else if (key == GLUT_KEY_F1)
        rotate_z -= 5;

    //  Solicitar actualización de visualización.
    glutPostRedisplay();

}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y){
    //control de teclas que hacen referencia a Escalar y trasladar la tetera en los ejes X,Y,Z.
    switch (key)
    {
    case 's':
        scale=0.5;
        break;
    case 'd':
        scale=1.5;
        break;
    case 'x' :
        X += 0.1f;
        break;
    case 'X' :
        X -= 0.1f;
        break;
    case 'y' :
        Y += 0.1f;
        break;
    case 'Y' :
        Y -= 0.1f;
        break;
    case 'z':
        Z += 0.1f;
        break;
    case 'Z':
        Z -= 0.1f;
        break;
    case 'q':
        exit(0);//Exit.
    }
    glutPostRedisplay();
}

void reshape(int x, int y){
    glViewport(0, 0,  (GLsizei) x, (GLsizei) y);
    glMatrixMode(GL_PROJECTION);// Activamos la matriz de proyeccion.
    glLoadIdentity();//"Limpiamos" la matriz identidad.
    glOrtho(-2.5, 2.5, -2.5, 2.5, -2.5, 2.5);// Usamos Proyeccion Ortogonal.
    glMatrixMode(GL_MODELVIEW);// Activamos la matriz de modelado/visionado.
    glLoadIdentity();// "Limpiamos" la matriz.
}



int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600, 600);//Tamaño de la ventana.
   glutInitWindowPosition(240, 100); //Pocisionde la ventana.
   glutCreateWindow("Tetera"); //Nombre en ventana.
   glutDisplayFunc(display);//Llamando la funcion de dibujo.
   glutKeyboardFunc(keyboard);//Llamando funcion de teclas.
   glutSpecialFunc(specialKeys);//Llamando funcion de teclas especiales.
   glutReshapeFunc(reshape);//Llamando funcion Reshape.
   glutMainLoop();
   return 0;
}