#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "Utils.h"
#include "HealthBonus.h"

int main()
{
	srand(static_cast<unsigned int>(time(0))); // inicjacja randa'a - ¿eby nie by³o powtarzalne

	Game game;
	bool keepRunning = game.Init(); // ³adowanie fontów, dŸwiêku, tekstur - je¿eli b³¹d - gra nie odpali siê

	while (keepRunning)
	{
		keepRunning = game.Run(); // g³ówna pêtla
	}

	return 0;
}

bool Game::Init()
{
	bool result = Utils::Textures::LoadTextures();
	result &= m_font.loadFromFile("Res\\fonts\\arial.ttf"); // and logiczny - true tylko jak wszystko bedzie ok
	result &= m_sound.openFromFile("Res\\audio\\audio.wav"); // uwaga - œcie¿ka wzglêdna! pliki powinny byæ w katalogu Res obok exe

	m_player.Init();

	m_playText.setFont(m_font);
	m_levelText.setFont(m_font);
	m_volumeText.setFont(m_font);
	m_pointsText.setFont(m_font);
	m_healthText.setFont(m_font);
	m_loseText.setFont(m_font);


	m_playText.setPosition(Utils::Window::width / 2 - 20, Utils::Window::heigth / 2 - 50);
	m_levelText.setPosition(Utils::Window::width / 2 - 20, Utils::Window::heigth / 2 - 20);
	m_volumeText.setPosition(Utils::Window::width / 2 - 20, Utils::Window::heigth / 2 + 10);
	m_pointsText.setPosition(10, 10);
	m_healthText.setPosition(Utils::Window::width / 2, 10);
	m_loseText.setPosition(20 / 2, Utils::Window::heigth / 2 - 50);

	m_playText.setString("Play");
	m_levelText.setString("Difficulty level: " + std::to_string(m_difficultyLevel));
	m_volumeText.setString("Volume: " + std::to_string(m_volumeLevel));
	m_pointsText.setString("Points: " + std::to_string(m_points));

	m_playText.setCharacterSize(28);
	m_levelText.setCharacterSize(28);
	m_volumeText.setCharacterSize(28);
	m_pointsText.setCharacterSize(28);
	m_healthText.setCharacterSize(28);
	m_loseText.setCharacterSize(40);

	m_playText.setFillColor(sf::Color::Red);
	m_levelText.setFillColor(sf::Color::White);
	m_volumeText.setFillColor(sf::Color::White);
	m_pointsText.setFillColor(sf::Color::White);
	m_healthText.setFillColor(sf::Color::White);
	m_loseText.setFillColor(sf::Color::Red);

	if (result)
	{
		m_window.create(sf::VideoMode(Utils::Window::width, Utils::Window::heigth), "Game");
		m_sound.play();
		m_sound.setVolume(m_volumeLevel);
	}

	m_window.setFramerateLimit(60);
	return result;
}

bool Game::Run()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window.close(); // wykrycie zamkniêcia aplikacji
	}

	Update();
	Draw();
	return m_window.isOpen();
}

void Game::Draw()
{
	m_window.clear();

	switch (m_state) // rysowanie elementów w zale¿noœci od aktualnego stanu gry
	{
	case GameState::Menu:
		m_window.draw(m_playText);
		m_window.draw(m_levelText);
		m_window.draw(m_volumeText);
		break;
	case GameState::Playing:
	case GameState::Pause:
		m_window.draw(m_player);
		m_window.draw(m_pointsText);
		m_healthText.setString("Health: " + std::to_string(m_player.GetHealth()));
		m_window.draw(m_healthText);

		for (const auto& zombie : m_zombies)
			m_window.draw(zombie);

		for (const auto& shot : m_shots)
			m_window.draw(shot);

		for (const auto& bonus : m_bonuses)
			m_window.draw(*bonus);

		break;
	case GameState::Lost:
		m_window.draw(m_loseText);
		break;
	default:
		break;
	}

	m_window.display();
}

void Game::Update()
{
	switch (m_state)
	{
	case GameState::Menu:
		UpdateMenu();
		break;
	case GameState::Playing:
		UpdateGame();
		break;
	case GameState::Pause:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_keyboardDelay.getElapsedTime() > sf::seconds(1)) // pauza z zabezpieczeniem przed wielokrotnym wejœciem (1 sekunda)
		{
			m_keyboardDelay.restart();
			m_state = GameState::Playing;
		}
		break;
	case GameState::Lost:
		m_window.draw(m_loseText);
		if (m_loseDelay.getElapsedTime() > sf::seconds(5))
		{
			ResetAll();
			m_state = GameState::Menu;
		}
		break;
	}
}

void Game::UpdateMenu()
{
	if (m_keyboardDelay.getElapsedTime() < sf::milliseconds(500)) // akceptuj przytrzymany klawisz co 500 ms
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_keyboardDelay.restart();
		m_playText.setFillColor(sf::Color::White);
		m_levelText.setFillColor(sf::Color::White);
		m_volumeText.setFillColor(sf::Color::White);

		switch (m_menuOption)
		{
		case MenuOption::Play:
			m_menuOption = MenuOption::Level;
			m_levelText.setFillColor(sf::Color::Red);
			break;
		case MenuOption::Level:
			m_menuOption = MenuOption::Volume;
			m_volumeText.setFillColor(sf::Color::Red);
			break;
		case MenuOption::Volume:
			m_menuOption = MenuOption::Play;
			m_playText.setFillColor(sf::Color::Red);
			break;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_keyboardDelay.restart();
		m_playText.setFillColor(sf::Color::White);
		m_levelText.setFillColor(sf::Color::White);
		m_volumeText.setFillColor(sf::Color::White);

		switch (m_menuOption)
		{
		case MenuOption::Play:
			m_menuOption = MenuOption::Volume;
			m_volumeText.setFillColor(sf::Color::Red);
			break;
		case MenuOption::Level:
			m_menuOption = MenuOption::Play;
			m_playText.setFillColor(sf::Color::Red);
			break;
		case MenuOption::Volume:
			m_menuOption = MenuOption::Level;
			m_levelText.setFillColor(sf::Color::Red);
			break;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_keyboardDelay.restart();
		switch (m_menuOption)
		{
		case MenuOption::Play:
			m_state = GameState::Playing;
			ResetAll();
			break;
		case MenuOption::Level:
			m_difficultyLevel = m_difficultyLevel < 3 ? ++m_difficultyLevel : 1;
			m_levelText.setString("Difficulty level: " + std::to_string(m_difficultyLevel));
			break;
		case MenuOption::Volume:
			m_volumeLevel = m_volumeLevel < 10 ? ++m_volumeLevel : 1;
			m_sound.setVolume(m_volumeLevel * 10);
			m_volumeText.setString("Volume: " + std::to_string(m_volumeLevel));
			break;
		}
	}
}

void Game::UpdateGame()
{
	UpdateShots();
	MoveZombies();
	GenerateZombies();
	UpdateBonuses();

	auto currentTime = time(0);
	if (currentTime != m_lastTime)
	{
		m_lastTime = currentTime;
		m_points++;
		m_pointsText.setString("Points: " + std::to_string(m_points));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_downDir = false; // kierunki niezbêdne do ustawienia poprawnej tekstury
		m_upDir = false;
		m_rightDir = false;
		m_leftDir = true;
		m_player.Move(-1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_downDir = false;
		m_upDir = false;
		m_leftDir = false;
		m_rightDir = true;
		m_player.Move(1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_downDir = false;
		m_rightDir = false;
		m_leftDir = false;
		m_upDir = true;
		m_player.Move(0, -1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_rightDir = false;
		m_leftDir = false;
		m_upDir = false;
		m_downDir = true;
		m_player.Move(0, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_shotPauseDelay.getElapsedTime() > sf::milliseconds(m_shotPause))
	{
		m_shotPauseDelay.restart();
		m_shots.emplace_back(m_player.getPosition().x + m_player.getTexture()->getSize().x / 2,
			m_player.getPosition().y + m_player.getTexture()->getSize().y / 2,
			m_leftDir, m_rightDir, m_upDir, m_downDir);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_keyboardDelay.getElapsedTime() > sf::seconds(1))
	{
		m_keyboardDelay.restart();
		m_state = GameState::Pause;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && m_keyboardDelay.getElapsedTime() > sf::seconds(1))
	{
		m_keyboardDelay.restart();
		ResetAll();
	}
}

void Game::UpdateShots()
{
	for (auto it = m_shots.begin(); it != m_shots.end();)
	{
		bool shotted = false;
		for (auto zit = m_zombies.begin(); zit != m_zombies.end();)
		{
			if (it->IsTouching(*zit))
			{
				zit = m_zombies.erase(zit); // aktualizacja iteratora jest niezbêdna - po usuniêciu elementu elementy wektora s¹ przesuwane - iteratory siê zmieniaj¹
				shotted = true;
				break;
			}
			else
				++zit;
		}

		if (shotted || !it->Move())
			it = m_shots.erase(it); // aktualizacja iteratora jest niezbêdna - po usuniêciu elementu elementy wektora s¹ przesuwane - iteratory siê zmieniaj¹
		else
			++it;
	}
}

void Game::UpdateBonuses()
{
	if (m_bonusDelay.getElapsedTime() > sf::seconds(15)) // bonus co 15 sekund
	{
		m_bonusDelay.restart();
		m_bonuses.emplace_back(std::make_unique<HealthBonus>(rand() % Utils::Window::width, rand() % Utils::Window::heigth)); // wrzucenie w losowe miejsce - unique_ptr z polimorfizmem (klasa wirtualna Bonuses)
	}

	for (auto it = m_bonuses.begin(); it != m_bonuses.end();)
	{
		if ((*it)->getGlobalBounds().intersects(m_player.getGlobalBounds())) // czy dotyka?
		{
			(*it)->DoAction(m_player); // zgarniêcie bonusa
			it = m_bonuses.erase(it); // usuniêcie bonusa
		}
		else
			++it;
	}
}

void Game::MoveZombies()
{
	for (auto it = m_zombies.begin(); it != m_zombies.end();)
	{
		if (it->IsTouching(m_player))
		{
			it = m_zombies.erase(it); // aktualizacja iteratora jest niezbêdna - po usuniêciu elementu elementy wektora s¹ przesuwane - iteratory siê zmieniaj¹

			if (!m_player.Touched())
			{
				m_loseText.setString("Game Over. Points: " + std::to_string(m_points));
				m_loseDelay.restart();
				m_state = GameState::Lost;
			}
		}
		else
		{
			auto zombiePos = it->getPosition();
			auto playerPos = m_player.getPosition();
			bool isRight = zombiePos.x < playerPos.x;
			bool isLeft = !isRight;
			bool isUp = zombiePos.y > playerPos.y;
			bool isDown = !isUp;

			auto xDist = std::abs(zombiePos.x - playerPos.x);
			auto yDist = std::abs(zombiePos.y - playerPos.y);

			if (m_difficultyLevel < 3)
				it->Move(xDist >= yDist && isLeft, xDist >= yDist && isRight, yDist > xDist && isUp, yDist > xDist && isDown); // tylko w jednym kierunku
			else
				it->Move(isLeft, isRight, isUp, isDown); // w dwóch kierunkach

			++it;
		}
	}
}

void Game::GenerateZombies()
{
	if (m_zombiesSpawnsDelay.getElapsedTime() > sf::milliseconds(m_zombiesSpawns))
	{
		m_zombiesSpawnsDelay.restart();

		int distance = 0;
		int xPos = 0;
		int yPos = 0;
		while (distance < m_player.getTexture()->getSize().x * m_spawnDistanceFactor) // nie losuj za blisko gracza
		{
			xPos = rand() % Utils::Window::width - 50;
			yPos = rand() % Utils::Window::heigth - 50;

			if (xPos < 0)
				xPos = 0;
			if (yPos < 0)
				yPos = 0;

			distance = sqrt(pow(m_player.getPosition().x - xPos, 2) + pow(m_player.getPosition().y - yPos, 2)); // aktualizacja dystansu
		}

		m_zombies.emplace_back(xPos, yPos);
	}
}

void Game::ResetAll()
{
	m_bonuses.clear();
	m_zombies.clear();
	m_player.Reset();
	m_shots.clear();

	m_shotPause = 500;

	if (m_difficultyLevel == 1) // zale¿noœci poziomu trudnoœci
		m_spawnDistanceFactor = 2.0; // wspó³czynnik informuj¹cy jak blisko mo¿na spawnowaæ zoombie
	else
		m_spawnDistanceFactor = 1.5;

	if (m_difficultyLevel < 3)
		m_zombiesSpawns = 2000;
	else
		m_zombiesSpawns = 1500;
	m_points = 0;
	m_zombiesSpawnsDelay.restart();
	m_lastTime = time(0);
	m_bonusDelay.restart();
}
