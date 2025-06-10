#include "Utils.h"

int Utils::Window::width = 800;
int Utils::Window::heigth = 600;

sf::Texture Utils::Textures::soldierTextureLeft;
sf::Texture Utils::Textures::soldierTextureUp;
sf::Texture Utils::Textures::soldierTextureRight;
sf::Texture Utils::Textures::soldierTextureDown;

sf::Texture Utils::Textures::zombieTextureLeft;
sf::Texture Utils::Textures::zombieTextureUp;
sf::Texture Utils::Textures::zombieTextureRight;
sf::Texture Utils::Textures::zombieTextureDown;

sf::Texture Utils::Textures::shotHorizontal;
sf::Texture Utils::Textures::shotVertical;
sf::Texture Utils::Textures::health;

bool Utils::Textures::LoadTextures()
{
	bool result = zombieTextureLeft.loadFromFile("Res\\zombie\\zombieLeft.png");
	result &= zombieTextureUp.loadFromFile("Res\\zombie\\zombieUp.png");
	result &= zombieTextureRight.loadFromFile("Res\\zombie\\zombieRight.png");
	result &= zombieTextureDown.loadFromFile("Res\\zombie\\zombieDown.png");
	result &= soldierTextureLeft.loadFromFile("Res\\soldier\\soldierLeft.png");
	result &= soldierTextureUp.loadFromFile("Res\\soldier\\soldierUp.png");
	result &= soldierTextureRight.loadFromFile("Res\\soldier\\soldierRight.png");
	result &= soldierTextureDown.loadFromFile("Res\\soldier\\soldierDown.png");
	result &= shotHorizontal.loadFromFile("Res\\shot\\shotHorizontal.png");
	result &= shotVertical.loadFromFile("Res\\shot\\shotVertical.png");
	result &= health.loadFromFile("Res\\bonuses\\health.png");

	return result;
}

bool Utils::Window::IsInWindow(int x, int y, int sizeX, int sizeY)
{
	if (x + sizeX > width || x < 0 || y < 0 || y + sizeY > heigth)
		return false;

	return true;
}
