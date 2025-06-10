#pragma once
#include <SFML/Graphics.hpp>
class MovableSprite : public sf::Sprite // klasa bazowa wszystkich element�w mog�cych si� rusza�
{
public:
	virtual bool Move(int x, int y);
	bool IsTouching(const MovableSprite& another);
};

