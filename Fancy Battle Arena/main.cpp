#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <string>

float angle = 0;
float tx = 0.0, ty = 0.0;

std::string Direction = "Right";

bool powerActive = false;

float powerPosX = 0.0;
float powerPosY = 0.0;

float powerSpeed = 2.0f;
float powerRadius = 1.5f;

std::string powerDirection = "Right";

void Power()
{
    if (!powerActive)
        return;

    glTranslatef(powerPosX, powerPosY, 0);

    if (powerDirection == "Up")
        glRotatef(90, 0, 0, 1);

    else if (powerDirection == "Down")
        glRotatef(-90, 0, 0, 1);

    else if (powerDirection == "Left")
        glRotatef(180, 0, 0, 1);

    glColor3f(0.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

        glVertex2f(-9, -1);
        glVertex2f(-0.5, -1);
        glVertex2f(-0.5, 1);
        glVertex2f(-9, 1);

    glEnd();

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(0, 0);

        for (int i = 0; i <= 360; i++)
        {
            float angle = i * 3.14159f / 180.0f;

            float x = powerRadius * cos(angle);
            float y = powerRadius * sin(angle);

            glVertex2f(x, y);
        }

    glEnd();

    if (powerDirection == "Up")
        glRotatef(-90, 0, 0, 1);

    else if (powerDirection == "Down")
        glRotatef(90, 0, 0, 1);

    else if (powerDirection == "Left")
        glRotatef(-180, 0, 0, 1);

    glTranslatef(-powerPosX, -powerPosY, 0);
}

void Player()
{
    glTranslatef(tx, ty, 0);

    glColor3f(1.00, 0.87, 0.80);

    float cX = 0.0;
    float cY = 1.7;
    float r = 0.7;

    glBegin(GL_POLYGON);

    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;

        float x = cX + r * cos(angle);
        float y = cY + r * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();

    glColor3f(1.00, 0.87, 0.80);

    glBegin(GL_TRIANGLES);

        glVertex2f(-0.4, 1);
        glVertex2f(0.4, 1);
        glVertex2f(0, 0.32);

    glEnd();

    glColor3f(0, 0, 1);

    glBegin(GL_QUADS);

        glVertex2f(-0.7, -0.1);
        glVertex2f(0.7, -0.1);
        glVertex2f(0.7, -0.4);
        glVertex2f(-0.7, -0.4);

    glEnd();

    glColor3f(1.0f, 0.65f, 0.25f);

    glBegin(GL_QUADS);

        glVertex2f(-0.7, -1);
        glVertex2f(-0.7, 1);
        glVertex2f(0.7, 1);
        glVertex2f(0.7, -1);

    glEnd();

    glColor3f(0, 0, 1);

    glBegin(GL_QUADS);

        glVertex2f(-0.7, -1);
        glVertex2f(0, 1);
        glVertex2f(0, -1.8);
        glVertex2f(-0.7, -1.8);

    glEnd();

    glColor3f(0, 0, 1);

    glBegin(GL_QUADS);

        glVertex2f(0.1, -1);
        glVertex2f(0.7, -1);
        glVertex2f(0.7, -1.8);
        glVertex2f(0.1, -1.8);

    glEnd();

    glTranslatef(-tx, -ty, 0);
}

void display()
{
    glClearColor(0.40f, 0.80f, 0.40f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Player();

    Power();

    glTranslatef(25, -25, 0);
    glRotatef(angle, 1, 1, 0);

    glBegin(GL_QUADS);

        glColor3f(1, 0, 0);
        glVertex3f(-2, -2, 2);
        glVertex3f(2, -2, 2);
        glVertex3f(2, 2, 2);
        glVertex3f(-2, 2, 2);

        glColor3f(0, 1, 0);
        glVertex3f(-2, -2, -2);
        glVertex3f(-2, 2, -2);
        glVertex3f(2, 2, -2);
        glVertex3f(2, -2, -2);

        glColor3f(0, 0, 1);
        glVertex3f(-2, -2, -2);
        glVertex3f(-2, -2, 2);
        glVertex3f(-2, 2, 2);
        glVertex3f(-2, 2, -2);

        glColor3f(1, 1, 0);
        glVertex3f(2, -2, -2);
        glVertex3f(2, 2, -2);
        glVertex3f(2, 2, 2);
        glVertex3f(2, -2, 2);

        glColor3f(0, 1, 1);
        glVertex3f(-2, 2, -2);
        glVertex3f(-2, 2, 2);
        glVertex3f(2, 2, 2);
        glVertex3f(2, 2, -2);

        glColor3f(1, 0, 1);
        glVertex3f(-2, -2, -2);
        glVertex3f(2, -2, -2);
        glVertex3f(2, -2, 2);
        glVertex3f(-2, -2, 2);

    glEnd();

    glLoadIdentity();

    glutSwapBuffers();
}

void updatePower(int value)
{
    if (powerActive)
    {
        if (powerDirection == "Up")
        {
            powerPosY += powerSpeed;
        }
        else if (powerDirection == "Down")
        {
            powerPosY -= powerSpeed;
        }
        else if (powerDirection == "Left")
        {
            powerPosX -= powerSpeed;
        }
        else if (powerDirection == "Right")
        {
            powerPosX += powerSpeed;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(35, updatePower, 0);
}

void update(int value)
{
    angle += 1;

    glutPostRedisplay();
    glutTimerFunc(3, update, 0);
}

void keyboard(unsigned char c, int x, int y)
{
    if (c == 'w')
    {
        ty += 1;
        Direction = "Up";
    }
    else if (c == 's')
    {
        ty -= 1;
        Direction = "Down";
    }
    else if (c == 'a')
    {
        tx -= 1;
        Direction = "Left";
    }
    else if (c == 'd')
    {
        tx += 1;
        Direction = "Right";
    }
    else if (c == 'j')
    {
        powerActive = true;

        powerPosX = tx;
        powerPosY = ty;

        powerDirection = Direction;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
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
    glutTimerFunc(0, updatePower, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
