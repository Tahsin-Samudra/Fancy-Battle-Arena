#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <string>

float angle = 0;
float tx = 0.0, ty = 0.0;

std::string Direction = "Right";




bool powerActive = false;

float playerHealth = 100.0f;
float playerMaxHealth = 100.0f;

float houseHealth = 100.0f;
float houseMaxHealth = 100.0f;

float powerPosX = 0.0;
float powerPosY = 0.0;

float powerSpeed = 2.0f;
float powerRadius = 1.5f;

float e1houseX = -21.0f;
float e1houseY = 18.0f;

float houseTargetX = e1houseX;
float houseTargetY = e1houseY;
float houseDamageRadius = 3.0f;
float houseDamageRate = 0.15f;

float rotation = 0.0;
float enemy1X = 15.0f;
float enemy1Y = -10.0f;

float enemy2X = -21.0f;
float enemy2Y = 10.0f;

float enemy3X = 10.0f;
float enemy3Y = -15.0f;

float enemyRadius = 2.0f;

bool enemy1Alive = true;
bool enemy2Alive = true;
bool enemy3Alive = true;

std::string powerDirection = "Right";

bool collision(float powerX, float powerY, float enemyX, float enemyY)
{
    float dx = powerX - enemyX;
    float dy = powerY - enemyY;

    float distance = sqrt(dx * dx + dy * dy);

    if (distance <= powerRadius + enemyRadius)
        return true;

    return false;
}

void drawHealthBarChunks(float x, float y, float chunkWidth, float chunkHeight,
                          float spacing, int totalChunks, int filledChunks,
                          float r, float g, float b)
{
    glDisable(GL_DEPTH_TEST);

    for (int i = 0; i < totalChunks; i++)
    {
        float chunkX = x + i * (chunkWidth + spacing);

        // filled or empty color
        if (i < filledChunks)
            glColor3f(r, g, b);
        else
            glColor3f(0.2f, 0.2f, 0.2f);

        glBegin(GL_QUADS);
            glVertex2f(chunkX, y);
            glVertex2f(chunkX + chunkWidth, y);
            glVertex2f(chunkX + chunkWidth, y + chunkHeight);
            glVertex2f(chunkX, y + chunkHeight);
        glEnd();

        // border
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(chunkX, y);
            glVertex2f(chunkX + chunkWidth, y);
            glVertex2f(chunkX + chunkWidth, y + chunkHeight);
            glVertex2f(chunkX, y + chunkHeight);
        glEnd();
    }
    glEnable(GL_DEPTH_TEST);
}


void updateEnemy(int val)
{
    if (enemy1Alive)
    {
        if (enemy1X < e1houseX)
            enemy1X += 0.05f;
        if (enemy1X > e1houseX)
            enemy1X -= 0.05f;
        if (enemy1Y < e1houseY)
            enemy1Y += 0.05f;
        if (enemy1Y > e1houseY)
            enemy1Y -= 0.05f;


        float dx = enemy1X - houseTargetX;
        float dy = enemy1Y - houseTargetY;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist <= houseDamageRadius)
        {
            houseHealth -= houseDamageRate;
            if (houseHealth < 0) houseHealth = 0;
        }
    }

    // repeat the same block for enemy2Alive and enemy3Alive
    if (enemy2Alive)
    {
        if (enemy2X < e1houseX) enemy2X += 0.05f;
        if (enemy2X > e1houseX) enemy2X -= 0.05f;
        if (enemy2Y < e1houseY) enemy2Y += 0.05f;
        if (enemy2Y > e1houseY) enemy2Y -= 0.05f;

        float dx = enemy2X - houseTargetX;
        float dy = enemy2Y - houseTargetY;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist <= houseDamageRadius)
        {
            houseHealth -= houseDamageRate;
            if (houseHealth < 0) houseHealth = 0;
        }
    }

    if (enemy3Alive)
    {
        if (enemy3X < e1houseX) enemy3X += 0.05f;
        if (enemy3X > e1houseX) enemy3X -= 0.05f;
        if (enemy3Y < e1houseY) enemy3Y += 0.05f;
        if (enemy3Y > e1houseY) enemy3Y -= 0.05f;

        float dx = enemy3X - houseTargetX;
        float dy = enemy3Y - houseTargetY;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist <= houseDamageRadius)
        {
            houseHealth -= houseDamageRate;
            if (houseHealth < 0) houseHealth = 0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(14, updateEnemy, 0);
}

void Enemy(float enemyX, float enemyY)
{
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(enemyX, enemyY);

        for (int i = 0; i <= 360; i++)
        {
            float enemyAngle = i * 3.14159f / 180.0f;

            float x = enemyX + enemyRadius * cos(enemyAngle);
            float y = enemyY + enemyRadius * sin(enemyAngle);

            glVertex2f(x, y);
        }

    glEnd();
}
void tree(float x, float y) {
    glTranslatef(x, y, 0);

    //x : 3 , y : 2 (2x2 = 4)
    glColor3f(0.60f, 0.32f, 0.15f);


    float radius = 1.2;
    float cx = -1.5;
    float cy = 1.5;

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0, 1, 0);

    for (int i = 0; i <=360; i++)
    {
        float angle = i * 3.14159 / 180;

        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);

        glVertex3f(x, y, 0);
    }

    glEnd();

    float radius1 = 1.5;
    float cx1 = 0.0;
    float cy1 = 3.4;

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0, 1, 0);

    for (int i = 0; i <=360; i++)
    {
        float angle = i * 3.14159 / 180;

        float x = cx1 + radius1 * cos(angle);
        float y = cy1 + radius1 * sin(angle);

        glVertex3f(x, y, 0);
    }

    glEnd();

    float radius2 = 1.2;
    float cx2 = 1.5;
    float cy2 = 2.0;

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0, 1, 0);

    for (int i = 0; i <=360; i++)
    {
        float angle = i * 3.14159 / 180;

        float x = cx2 + radius2 * cos(angle);
        float y = cy2 + radius2 * sin(angle);

        glVertex3f(x, y, 0);
    }

    glEnd();

    //body
    glColor3f(0.60f, 0.32f, 0.15f);
    glBegin(GL_QUADS);

        glVertex2f(-1, -2);
        glVertex2f(-1, 2);
        glVertex2f(1, 2);
        glVertex2f(1, -2);

    glEnd();

}


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
            float powerAngle = i * 3.14159f / 180.0f;

            float x = powerRadius * cos(powerAngle);
            float y = powerRadius * sin(powerAngle);

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
        float playerAngle = i * 3.1416 / 180;

        float x = cX + r * cos(playerAngle);
        float y = cY + r * sin(playerAngle);

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

void cross(){
    //cross
    glTranslatef(-16.5,-23,0.0);
        glRotatef(rotation,0.0, 0.0, 1.0);


    glColor3f(1,1,0);
    glBegin(GL_QUADS);
        glVertex2f(-4, -1);
        glVertex2f(4, -1);
        glVertex2f(4, 1);
        glVertex2f(-4, 1);
    glEnd();


    glBegin(GL_QUADS);
        glVertex2f(-1, -4);
        glVertex2f(1, -4);
        glVertex2f(1, 4);
        glVertex2f(-1, 4);
    glEnd();
}

void display()
{
    glClearColor(0.40f, 0.80f, 0.40f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLoadIdentity();

    int totalChunks = 5;
    int filledHealthChunks = (int)ceil((playerHealth / playerMaxHealth) * totalChunks);
    drawHealthBarChunks(15, 27, 1.4, 1.2, 0.3, totalChunks, filledHealthChunks, 0, 1, 0);

    int filledHouseChunks = (int)ceil((houseHealth / houseMaxHealth) * totalChunks);
    drawHealthBarChunks(15, 24.5, 1.4, 1.2, 0.3, totalChunks, filledHouseChunks, 1, 0.5f, 0);



    //door
    glBegin(GL_QUADS);

        glColor3f(1,0,0);

        glVertex2f(-27,-30);
        glVertex2f(-27,-26);
        glVertex2f(-23,-26);
        glVertex2f(-23,-30);



    glEnd();

    //Farm House
    glBegin(GL_POLYGON);

        glColor3f(0.0f, 0.45f, 1.0f);

        glVertex2f(-30,-30);
        glVertex2f(-30,-25);
        glVertex2f(-25,-20);
        glVertex2f(-20,-25);
        glVertex2f(-20,-30);

    glEnd();


    //mill
    glBegin(GL_QUADS);

        glColor3f(0.0f, 0.45f, 1.0f);

        glVertex2f(-18,-30);
        glVertex2f(-18,-24);
        glVertex2f(-15,-24);
        glVertex2f(-15,-30);

    glEnd();






    //House
    //Door1
    glBegin(GL_QUADS);

        glColor3f(0.0f, 0.45f, 1.0f);

        glVertex2f(-21,21);
        glVertex2f(-21,26);
        glVertex2f(-18,26);
        glVertex2f(-18,21);

    glEnd();

    //Door2
    glBegin(GL_QUADS);

        glColor3f(0.0f, 0.45f, 1.0f);

        glVertex2f(-27,21);
        glVertex2f(-27,26);
        glVertex2f(-24,26);
        glVertex2f(-24,21);

    glEnd();

    //body
    glBegin(GL_QUADS);

        glColor3f(0.95f, 0.95f, 0.95f);

        glVertex2f(-30,21);
        glVertex2f(-30,30);
        glVertex2f(-15,30);
        glVertex2f(-15,21);

    glEnd();


    tree(15,16);
    glLoadIdentity();


    Player();

    Power();

    if (enemy1Alive)
        Enemy(enemy1X, enemy1Y);

    if (enemy2Alive)
        Enemy(enemy2X, enemy2Y);

    if (enemy3Alive)
        Enemy(enemy3X, enemy3Y);



    glLoadIdentity();

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
    cross();


    glutSwapBuffers();
}

void update_cross(int value) {

    rotation += 1;

    glutPostRedisplay();
    glutTimerFunc(16, update_cross, 0);
}

void updatePower(int value)
{
    if (powerActive)
    {
        if (powerDirection == "Up")
            powerPosY += powerSpeed;

        else if (powerDirection == "Down")
            powerPosY -= powerSpeed;

        else if (powerDirection == "Left")
            powerPosX -= powerSpeed;

        else if (powerDirection == "Right")
            powerPosX += powerSpeed;


        if (enemy1Alive && collision(powerPosX, powerPosY, enemy1X, enemy1Y))
        {
            enemy1Alive = false;
            powerActive = false;
        }

        if (enemy2Alive && collision(powerPosX, powerPosY, enemy2X, enemy2Y))
        {
            enemy2Alive = false;
            powerActive = false;
        }

        if (enemy3Alive && collision(powerPosX, powerPosY, enemy3X, enemy3Y))
        {
            enemy3Alive = false;
            powerActive = false;
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
    glutTimerFunc(0, updateEnemy, 0);
    glutTimerFunc(16, update, 0);
    glutTimerFunc(0, updatePower, 0);
    glutTimerFunc(0, update_cross, 0);
    glutKeyboardFunc(keyboard);
    printf("enemy1: %.1f, %.1f\n", enemy1X, enemy1Y);

    glutMainLoop();

    return 0;
}
