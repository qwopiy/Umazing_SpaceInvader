#pragma once
#include "Vector3.h"

class Player {
public:
	// attributes
	int health;
	bool isMovingLeft;
	bool isMovingRight;
	Vector3 pos;

	// methods
	void start();
	void update(Vector3 newPos);
	void move(float deltaTime);
	void draw();

	// constructor
	Player();
private:
	float width;
	float height;
	float moveSpeed;
};