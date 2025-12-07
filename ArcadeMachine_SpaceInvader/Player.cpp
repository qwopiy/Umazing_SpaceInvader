#include "Player.h"
#include "Vector2.h"
#include "Vector3.h"
#include <glut.h>

Player::Player() {
	health = 3;
	isMovingLeft = false;
	isMovingRight = false;
	pos = Vector2(0.0f, 0.0f);
	width = 0.2f;
	height = 0.1f;
	moveSpeed = 0.001f;
	zOffset = 0.51f; // sedikit di depan game screen
}

void Player::start() {
	
}

void Player::update(Vector2 newPos) {
	pos = newPos;
}

void Player::move(float deltaTime) {
	if (isMovingLeft && isMovingRight) {
		return;
	}
	if (isMovingLeft) {
		pos.x -= moveSpeed * deltaTime;
	}
	if (isMovingRight) {
		pos.x += moveSpeed * deltaTime;
	}
}

void Player::draw() {
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
	Vector3 a = Vector3(pos.x - width / 2, pos.y + height / 2, zOffset);
	Vector3 b = Vector3(pos.x + width / 2, pos.y + height / 2, zOffset);
	Vector3 c = Vector3(pos.x + width / 2, pos.y - height / 2, zOffset);
	Vector3 d = Vector3(pos.x - width / 2, pos.y - height / 2, zOffset);

	
	Vector3 pA = Vector3(pos.x, pos.y + height / 2 + width * 0.2, zOffset);
	Vector3 pB = Vector3(pos.x + width * 0.1, pos.y + height / 2, zOffset);
	Vector3 pC = Vector3(pos.x - width * 0.1, pos.y + height / 2, zOffset);


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
}