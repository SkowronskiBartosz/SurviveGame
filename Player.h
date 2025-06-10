#pragma once
#include "MovableSprite.h"

class Player : public MovableSprite
{
public:
	void Init();
	void AddHealth();
	bool Move(int x, int y) override;
	bool Touched();
	void Reset();

	int GetHealth();
private:
	int m_health = 5;
};

