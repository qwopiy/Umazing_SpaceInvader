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

class Explosion {
public: 
	Vector3 pos;
	float duration;
	float elapsedTime;
	void update(float deltaTime) {
		radius += 0.1f * deltaTime;
		elapsedTime += deltaTime;
	};
	void draw() {
		// Draw explosion effect (placeholder)
		glBegin(GL_POLYGON);
		glColor3f(1, 0.5f, 0);
		int numSegments = 100;
		for (int i = 0; i < numSegments; ++i) {
			float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
			float dx = radius * cosf(theta);
			float dy = radius * sinf(theta);
			glVertex3f(pos.x + dx, pos.y + dy, pos.z);
		}
		glEnd();
	};
	Explosion(Vector3 position, float duration) {
		this->pos = Vector3(position.x, position.y, position.z + 0.01f);
		this->duration = duration;
		this->elapsedTime = 0.0f;
	};
private:
    float radius = 0.0f;
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
    }

    void draw() {
        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex3f(pos.x - 0.01f, pos.y + 0.02f, pos.z);
        glVertex3f(pos.x + 0.01f, pos.y + 0.02f, pos.z);
        glVertex3f(pos.x + 0.01f, pos.y - 0.02f, pos.z);
        glVertex3f(pos.x - 0.01f, pos.y - 0.02f, pos.z);
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
vector<Explosion> explosions;

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
	if (!explosions.empty()) {
		for (Explosion& explosion : explosions)
		{
			explosion.draw();
		}
	}

    glBegin(GL_QUADS);

    // =====================================================
    // 1. FRAME DEPAN 
    // =====================================================

    float fx1 = -1.2f, fx2 = 1.2f;
    float fy1 = -1.2f, fy2 = 1.2f;
    float fz  = 1.1f;

    glColor3f(0.2f, 0.2f, 0.2f);
    // FRAME DEPAN – hitam metal
    //glColor3f(0.1f, 0.1f, 0.1f);

    // Atas
    glVertex3f(fx1, fy2, fz);
    glVertex3f(fx2, fy2, fz);
    glVertex3f(fx2, 1.0f, fz);
    glVertex3f(fx1, 1.0f, fz);

    // Bawah
    glVertex3f(fx1, -1.0f, fz);
    glVertex3f(fx2, -1.0f, fz);
    glVertex3f(fx2, fy1, fz);
    glVertex3f(fx1, fy1, fz);

    // Kiri
    glVertex3f(fx1, -1.1f, fz);
    glVertex3f(-1.0f, -1.1f, fz);
    glVertex3f(-1.0f, 1.1f, fz);
    glVertex3f(fx1, 1.1f, fz);

    // Kanan
    glVertex3f(1.0f, -1.1f, fz);
    glVertex3f(fx2, -1.1f, fz);
    glVertex3f(fx2, 1.1f, fz);
    glVertex3f(1.0f, 1.1f, fz);

    // =====================================================
    // 2. Back Cover Frame
    // =====================================================

    float backZ = -1.6f;

    //glColor3f(0.15f, 0.15f, 0.15f);
    // BACK COVER – abu metal gelap
    glColor3f(0.15f, 0.15f, 0.17f);

    glVertex3f(-1.2f, -1.2f, backZ);
    glVertex3f(1.2f, -1.2f, backZ);
    glVertex3f(1.2f, 1.2f, backZ);
    glVertex3f(-1.2f, 1.2f, backZ);

    // =====================================================
    // 3. BODY ATAS 
    // =====================================================

    
    // Samping kiri & kanan
    glColor3f(0.0f, 0.2f, 0.7f);

    // Kiri
    glVertex3f(-1.2f, -1.2f, backZ);
    glVertex3f(-1.2f, -1.2f, fz);
    glVertex3f(-1.2f, 1.2f, fz);
    glVertex3f(-1.2f, 1.2f, backZ);

    // Kanan
    glVertex3f(1.2f, -1.2f, backZ);
    glVertex3f(1.2f, -1.2f, fz);
    glVertex3f(1.2f, 1.2f, fz);
    glVertex3f(1.2f, 1.2f, backZ);

    // =====================================================
    // 4. ATAS BODY 
    // =====================================================

  
    glColor3f(0.0f, 0.1f, 0.3f);

    glVertex3f(-1.2f, 1.2f, backZ);
    glVertex3f(1.2f, 1.2f, backZ);
    glVertex3f(1.2f, 1.2f, fz);
    glVertex3f(-1.2f, 1.2f, fz);

    // =====================================================
	// 5. Kubus cabinet
    // =====================================================
    float lcX1 = -1.2f, lcX2 = 1.2f;
    float lcTopY = -1.2f;
    float lcBotY = -2.0f;
    float lcFrontZ = 1.1f;
    float lcBackZ  = -1.6f;


    // Depan
    glColor3f(0.0f, 0.25f, 0.9f);
    glVertex3f(lcX1, lcBotY, lcFrontZ);
    glVertex3f(lcX2, lcBotY, lcFrontZ);
    glVertex3f(lcX2, lcTopY, lcFrontZ);
    glVertex3f(lcX1, lcTopY, lcFrontZ);

    // Belakang
    glColor3f(0.0f, 0.15f, 0.5f);
    glVertex3f(lcX1, lcBotY, lcBackZ);
    glVertex3f(lcX2, lcBotY, lcBackZ);
    glVertex3f(lcX2, lcTopY, lcBackZ);
    glVertex3f(lcX1, lcTopY, lcBackZ);

    // Kiri 
    glColor3f(0.0f, 0.20f, 0.7f);

    glVertex3f(lcX1, lcBotY, lcBackZ);
    glVertex3f(lcX1, lcBotY, lcFrontZ);
    glVertex3f(lcX1, lcTopY, lcFrontZ);
    glVertex3f(lcX1, lcTopY, lcBackZ);

    // Kanan
    glColor3f(0.0f, 0.20f, 0.7f);
    glVertex3f(lcX2, lcBotY, lcFrontZ);
    glVertex3f(lcX2, lcBotY, lcBackZ);
    glVertex3f(lcX2, lcTopY, lcBackZ);
    glVertex3f(lcX2, lcTopY, lcFrontZ);

    // ATAS cabinet 
    glColor3f(0.05f, 0.05f, 0.1f);
    glVertex3f(lcX1, lcTopY, lcBackZ);
    glVertex3f(lcX2, lcTopY, lcBackZ);
    glVertex3f(lcX2, lcTopY, lcFrontZ);
    glVertex3f(lcX1, lcTopY, lcFrontZ);

    // BAWAH cabinet 
    glColor3f(0.02f, 0.02f, 0.05f);
    glVertex3f(lcX1, lcBotY, lcBackZ);
    glVertex3f(lcX2, lcBotY, lcBackZ);
    glVertex3f(lcX2, lcBotY, lcFrontZ);
    glVertex3f(lcX1, lcBotY, lcFrontZ);

    glEnd();


    // =====================================================
    // 6. TRAPESIUM 3D (control panel)
    // =====================================================

    float pX1 = -1.2f, pX2 = 1.2f;
    float pYBot = -2.0f, pYTop = -1.2f;
    float pZBack = 1.1f, pZFront = 2.0f;


    // 1. BAWAH
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.0f);   

    glVertex3f(pX1, pYBot, pZBack);
    glVertex3f(pX2, pYBot, pZBack);
    glVertex3f(pX2, pYBot, pZFront);
    glVertex3f(pX1, pYBot, pZFront);
    glEnd();

    // 2. BELAKANG
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.5f);  
    glVertex3f(pX1, pYBot, pZBack);
    glVertex3f(pX2, pYBot, pZBack);
    glVertex3f(pX2, pYTop, pZBack);
    glVertex3f(pX1, pYTop, pZBack);
    glEnd();

    // 3. DEPAN MIRING
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.2f); 
    glVertex3f(pX1, pYTop, pZBack);
    glVertex3f(pX2, pYTop, pZBack);
    glVertex3f(pX2, pYBot, pZFront);
    glVertex3f(pX1, pYBot, pZFront);
    glEnd();

    // 4. KANAN (segitiga)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.35f, 0.0f); 
    glVertex3f(pX2, pYBot, pZBack);
    glVertex3f(pX2, pYBot, pZFront);
    glVertex3f(pX2, pYTop, pZBack);
    glEnd();

    // 5. KIRI (segitiga)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.35f, 0.0f); 
    glVertex3f(pX1, pYBot, pZBack);
    glVertex3f(pX1, pYBot, pZFront);
    glVertex3f(pX1, pYTop, pZBack);
    glEnd();


    // =====================================================
    // 7. KUBUS BAWAH 
    // =====================================================

    float bx1 = lcX1, bx2 = lcX2;
    float bTopY = lcBotY;
    float bBotY = -4.8f;
    float bFrontZ = 2.0f;
    float bBackZ = lcBackZ;

    glBegin(GL_QUADS);

    // Depan
    glColor3f(0.0f, 0.20f, 0.7f);

    glVertex3f(bx1, bBotY, bFrontZ);
    glVertex3f(bx2, bBotY, bFrontZ);
    glVertex3f(bx2, bTopY, bFrontZ);
    glVertex3f(bx1, bTopY, bFrontZ);

    // Belakang

    glColor3f(0.0f, 0.20f, 0.7f);

    glVertex3f(bx1, bBotY, bBackZ);
    glVertex3f(bx2, bBotY, bBackZ);
    glVertex3f(bx2, bTopY, bBackZ);
    glVertex3f(bx1, bTopY, bBackZ);

    // Kiri
    glColor3f(0.0f, 0.20f, 0.7f);

    glVertex3f(bx1, bBotY, bBackZ);
    glVertex3f(bx1, bBotY, bFrontZ);
    glVertex3f(bx1, bTopY, bFrontZ);
    glVertex3f(bx1, bTopY, bBackZ);

    // Kanan
    glColor3f(0.0f, 0.20f, 0.7f);

    glVertex3f(bx2, bBotY, bFrontZ);
    glVertex3f(bx2, bBotY, bBackZ);
    glVertex3f(bx2, bTopY, bBackZ);
    glVertex3f(bx2, bTopY, bFrontZ);

    // Atas
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex3f(bx1, bTopY,  bBackZ);
    glVertex3f(bx2, bTopY,  bBackZ);
    glVertex3f(bx2, bTopY,  bFrontZ);
    glVertex3f(bx1, bTopY,  bFrontZ);

    // Bawah
    glColor3f(0.01f, 0.01f, 0.01f);
    glVertex3f(bx1, bBotY, bBackZ);
    glVertex3f(bx2, bBotY, bBackZ);
    glVertex3f(bx2, bBotY, bFrontZ);
    glVertex3f(bx1, bBotY, bFrontZ);

    glEnd();

     //// MERAH 
     //glColor3f(1, 0, 0);
     //glVertex3f(-1, -1, 1);
     //glVertex3f(1, -1, 1);
     //glVertex3f(1, 1, 1);
     //glVertex3f(-1, 1, 1);

    

}

void display() {
    glDisable(GL_CULL_FACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, 0, 9,// Posisi kamera. eye X, eye Y, eye Z.
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

	// update enemies movement setiap detik
	timeElapsed += deltaTime;

    if (timeElapsed > 1) {
		timeElapsed -= 1;
        for (Enemy& enemy : enemies)
        {
            enemy.move();
        }
    }

	// update bullets
    for (int i = playerBullets.size() - 1; i >= 0; --i) {
        playerBullets[i].update(deltaTime);

        // bullet max range
        if (playerBullets[i].pos.y > 1.0f) {
            playerBullets.erase(playerBullets.begin() + i);
            continue;
        }

        // Check collision dengan enemies
        bool bulletHit = false;
        for (int j = enemies.size() - 1; j >= 0; --j) {
            Enemy& e = enemies[j];
            // AABB collision
            if (playerBullets[i].pos.x > e.a.x && playerBullets[i].pos.x < e.b.x &&
                playerBullets[i].pos.y < e.a.y && playerBullets[i].pos.y > e.d.y) {
				// Create explosion
				explosions.push_back(Explosion(e.pos, 0.5f));
                // Remove enemy and bullet
                enemies.erase(enemies.begin() + j);
                playerBullets.erase(playerBullets.begin() + i);
                bulletHit = true;
                break;
            }
        }
        if (bulletHit) continue; 
    }

	// update explosions
	for (int i = explosions.size() - 1; i >= 0; --i) {
		explosions[i].update(deltaTime);
		if (explosions[i].elapsedTime > explosions[i].duration) {
			explosions.erase(explosions.begin() + i);
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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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