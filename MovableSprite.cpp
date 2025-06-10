#include "MovableSprite.h"
#include "Utils.h"

bool MovableSprite::Move(int x, int y)
{
	if (Utils::Window::IsInWindow(getPosition().x + x, getPosition().y + y, getTexture()->getSize().x, getTexture()->getSize().y))
	{
		move(x, y);
		return true;
	}
	return false;
}

bool MovableSprite::IsTouching(const MovableSprite& another)
{
	return getGlobalBounds().intersects(another.getGlobalBounds()); // true jeœli prostok¹ty nachodz¹ na siebie
}
