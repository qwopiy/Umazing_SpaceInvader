#pragma once
#include <glut.h>
#include "Vector3.h"

struct Vector2 {
	float x;
	float y;

	void toGLVertex2f();
	void toGLVertex3f();

	void Vertex2f(Vector2 v);
	void Vertex3f(Vector2 v);

	Vector3 toVector3();

	Vector2(float x, float y);
	Vector2(int x, int y);
	Vector2();
};