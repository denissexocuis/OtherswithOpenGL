#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

//cuerpo
#define BODY_HEIGHT 4.5
#define BODY_WIDTH 3.0
#define BODY_LENGTH 3.0

//brazo
#define ARM_HEIGHT 3.5
#define ARM_WIDTH 1.0
#define ARM_LENGTH 1.0

//pie
#define LEG_HEIGHT 4.0
#define LEG_WIDTH 1.0
#define LEG_LENGTH 1.0

//cabeza
#define HEAD_HEIGHT 2.5
#define HEAD_WIDTH 2.5
#define HEAD_LENGTH 2.5

//gorrito
#define GORR_HEIGHT 1.0
#define GORR_WIDTH 3.5
#define GORR_LENGTH 2.0

// variable global para manejar el angulo de movimiento
float angulo = 0.0,
      brazoDerecho = 0.0;


void bodyMario(void) {
    // cuerpo
    glPushMatrix();
        glTranslatef(0, BODY_HEIGHT / 2, 0);
        glScalef(BODY_WIDTH, BODY_HEIGHT, BODY_LENGTH);
        glColor3f(0.0, 0.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();
}

void cabMario(void) {
    //  cabeza
    glPushMatrix();
        glTranslatef(0.0, BODY_HEIGHT + HEAD_HEIGHT / 2, 0.0);
        glScalef(HEAD_WIDTH, HEAD_HEIGHT, HEAD_LENGTH);
        glColor3f(1, 0.6, 0.6);
        glutSolidCube(1.0);
    glPopMatrix();

    //  gorra
    glPushMatrix();
        glTranslatef(0.0, BODY_HEIGHT + HEAD_HEIGHT + GORR_HEIGHT / 2, 0.0);
        glScalef(GORR_WIDTH, GORR_HEIGHT, GORR_LENGTH);
        glColor3f(1, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
}

void braD(void) {
    //  brazo derecho
    
    glPushMatrix();
        //primero se posiciona el brazo hasta arriba para que se posicionen JUNTOS y se muevan JUNTOS
        glTranslatef(-(BODY_WIDTH + ARM_WIDTH) / 2, BODY_HEIGHT - ARM_HEIGHT / 2, 0.0);
        glTranslatef(0,ARM_HEIGHT/2,0); // para posicionar tu brazo antes de girar y posicionar hombro
            // AQUI SE PONE GLROTATEF
            glRotatef(brazoDerecho, 0,0,1);
            // se pone otro angulo para que no se mueva para atrás cada vez que quieras mover el brazo
        glTranslatef(0,-ARM_HEIGHT/2,0); // para mantener estático tu hombro

        // BRAZO DERECHO
        glPushMatrix();
            glScalef(ARM_WIDTH, ARM_HEIGHT, ARM_LENGTH);
            glColor3f(1.0, 0.0, 0.0);
            glutSolidCube(1.0);
        glPopMatrix();
        
        //la mano derecha debe ir en la misma matriz que el brazo para que se mueva con tooodo y el brazo, si no, la mano se quedará estática
        glTranslatef(0,-(ARM_HEIGHT+ARM_WIDTH)/2,0); //se baja un poco la mano para que se posicione bien
        glScalef(ARM_WIDTH, ARM_WIDTH, ARM_LENGTH);
        glColor3f(1.0, 1.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();

    //mano derecha
    glPushMatrix();
       
    glPopMatrix();
}

void braI(void) {

    // brazo izquierdo 
    glPushMatrix();
        glTranslatef((BODY_WIDTH + ARM_WIDTH) / 2, BODY_HEIGHT - ARM_HEIGHT / 2, 0.0);
        glScalef(ARM_WIDTH, ARM_HEIGHT, ARM_LENGTH);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // mano izquierda
    glPushMatrix();
        glTranslatef((BODY_WIDTH + ARM_WIDTH) / 2, BODY_HEIGHT - ARM_HEIGHT - ARM_WIDTH / 2, 0.0);
        glScalef(ARM_WIDTH, ARM_WIDTH, ARM_LENGTH);
        glColor3f(1.0, 1.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
}

void pieD(void) {
    //pierna derecha
    glPushMatrix();
        glTranslatef(-(BODY_WIDTH - LEG_WIDTH) / 2, -(BODY_HEIGHT + LEG_HEIGHT) / 4.4, 0.0);
        glScalef(LEG_WIDTH, LEG_HEIGHT, LEG_LENGTH);
        glColor3f(0.0, 0.1, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // bota derecha
    glPushMatrix();
        glTranslatef(-(BODY_WIDTH - LEG_WIDTH) / 2, -(BODY_HEIGHT + LEG_HEIGHT + LEG_WIDTH) / 2.5, LEG_LENGTH / 2);
        glScalef(LEG_WIDTH, LEG_WIDTH, LEG_LENGTH * 2);
        glColor3f(0.4, 0.3, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();

}

void pieI(void) {
    //pierna izquierda
    glPushMatrix();
        glTranslatef((BODY_WIDTH - LEG_WIDTH) / 2, -(BODY_HEIGHT + LEG_HEIGHT) / 4.4, 0.0);
        glScalef(LEG_WIDTH, LEG_HEIGHT, LEG_LENGTH);
        glColor3f(0.0, 0.1, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();

    // bota izquierda
    glPushMatrix();
        glTranslatef((BODY_WIDTH - LEG_WIDTH) / 2, -(BODY_HEIGHT + LEG_HEIGHT + LEG_WIDTH) / 2.5, LEG_LENGTH / 2);
        glScalef(LEG_WIDTH, LEG_WIDTH, LEG_LENGTH * 2);
        glColor3f(0.4, 0.3, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();

}
/* teclado
    unsigned char key es la letra que pulsamos en el programa
    x y y es la posición del mouse
 */
static void keyboard(unsigned char key, int x, int y)
{
    //no supe que letra querias para adelante o atrás pero te puse w y s
    if(key == 'w' || key == 'W')
        angulo +=1; //cada vez que presionas w, el angulo se  suma +1 y se cambia en el lugar donde está dibujado todo tu muñeco, en tu display, es decir, se mueve para adelante
    else if(key == 's' || key == 'S')
        angulo -=1; //cada vez que presionas w, el angulo se suma -1 y  se mueve paara atrás
    else if(key == 'r' || key == 'R')
        brazoDerecho -=2;

    glutPostRedisplay();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity(); //matriz de identidad
    glTranslatef(0,-1.5,-20); //para que se vea, lo mueves un poco atrás

    /* te voy a explicar porque no se movia, cada vez que vuelves a dibujar con glutPostRedisplay, TOODO el display vuelve a dibujarse, dentro del display tienes la función de glTranslatef(0.0, 0.0, -12), entonces, cada vez que dibujas, el muñeco se hará para atrás hasta que ya no se vea porque se está volviendo a dibujar todo el tiempo
    
    si pones glutPostRedisplay en keyboard, siempre se irá para atrás cada vez que pulses una tecla
    si pones glutPostRedisplay en display, se moverá una vez que compilas el programa

    SOLUCIÓN
    1. cargar matriz de identidad desde antes en display
    2. posicionas tu muñeco en donde quieras que se vea
    3. asegurate de tener glMatrixMode(GL_MODELVIEW);
    4. ahora si, pon todas las funciones que quieras para que se mueva o gire
    */

   //para adelante y atrás
    glTranslatef(0.0, 0.0, angulo);

    glPushMatrix();
        cabMario();
    glPopMatrix();

    glPushMatrix();
        bodyMario();
    glPopMatrix();

    glPushMatrix();
    /* ¿porqué NO poner glRotatef aqui, porque se movera todo el brazo y queremos que una parte se quede estática ;) 
    ve a la linea 66
    */
        braD();
    glPopMatrix();

    glPushMatrix();
        braI();
    glPopMatrix();

    glPushMatrix();
        pieD();
    glPopMatrix();

    glPushMatrix();
        pieI();
    glPopMatrix();

    glutSwapBuffers();

}

// solo hace falta glutPostRedisplay para volver a dibujar
/* void update(int value) {
    glutPostRedisplay();  // Redibujar
    glutTimerFunc(16, update, value + 1);  // Llamar a update nuevamente
} */


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("HUMANITOO mario");

    glClearColor(0.5, 0.7, 1.0, 1.0);
    glViewport(0, 0, 600, 600);  // Alineamos viewport con el tamaño de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, 1.0, 1.0, 100.0);
    glShadeModel(GL_SMOOTH);
    //te faltaba model view, por eso no se movia
    glMatrixMode(GL_MODELVIEW);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
