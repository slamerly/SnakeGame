#pragma once
#include "raylib.h"

class Tail
{
private:
	Vector2 mPosition;
	Vector2 mSpeed;
	Color mColor;

public:
	Tail();
	Tail(Vector2 position, float size, Color color);
	~Tail();

	Vector2 GetPosition();
	Vector2 GetSpeed();
	Color GetColor();

	void SetPostion(Vector2 position);
	void SetSpeed(Vector2 speed);
};

