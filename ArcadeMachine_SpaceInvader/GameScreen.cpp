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
	a.toGLVertex3f();
	b.toGLVertex3f();
	c.toGLVertex3f();
	d.toGLVertex3f();
	glEnd();
}