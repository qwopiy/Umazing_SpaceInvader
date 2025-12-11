#include <glut.h>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct Vector3 {
    float x;
    float y;
    float z;

    void toGLVertex2f() {
        glVertex2f(this->x, this->y);
    };

    void toGLVertex3f() {
		glVertex3f(this->x, this->y, this->z);
    };

    void Vertex2f(Vector3 v) {
        glVertex2f(v.x, v.y);
    };

    void Vertex3f(Vector3 v) {
        glVertex3f(v.x, v.y, v.z);
    };

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };
    Vector3(int x, int y, int z) {
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
		this->z = static_cast<float>(z);
    };
    Vector3() {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    };
};

class Enemy {
public:
    Vector3 pos;
    Vector3 a;
    Vector3 b;
    Vector3 c;
    Vector3 d;

    void move() {
        pos.x += movespeed * direction;

        if (pos.x > startPos.x + moveAmplitude) {
            direction = -1.0f;
            pos.y -= 0.1f;
        }
        else if (pos.x < startPos.x) {
            direction = 1.0f;
            pos.y -= 0.1f;
        }

        a = { (pos.x - width / 2), (pos.y + height / 2), pos.z };
        b = { (pos.x + width / 2), (pos.y + height / 2), pos.z };
        c = { (pos.x + width / 2), (pos.y - height / 2), pos.z };
        d = { (pos.x - width / 2), (pos.y - height / 2), pos.z };
    };

    void draw() {
        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        a.toGLVertex3f();
        b.toGLVertex3f();
        c.toGLVertex3f();
        d.toGLVertex3f();
        glEnd();
    };
    void die();

    Enemy(Vector3 startPos, float width, float height) {
        this->startPos = startPos;
        pos = startPos;
        this->width = width;
        this->height = height;

        moveAmplitude = 0.5f;
        movespeed = 0.02f;
        direction = 1.0f;
        a = { (pos.x - width / 2), (pos.y + height / 2), pos.z };
        b = { (pos.x + width / 2), (pos.y + height / 2), pos.z };
        c = { (pos.x + width / 2), (pos.y - height / 2), pos.z };
        d = { (pos.x - width / 2), (pos.y - height / 2), pos.z };
    };

private:
    Vector3 startPos;
    float width;
    float height;
    float moveAmplitude;
    float movespeed;
    float direction;
};

class GameScreen {
public:
    // attributes
    float screenHeight;
    float screenWidth;
    float zOffset;

    // methods
    void draw() {
        glBegin(GL_QUADS);

        glColor3f(0, 0, 0);
        a.toGLVertex3f();
        b.toGLVertex3f();
        c.toGLVertex3f();
        d.toGLVertex3f();
        glEnd();
    };

    // constructor
    GameScreen() {
        screenHeight = 2;
        screenWidth = 2;
        zOffset = 1.0f;
        a = Vector3(-screenWidth / 2, screenHeight / 2, zOffset);
        b = Vector3(screenWidth / 2, screenHeight / 2, zOffset);
        c = Vector3(screenWidth / 2, -screenHeight / 2, zOffset);
        d = Vector3(-screenWidth / 2, -screenHeight / 2, zOffset);
    };
private:
    // Screen corners
    Vector3 a;
    Vector3 b;
    Vector3 c;
    Vector3 d;
};

class Player {
public:
    // attributes
    int health;
    bool isMovingLeft;
    bool isMovingRight;
    Vector3 pos;

    // methods
    void start();
    void update(Vector3 newPos) {
        pos = newPos;
    };
    void move(float deltaTime) {
        if (isMovingLeft && isMovingRight) {
            return;
        }
        if (isMovingLeft) {
            pos.x -= moveSpeed * deltaTime;
        }
        if (isMovingRight) {
            pos.x += moveSpeed * deltaTime;
        }
    };
    void draw() {
        /*
        *
        *	 bentuk Tanknya
        *
        *			 pA
        *			/  \
        *	a-----pC----pB-----b
        *	|				   |
        *	|				   |
        *	d------------------c
        *
        *
        */
        // Square Corners
        Vector3 a = Vector3(pos.x - width / 2, pos.y + height / 2, pos.z);
        Vector3 b = Vector3(pos.x + width / 2, pos.y + height / 2, pos.z);
        Vector3 c = Vector3(pos.x + width / 2, pos.y - height / 2, pos.z);
        Vector3 d = Vector3(pos.x - width / 2, pos.y - height / 2, pos.z);


        Vector3 pA = Vector3(pos.x, pos.y + height / 2 + width * 0.2, pos.z);
        Vector3 pB = Vector3(pos.x + width * 0.1, pos.y + height / 2, pos.z);
        Vector3 pC = Vector3(pos.x - width * 0.1, pos.y + height / 2, pos.z);


        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        a.toGLVertex3f();
        b.toGLVertex3f();
        c.toGLVertex3f();
        d.toGLVertex3f();
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0, 1, 0);
        pA.toGLVertex3f();
        pB.toGLVertex3f();
        pC.toGLVertex3f();
        glEnd();
    };

    // constructor
    Player() {
        float zOffset = 1.01f; // sedikit di depan game screen
        health = 3;
        isMovingLeft = false;
        isMovingRight = false;
        pos = Vector3(0.0f, -0.7f, zOffset);
        width = 0.2f;
        height = 0.1f;
        moveSpeed = 1.0f;
    };
private:
    float width;
    float height;
    float moveSpeed;
};

class PlayerBullet {
public:
    Vector3 pos;

    void update(float deltaTime) {
        pos.y += moveSpeed * deltaTime;
    };

    void draw() {
        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex3f(pos.x - 0.01f, pos.y + 0.02f, pos.z + 0.1f);
        glVertex3f(pos.x + 0.01f, pos.y + 0.02f, pos.z + 0.1f);
        glVertex3f(pos.x + 0.01f, pos.y - 0.02f, pos.z + 0.1f);
        glVertex3f(pos.x - 0.01f, pos.y - 0.02f, pos.z + 0.1f);
        glEnd();
    };

    PlayerBullet(Vector3 playerPos) {
        pos = playerPos;
        moveSpeed = 1.0f;
    };
private:
    float moveSpeed;
};

float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

GameScreen gameScreen;
Player player;
vector<PlayerBullet> playerBullets; 
vector<Enemy> enemies;

float deltaTime = 0.0f;
float oldTimeSinceStart = 0.0f;
float timeElapsed = 0.0f;
float enemyMoveInterval = 1.0f;

void initEnemies() {
    float startY = 0.7f;
    float spacingY = 0.2f;
    float startX = -0.8f;
    float spacingX = 0.3f;
    int rows = 3;
    int cols = 5;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Vector3 enemyPos = Vector3(startX + j * spacingX, startY - i * spacingY, 1.01f);
            enemies.push_back(Enemy(enemyPos, 0.1f, 0.1f));
        }
    }
}

void draw() {
	gameScreen.draw();
	player.draw();
    if (!playerBullets.empty()) {
        for (PlayerBullet& pb : playerBullets)
        {
            pb.draw();
        }
    }
    if (!enemies.empty()) {
        for (Enemy& enemy : enemies)
        {
            enemy.draw();
        }
    }


    glBegin(GL_QUADS);

    //// MERAH 
    //glColor3f(1, 0, 0);
    //glVertex3f(-1, -1, 1);
    //glVertex3f(1, -1, 1);
    //glVertex3f(1, 1, 1);
    //glVertex3f(-1, 1, 1);

    // HIJAU
    glColor3f(0, 1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    // BIRU
    glColor3f(0, 0, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);

    //KUNING
    glColor3f(1, 1, 0);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    // MAGENTA
    glColor3f(1, 0, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    // CYAN
    glColor3f(0, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, 0, 3,// Posisi kamera. eye X, eye Y, eye Z.
        0, 0, 0,  // Titik fokus kamera
        0, 1, 0); // Vektor "up" kamera

    // Rotasi pada setiap sumbu
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);

    draw();
    glutSwapBuffers();
}

void updateDeltaTime() {
    float timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (timeSinceStart - oldTimeSinceStart) / 1000.0f;
    oldTimeSinceStart = timeSinceStart;
}

void update() {
    glutPostRedisplay();
    updateDeltaTime();

    // update player
    player.move(deltaTime);

    // update player bullets (kalo ada)
    for (int i = playerBullets.size() - 1; i >= 0; --i)
    {
        playerBullets[i].update(deltaTime);
        //cout << fixed << setprecision(2) << "Bullet Position Y: " << playerBullets[i].pos.y << endl;
        if (playerBullets[i].pos.y > 1.0f) {
            playerBullets.erase(playerBullets.begin() + i);
        }
    }

	// update enemies movement setiap detik
	timeElapsed += deltaTime;

    if (timeElapsed > 1) {
		timeElapsed -= 1;
        for (Enemy& enemy : enemies)
        {
            enemy.move();
        }
    }
}


// Fungsi menangani ukuran window
void reshape(int width, int height) {
    if (height == 0) height = 1; // hindari pembagian nol
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height); // atur area tampilan
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0,    // FOV (field of view)
        aspect,  // Aspect ratio
        0.1,     // Near clipping plane
        100.0);  // Far clipping plane
    glMatrixMode(GL_MODELVIEW);
}

// TODO: buat gerak kamera makin fluid

void keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': angleX -= 5.0f; break;
    case 's': angleX += 5.0f; break;
    case 'a': angleY -= 5.0f; break;
    case 'd': angleY += 5.0f; break;
    case 'q': angleZ -= 5.0f; break;
    case 'e': angleZ += 5.0f; break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': angleX -= 5.0f; break;
    case 's': angleX += 5.0f; break;
    case 'a': angleY -= 5.0f; break;
    case 'd': angleY += 5.0f; break;
    case 'q': angleZ -= 5.0f; break;
    case 'e': angleZ += 5.0f; break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void keyboardSpecialDown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
		cout << "Fire!" << endl;
		playerBullets.push_back(PlayerBullet(player.pos));
		break;
    case GLUT_KEY_LEFT:
        player.isMovingLeft = true;
        break;
    case GLUT_KEY_RIGHT:
        player.isMovingRight = true;
        break;
    }
}

void keyboardSpecialUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		player.isMovingLeft = false;
		break;
	case GLUT_KEY_RIGHT:
		player.isMovingRight = false;
		break;
	}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Cube - Control with ASDW + QE for Z Rotation");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	initEnemies();

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(keyboardSpecialDown);
	glutSpecialUpFunc(keyboardSpecialUp);

    glutMainLoop();

    return 0;
}