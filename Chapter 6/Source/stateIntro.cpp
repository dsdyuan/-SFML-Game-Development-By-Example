#include <iostream>
#include "stateIntro.h"
#include "stateManager.h"

StateIntro::StateIntro(StateManager * l_stateManager)
	: BaseState(l_stateManager)
{
}

StateIntro::~StateIntro()
{
}

void StateIntro::OnCreate()
{
	std::cout << "'StateIntro' loaded." << std::endl;

	m_timePassed = 0.0f;

	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
	
	m_introTexture.loadFromFile("Intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition(windowSize.x / 2.0f, 0);

	m_font.loadFromFile("Lora.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "Press SPACE to continue..." });
	m_text.setCharacterSize(14);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + 64);

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Intro, "Intro_Continue", &StateIntro::Continue, this);
}

void StateIntro::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void StateIntro::Activate()
{
}

void StateIntro::Deactivate()
{
}

void StateIntro::Update(const sf::Time & l_time)
{
	if (m_timePassed < 5.0f)
	{
		m_timePassed += l_time.asSeconds();
		m_introSprite.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + (48 * l_time.asSeconds()));
	}
}

void StateIntro::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_introSprite);
	
	if (m_timePassed >= 5.0f)
	{
		window->draw(m_text);
	}
}

void StateIntro::Continue(EventDetails * l_details)
{
	if (m_timePassed >= 5.0f)
	{
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_stateMgr->Remove(StateType::Intro);
	}
}
