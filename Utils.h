#pragma once
#include <SFML/Graphics.hpp>

namespace Utils
{
	namespace Window
	{
		bool IsInWindow(int x, int y, int sizeX, int sizeY);

		extern int width; // extern wymagany w celu zaalokowania jednego globalnego obiektu
		extern int heigth;
	}

	namespace Textures
	{
		bool LoadTextures();
		//globalne obiekty tekstur - ³adowane raz, wykorzystywane przez wszystkie obiekty
		extern sf::Texture soldierTextureLeft;
		extern sf::Texture soldierTextureUp;
		extern sf::Texture soldierTextureRight;
		extern sf::Texture soldierTextureDown;
		extern sf::Texture zombieTextureLeft;
		extern sf::Texture zombieTextureUp;
		extern sf::Texture zombieTextureRight;
		extern sf::Texture zombieTextureDown;
		extern sf::Texture shotHorizontal;
		extern sf::Texture shotVertical;
		extern sf::Texture health;
	}
}
