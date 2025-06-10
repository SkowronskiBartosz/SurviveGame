#pragma once
#include <SFML/Graphics.hpp>
class MovableSprite : public sf::Sprite // klasa bazowa wszystkich elementów mog¹cych siê ruszaæ
{
public:
	virtual bool Move(int x, int y);
	bool IsTouching(const MovableSprite& another);
};

