#pragma once
#include "MovableSprite.h"

class Zombie : public MovableSprite
{
public:
	Zombie(int x, int y);
	~Zombie() = default;

	bool Move(bool left, bool right, bool up, bool down);
};

