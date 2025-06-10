#pragma once
#include "Bonus.h"
#include "Player.h"

class HealthBonus :
	public Bonus
{
public:
	HealthBonus(int x, int y);
	HealthBonus() = default;

	void DoAction(Player& player) override;
};

