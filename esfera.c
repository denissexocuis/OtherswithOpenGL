
//Librerías
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

//Variable globlal para la posición de las esferas en el eje X
float posX=0.0;

/*redimensionamiento
    Se manda llamar cuando cambiamos el tamaño de la ventana. lo que hace
    es ajustar la ventana de visualización y la matriz de proyección.
    Nuestra figura se adapta a las nuevas dimensiones de la pantalla.
*/
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

/* Visualización
Dibuja nuestra figura, en sí, dibuja la escena.
En este caso, establece el color a rojo y dibujamos dos eferas.
*/
static void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    glRotatef(.1,1,0,0);

        
    
    /*
        Dibujamos la primer esfera, es sólida
    */
    glPushMatrix();
        glTranslated(posX,1.2,-6);
        
        glutSolidSphere(1,50,50);
    glPopMatrix();
    
    /*
        Dibujamos la segunda esfera, mallada
    */
   glPushMatrix();
        glRotatef(posX,.0,.0,1.0);
        glTranslated(0.0,-1.2,-6);
        glutWireSphere(1,16,16);
    glPopMatrix();
    //Rotatef y Translated, rotar y trasladar, posicionamos las esferas.
    
    glutSwapBuffers();
    glutPostRedisplay();//refrescar
}

/*
    Definimos las propiedades de iluminación y del material que dibuja o da forma
    a un objeto 3D.

*/

/*Iluminación
	-ambient = El color ambiental de la luz
		El color que se refleja uniformemente en todas las superficies
	-diffuse = El color difuso de la luz
		El color que se refleja uniformemente en todas las superficies, que
		miran directamente a la luz
	-specular = El color especular de la luz
		El color que se refleja en las superficies brillantes
	-position = La posición de la luz en la escena
		Se refiere a la luz que se propaga desde la posición de la figura hacia
		todas las direcciones.
estas son las 4 variables que definen las propiedades de iluminación

*/
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

/*Material
	-mat_ambient = Define el color ambiental del material.
		Es el color que se refleja uniformemente en el material.
	-mat_diffuse = Define el color difuso del material.
		El color que refleja el material en las superficies cuando miran 
		directamente a la luz.
	-mat_specular = Define el color especular del material.
		El color que refleja el material en las superficies brillantes.
	-high_shininess = Define el brillo del material.
		Cantidad de brillo alto.

Estas son las 4 variables que definen las propiedades de los materiales

Tanto las propiedades de iluminación como del material nos permiten dar un
efecto 3D más realista.
*/
const GLfloat m_ambient[]={ 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]={ 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]={ 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[]={ 100.0f };


/*
    Se va a mandar llamar cuando presionemos una tecla.
*/
static void keyboard(unsigned char key, int x, int y)
{
   if((key == 0x1b)||(key == 'q')||(key == 'Q'))
      exit(0); // terminar programa
   else
     if ((key=='R') || (key == 'r'))//Rotar
       {
            posX += 1;
       }
     if ((key=='t') || (key == 'T'))  
            posX -=1;
   glutSwapBuffers();
   glutPostRedisplay();//refrescar
}

/* Principal
    Iniciamos GLUT, creamos la ventana, se configura el tamaño de la pantalla
    Se mandan llamar las funciones necesarias.
 */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    
    glutCreateWindow("Esferas 3D");
    
    //Entrando al ciclo para redibujar la escena.
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glClearColor(1,1,1,1);

    //renderizado
    glShadeModel (GL_SMOOTH); //Sombreado ligero
    glEnable(GL_CULL_FACE); //Habilita la eliminación de la cara trasera 
    glCullFace(GL_BACK); //Esta indica que se deben eliminar las caras traseras
    
    glEnable(GL_DEPTH_TEST);//Prueba de profundidad
    glDepthFunc(GL_LESS); //Cantidad de profundidad (acuérdense del pulgar)
    
   
    glEnable(GL_LIGHT0);//Habilita la fuente de luz 0
    glEnable(GL_NORMALIZE);//Habilita la normalización de los vectores.
    glEnable(GL_COLOR_MATERIAL);//Habilita el color dependiendo de la luz
    glEnable(GL_LIGHTING); //Habilitar la iluminación en general
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); //Componente ambiental de la luz
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); //Componente difuso de la luz
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //Componente especular de la luz, hablando de superficies
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //Componente posición de la fuente de luz
    
    /* glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient); //Componente ambiental del material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //Componente difuso del material
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //Componente especular del material
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); //Componente de brillo de material */
   
    glutMainLoop(); 
    
    return EXIT_SUCCESS;
}