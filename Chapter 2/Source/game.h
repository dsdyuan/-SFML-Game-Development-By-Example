#pragma once

#include "window.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	
	Window * GetWindow();

	sf::Time GetElapsed();
	void RestartClock(bool fixed = false);

private:
	void MoveBoo();
	Window m_window;
	sf::Texture m_booTexture;
	sf::Sprite m_boo;
	sf::Vector2f m_increment;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};