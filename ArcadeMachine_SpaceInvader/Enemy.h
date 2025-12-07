#pragma once
#include "Vector3.h"

class Enemy {
public:
	Vector3 pos;
	Vector3 a;
	Vector3 b;
	Vector3 c;
	Vector3 d;

	void move();
	void draw();
	void die();

	Enemy(Vector3 startPos, float width, float height);
private:
	Vector3 startPos;
	float width;
	float height;
	float moveAmplitude;
	float movespeed;
	float direction;
};