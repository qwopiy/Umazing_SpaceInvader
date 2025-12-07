#pragma once
#include "Vector2.h"

class Player {
public:
	// attributes
	int health;
	bool isMovingLeft;
	bool isMovingRight;

	// methods
	void start();
	void update(Vector2 newPos);
	void move(float deltaTime);
	void draw();

	// constructor
	Player();
private:
	Vector2 pos;
	float zOffset; // untuk game screen 3d
	float width;
	float height;
	float moveSpeed;
};