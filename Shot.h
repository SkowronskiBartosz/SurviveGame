#pragma once
#include "MovableSprite.h"
class Shot :
	public MovableSprite
{
public:
	Shot(int x, int y, bool left, bool right, bool up, bool down);
	~Shot() = default;
	bool Move();
private:
	bool m_rightDir = false;
	bool m_downDir = false;
	bool m_upDir = false;
	bool m_leftDir = false;
};

