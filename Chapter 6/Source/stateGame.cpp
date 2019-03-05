#include <iostream>
#include "stateGame.h"
#include "stateManager.h"

StateGame::StateGame(StateManager * l_stateManager)
	: BaseState(l_stateManager)
{
}

StateGame::~StateGame()
{
}

void StateGame::OnCreate()
{
	std::cout << "'StateGame' loaded." << std::endl;

	m_texture.loadFromFile("Boo.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0.0f, 0.0f);
	m_increment = sf::Vector2f(400.0f, 400.0f);

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Game, "Key_Escape", &StateGame::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P", &StateGame::Pause, this);
}

void StateGame::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Paused, "Key_P");
}

void StateGame::Activate()
{
}

void StateGame::Deactivate()
{
}

void StateGame::Update(const sf::Time & l_time)
{
	sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetWindowSize();
	sf::Vector2u l_textSize = m_texture.getSize();

	if ((m_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
		(m_sprite.getPosition().x < 0 && m_increment.x < 0))
		m_increment.x *= -1;

	if ((m_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_sprite.getPosition().y < 0 && m_increment.y < 0))
		m_increment.y *= -1;

	m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()), m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));
}

void StateGame::Draw()
{
	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_sprite);
}

void StateGame::MainMenu(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void StateGame::Pause(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::Paused);
}
