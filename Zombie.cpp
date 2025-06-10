#include "Zombie.h"
#include "Utils.h"

Zombie::Zombie(int x, int y)
{
	setPosition(x, y);
	setTexture(Utils::Textures::zombieTextureRight);
}

bool Zombie::Move(bool left, bool right, bool up, bool down)
{
	int x = left ? -1 : right ? 1 : 0;
	int y = up ? -1 : down ? 1 : 0;

	return MovableSprite::Move(x, y);
}
