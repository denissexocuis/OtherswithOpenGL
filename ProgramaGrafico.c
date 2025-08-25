#include <GL/glut.h>

/* Graphic Library Utility Toolkit (GLUT) =)
    Librería de alto nivel que nos simplifica la creación de ventanas
    manejo de eventos y las cuestiones de dibujo básico
*/

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT); //borra el color del buffer que guarda el color
        glColor3f(0.0, 1.0, 0.0); //asignar color
        
        //dibujado de conjunto de lineas
        glBegin(GL_LINES); //triangle, cube, dependiendo ;)
            glVertex2f(0.0, 0.0);//vertice inicio de la linea
            glVertex2f(100.0, 100.0); //define el 2do vertice de la linea
            glVertex2f(400.0, 400.0);
            glVertex2f(-300.0, -300.0);
        glEnd();

        glFlush();
    }


int main(int argc, char **argv)
{
    //inicializando GLUT =)
    glutInit(&argc, argv);

    //estableciendo modo de visualización
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //como mandar a llamar el despliege de display

    //estableciendo tamaño de la ventana
    glutInitWindowSize(1080,720); 

    //estableciendo posición de la ventana
    glutInitWindowPosition(100,100); 

    //creando la ventana y dandole un título
    glutCreateWindow("Mi ventanita ;)"); 

    //color de fondo de la ventana
    glClearColor(30.0, 0.0, 0.0, 0.0); 

    //llamando la función  :)
    glutDisplayFunc(display);

    //inicializar el ciclo de GLUT
    glutMainLoop();

    return 0;
}