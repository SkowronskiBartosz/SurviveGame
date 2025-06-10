#include "Shot.h"
#include "Utils.h"

Shot::Shot(int x, int y, bool left, bool right, bool up, bool down) : m_leftDir(left) ,m_rightDir(right), m_upDir(up), m_downDir(down)
{
	setPosition(x, y);
	int xDir = m_rightDir ? 1 : m_leftDir ? -1 : 0; // kierunki s¹ niezbêdne ¿eby poprawnie rysowaæ animacje strza³u (wybór tesktury)
	int yDir = m_downDir ? 1 : m_upDir ? -1 : 0;
	if (xDir != 0)
		setTexture(Utils::Textures::shotHorizontal);
	else if (yDir != 0)
		setTexture(Utils::Textures::shotVertical);
}

bool Shot::Move()
{
	int x = m_rightDir ? 1 : m_leftDir ? -1 : 0;
	int y = m_downDir ? 1 : m_upDir ? -1 : 0;

	return MovableSprite::Move(x * 4, y * 4);
}
