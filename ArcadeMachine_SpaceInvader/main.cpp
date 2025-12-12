#include "Vector3.h"
#include "GameScreen.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include <glut.h>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

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