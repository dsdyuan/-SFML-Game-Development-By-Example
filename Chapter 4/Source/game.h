#pragma once

#include <cstdlib>
#include <ctime>
#include "window.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	
	Window * GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

	void MoveSprite(EventDetails* l_details);

private:
	Window m_window;

	sf::Clock m_clock;

	sf::Texture m_booTexture;
	sf::Sprite m_boo;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;
};