#include "Vector2.h"

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2(int x, int y) {
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
}

Vector2::Vector2() {
	this->x = 0.0f;
	this->y = 0.0f;
}