#include "HealthBonus.h"
#include "Utils.h"

HealthBonus::HealthBonus(int x, int y)
{
	setPosition(x, y);
	setTexture(Utils::Textures::health);
}

void HealthBonus::DoAction(Player & player)
{
	player.AddHealth();
}
