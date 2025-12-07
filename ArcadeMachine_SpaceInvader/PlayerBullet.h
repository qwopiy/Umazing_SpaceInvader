#pragma once
#include "Vector3.h"

class PlayerBullet {
public:
	Vector3 pos;

	void update(float deltaTime);
	void draw();

	PlayerBullet(Vector3);
private:
	float moveSpeed;
};