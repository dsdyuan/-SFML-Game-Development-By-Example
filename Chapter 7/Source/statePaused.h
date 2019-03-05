#pragma once

#include "baseState.h"
#include "eventManager.h"

class StatePaused : public BaseState
{
public:
	StatePaused(StateManager* l_stateManager);
	~StatePaused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time & l_time);
	void Draw();

	void Unpause(EventDetails* l_details);

private:
	sf::Font m_font;
	sf::Text m_text;

	sf::RectangleShape m_rect;
};