#pragma once

#include <cstdlib>
#include <ctime>
#include "window.h"
#include "eventManager.h"
#include "stateManager.h"
#include "textureManager.h"
#include "entityManager.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void LateUpdate();
	void Render();
	
	Window * GetWindow();

	sf::Time GetElapsed();
	
private:
	Window m_window;
	StateManager m_stateManager;
	SharedContext m_context;
	EntityManager m_entityManager;
	TextureManager m_textureManager;

	sf::Clock m_clock;
	sf::Time m_elapsed;
	
	void RestartClock();
};