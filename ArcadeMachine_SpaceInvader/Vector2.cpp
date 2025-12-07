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

void Vector2::toGLVertex2f() {
	glVertex2f(this->x, this->y);
}

void Vector2::toGLVertex3f() {
	glVertex3f(this->x, this->y, 0.0f);
}

void Vector2::Vertex2f(Vector2 v) {
	glVertex2f(v.x, v.y);
}

void Vector2::Vertex3f(Vector2 v) {
	glVertex3f(v.x, v.y, 0.0f);
}