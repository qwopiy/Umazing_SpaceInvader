#include "PlayerBullet.h"
#include <glut.h>
#include <iostream>
#include <iomanip>

PlayerBullet::PlayerBullet(Vector3 playerPos) {
	pos = playerPos;
	moveSpeed = 1.0f;
}

void PlayerBullet::update(float deltaTime) {
	pos.y += moveSpeed * deltaTime;
}

void PlayerBullet::draw() {
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(pos.x - 0.01f, pos.y + 0.02f, pos.z + 0.1f);
	glVertex3f(pos.x + 0.01f, pos.y + 0.02f, pos.z + 0.1f);
	glVertex3f(pos.x + 0.01f, pos.y - 0.02f, pos.z + 0.1f);
	glVertex3f(pos.x - 0.01f, pos.y - 0.02f, pos.z + 0.1f);
	glEnd();
}