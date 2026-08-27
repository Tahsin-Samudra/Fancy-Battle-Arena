#include <GL/glut.h>
#include <cmath>

float angle = 0;

void display() {
    glClearColor(0.40f, 0.80f, 0.40f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //player
    //Head
    glColor3f(1.00,0.87,0.80);
    float cX = 0.0;
    float cY = 1.7;
    float r = 0.7;

    glBegin(GL_POLYGON);

    for(int i=0; i<=360; i++)
    {
        float angle = i*3.1416/180;

        float x =cX+r*cos(angle);
        float y =cY+r*sin(angle);

        glVertex2f(x, y);
    }

    glEnd();


    //chest
    glColor3f(1.00,0.87,0.80);
    glBegin(GL_TRIANGLES);

        glVertex2f(-0.4, 1);
        glVertex2f(0.4, 1);
        glVertex2f(0,0.32);


    glEnd();

    //Belt
    glColor3f(0,0,1);
    glBegin(GL_QUADS);

        glVertex2f(-0.7,-0.1);
        glVertex2f(0.7,-0.1);
        glVertex2f(0.7,-0.4);
        glVertex2f(-0.7,-0.4);

    glEnd();


    //body
    glColor3f(1.0f, 0.65f, 0.25f);
    glBegin(GL_QUADS);

        glVertex2f(-.7,-1);
        glVertex2f(-.7,1);
        glVertex2f(.7,1);
        glVertex2f(.7,-1);

    glEnd();



    //left leg
    glColor3f(0,0,1);
    glBegin(GL_QUADS);

        glVertex2f(-.7,-1);
        glVertex2f(0,1);
        glVertex2f(0,-1.8);
        glVertex2f(-.7,-1.8);

    glEnd();
    //right leg
    glColor3f(0,0,1);
    glBegin(GL_QUADS);

        glVertex2f(0.1,-1);
        glVertex2f(0.7,-1);
        glVertex2f(0.7,-1.8);
        glVertex2f(0.1,-1.8);

    glEnd();



    //health Cube
    glPushMatrix();

    glTranslatef(25, -25, 0);
    glRotatef(angle, 1, 1, 0);

    glBegin(GL_QUADS);

        // Front
        glColor3f(1, 0, 0);
        glVertex3f(-2, -2, 2);
        glVertex3f(2, -2, 2);
        glVertex3f(2, 2, 2);
        glVertex3f(-2, 2, 2);

        // Back
        glColor3f(0, 1, 0);
        glVertex3f(-2, -2, -2);
        glVertex3f(-2, 2, -2);
        glVertex3f(2, 2, -2);
        glVertex3f(2, -2, -2);

        // Left
        glColor3f(0, 0, 1);
        glVertex3f(-2, -2, -2);
        glVertex3f(-2, -2, 2);
        glVertex3f(-2, 2, 2);
        glVertex3f(-2, 2, -2);

        // Right
        glColor3f(1, 1, 0);
        glVertex3f(2, -2, -2);
        glVertex3f(2, 2, -2);
        glVertex3f(2, 2, 2);
        glVertex3f(2, -2, 2);

        // Top
        glColor3f(0, 1, 1);
        glVertex3f(-2, 2, -2);
        glVertex3f(-2, 2, 2);
        glVertex3f(2, 2, 2);
        glVertex3f(2, 2, -2);

        // Bottom
        glColor3f(1, 0, 1);
        glVertex3f(-2, -2, -2);
        glVertex3f(2, -2, -2);
        glVertex3f(2, -2, 2);
        glVertex3f(-2, -2, 2);

    glEnd();

    glPopMatrix();


    glutSwapBuffers();
}

void update(int value) {

    angle += 1;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}




int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1980, 1080);
    glutCreateWindow("3D Objects");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-30, 30, -30, 30, -30, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
