#include "Player.h"
#include "Utils.h"

void Player::Init()
{
	setTexture(Utils::Textures::soldierTextureRight);
	setPosition(Utils::Window::width / 2 - getTexture()->getSize().x / 2, Utils::Window::heigth / 2 - getTexture()->getSize().y / 2);
}

void Player::AddHealth()
{
	++m_health;
}

bool Player::Move(int x, int y)
{
	if (x < 0)
		setTexture(Utils::Textures::soldierTextureLeft);

	if (x > 0)
		setTexture(Utils::Textures::soldierTextureRight);

	if (y < 0)
		setTexture(Utils::Textures::soldierTextureUp);

	if (y > 0)
		setTexture(Utils::Textures::soldierTextureDown);

	return MovableSprite::Move(x * 2, y * 2);
}

bool Player::Touched()
{
	m_health--;
	if (m_health == 0)
		return false;
	
	return true;
}

void Player::Reset()
{
	m_health = 5;
	setTexture(Utils::Textures::soldierTextureRight);
	setPosition(Utils::Window::width / 2 - getTexture()->getSize().x / 2, Utils::Window::heigth / 2 - getTexture()->getSize().y / 2);
}

int Player::GetHealth()
{
	return m_health;
}
