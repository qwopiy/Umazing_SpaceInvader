#include "Vector3.h"
Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(int x, int y, int z) {
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
	this->z = static_cast<float>(z);
}

Vector3::Vector3() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

void Vector3::toGLVertex2f() {
	glVertex2f(this->x, this->y);
}
void Vector3::toGLVertex3f() {
	glVertex3f(this->x, this->y, this->z);
}

void Vector3::Vertex2f(Vector3 v) {
	glVertex2f(v.x, v.y);
}
void Vector3::Vertex3f(Vector3 v) {
	glVertex3f(v.x, v.y, v.z);
}