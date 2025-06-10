#pragma once
#include <list>
#include <memory>
#include "Zombie.h"
#include "Player.h"
#include "Bonus.h"
#include "Shot.h"
#include <SFML/Audio.hpp>

enum class GameState
{
	Menu = 0,
	Playing,
	Pause,
	Lost
};

enum class MenuOption
{
	Play = 0,
	Level,
	Volume
};

class Game
{
public:
	bool Init(); // wo³aæ przed rozpoczêciem gry	
	bool Run(); // pêtla gry

private:
	void Draw(); // rysowanie sfml
	void Update(); // aktualizacja rozgrywki
	// aktualizacje poszczególnych elementów
	void UpdateMenu();
	void UpdateGame();
	void UpdateShots();
	void UpdateBonuses();
	void MoveZombies();
	void GenerateZombies();
	void ResetAll(); // przywrócenie domyœlnych ustawieñ

	sf::RenderWindow m_window;
	sf::Event m_event;

	GameState m_state = GameState::Menu;

	Player m_player;
	std::list<Zombie> m_zombies;
	std::list<std::unique_ptr<Bonus>> m_bonuses;
	std::list<Shot> m_shots;

	bool m_rightDir = true;
	bool m_leftDir = false;
	bool m_downDir = false;
	bool m_upDir = false;

	sf::Font m_font;
	sf::Text m_playText;
	sf::Text m_levelText;
	sf::Text m_volumeText;
	sf::Text m_pointsText;
	sf::Text m_healthText;
	sf::Text m_loseText;

	int m_points = 0;
	std::uint64_t m_lastTime = 0;
	MenuOption m_menuOption = MenuOption::Play;

	int m_difficultyLevel = 1;
	int m_volumeLevel = 1;

	sf::Clock m_keyboardDelay;
	sf::Clock m_zombiesSpawnsDelay;
	int m_zombiesSpawns = 2000;
	sf::Clock m_shotPauseDelay;
	int m_shotPause = 500;
	sf::Clock m_loseDelay;
	float m_spawnDistanceFactor = 2.0;
	sf::Clock m_bonusDelay;

	sf::Music m_sound;
};

