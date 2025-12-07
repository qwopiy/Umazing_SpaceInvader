#include "Vector2.h"
#include "Vector3.h"
#include "GameScreen.h"
#include "Player.h"
#include <glut.h>

float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

GameScreen gameScreen;
Player player;

float deltaTime = 0.0f;
float oldTimeSinceStart = 0.0f;

void drawCube() {
	gameScreen.draw();
	player.draw();

    glBegin(GL_QUADS);

    //// MERAH 
    //glColor3f(1, 0, 0);
    //glVertex3f(-0.5, -0.5, 0.5);
    //glVertex3f(0.5, -0.5, 0.5);
    //glVertex3f(0.5, 0.5, 0.5);
    //glVertex3f(-0.5, 0.5, 0.5);

    // HIJAU
    glColor3f(0, 1, 0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // BIRU
    glColor3f(0, 0, 1);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    //KUNING
    glColor3f(1, 1, 0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);

    // MAGENTA
    glColor3f(1, 0, 1);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // CYAN
    glColor3f(0, 1, 1);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);

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

    drawCube();
    glutSwapBuffers();
}

void updateDeltaTime() {
    float timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;
}

void update() {
	glutPostRedisplay();
	updateDeltaTime();
	player.move(deltaTime);
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

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(keyboardSpecialDown);
	glutSpecialUpFunc(keyboardSpecialUp);

    glutMainLoop();

    return 0;
}