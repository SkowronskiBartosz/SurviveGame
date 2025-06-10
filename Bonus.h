#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Bonus : public sf::Sprite
{
public:
	virtual void DoAction(Player& player) = 0; // czysto wirtualna metoda, do nadpisania przez klasy pochodne w celu zdefiniowania akcji na graczu (plus HP, szybsze poruszanie itp.)
};

