#pragma once
#include "Vector3.h"

class GameScreen {
public:
	// attributes
	float screenHeight;
	float screenWidth;
	float zOffset;

	// methods
	void start();
	void update();
	void draw();

	// constructor
	GameScreen();
private:
	// Screen corners
	Vector3 a;
	Vector3 b;
	Vector3 c;
	Vector3 d;
};