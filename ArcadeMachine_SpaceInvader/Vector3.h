#pragma once
#include <glut.h>
#include "Vector2.h"

struct Vector3 {
	float x;
	float y;
	float z;

	void toGLVertex2f();
	void toGLVertex3f();

	void Vertex2f(Vector3 v);
	void Vertex3f(Vector3 v);

	Vector2 toVector2();

	Vector3(float x, float y, float z);
	Vector3(int x, int y, int z);
	Vector3();
};