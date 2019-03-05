#pragma once

#include "baseState.h"
#include "eventManager.h"

class StateIntro : public BaseState
{
public:
	StateIntro(StateManager* l_stateManager);
	~StateIntro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time & l_time);
	void Draw();

	void Continue(EventDetails* l_details);

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;

	sf::Text m_text;
	sf::Font m_font;

	float m_timePassed;
};