#pragma once

#include "baseState.h"
#include "eventManager.h"

class StateGame : public BaseState
{
public:
	StateGame(StateManager* l_stateManager);
	~StateGame();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time & l_time);
	void Draw();

	void MainMenu(EventDetails* l_details);
	void Pause(EventDetails* l_details);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_increment;
};