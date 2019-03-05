#pragma once

#include <cstdlib>
#include <ctime>
#include "eventManager.h"
#include "stateManager.h"
#include "sharedContext.h"

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

	sf::Clock m_clock;
	sf::Time m_elapsed;
	
	void RestartClock();
};