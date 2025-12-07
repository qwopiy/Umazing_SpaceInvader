#include "Enemy.h"
#include "PlayerBullet.h"
#include <vector>

Enemy::Enemy(Vector3 startPos, float width, float height) {
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
}

void Enemy::draw() {
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	a.toGLVertex3f();
	b.toGLVertex3f();
	c.toGLVertex3f();
	d.toGLVertex3f();
	glEnd();
}

void Enemy::move() {
	pos.x += movespeed * direction;

	if (pos.x > startPos.x + moveAmplitude) {
		direction = -1.0f;
		pos.y -= 0.1f;
	}
	else if (pos.x < startPos.x ) {
		direction = 1.0f;
		pos.y -= 0.1f;
	}

	a = { (pos.x - width / 2), (pos.y + height / 2), pos.z };
	b = { (pos.x + width / 2), (pos.y + height / 2), pos.z };
	c = { (pos.x + width / 2), (pos.y - height / 2), pos.z };
	d = { (pos.x - width / 2), (pos.y - height / 2), pos.z };
}