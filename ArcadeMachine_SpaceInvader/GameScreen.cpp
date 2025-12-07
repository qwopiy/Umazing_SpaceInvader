#include "GameScreen.h"
#include <glut.h>

GameScreen::GameScreen() {
	screenHeight = 1;
	screenWidth = 1;
	zOffset = 0.5f;
	a = Vector3(-screenWidth / 2, screenHeight / 2, zOffset);
	b = Vector3(screenWidth / 2, screenHeight / 2, zOffset);
	c = Vector3(screenWidth / 2, -screenHeight / 2, zOffset);
	d = Vector3(-screenWidth / 2, -screenHeight / 2, zOffset);
}

void GameScreen::draw() {
	glBegin(GL_QUADS);

	glColor3f(0, 0, 0);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glVertex3f(d.x, d.y, d.z);
	glEnd();
}