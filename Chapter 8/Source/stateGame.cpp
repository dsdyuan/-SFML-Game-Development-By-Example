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

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Game, "Key_Escape", &StateGame::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P", &StateGame::Pause, this);

	sf::Vector2u size = m_stateMgr->GetContext()->m_wind->GetWindowSize();

	m_view.setSize(static_cast<float>(size.x), static_cast<float>(size.y));
	m_view.setCenter(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));
	m_view.zoom(0.6f);

	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->setView(m_view);

	m_gameMap = new Map(m_stateMgr->GetContext(), this);
	m_gameMap->LoadMap("map1.map");
}

void StateGame::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Paused, "Key_P");

	delete m_gameMap;
	m_gameMap = nullptr;
}

void StateGame::Activate()
{
}

void StateGame::Deactivate()
{
}

void StateGame::Update(const sf::Time & l_time)
{
	SharedContext* context = m_stateMgr->GetContext();
	EntityBase* player = context->m_entityManager->Find("Player");

	if (!player)
	{
		std::cout << "Respawning player..." << std::endl;

		context->m_entityManager->Add(EntityType::Player, "Player");

		player = context->m_entityManager->Find("Player");
		player->SetPosition(m_gameMap->GetPlayerStart());
	}
	else
	{
		m_view.setCenter(player->GetPosition());
		context->m_wind->GetRenderWindow()->setView(m_view);
	}

	sf::FloatRect viewSpace = context->m_wind->GetViewSpace();

	if (viewSpace.left <= 0)
	{
		m_view.setCenter(viewSpace.width / 2, m_view.getCenter().y);

		context->m_wind->GetRenderWindow()->setView(m_view);
	}
	else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x + 1) * Sheet::TileSize)
	{
		m_view.setCenter(((m_gameMap->GetMapSize().x + 1) * Sheet::TileSize) - (viewSpace.width / 2), m_view.getCenter().y);

		context->m_wind->GetRenderWindow()->setView(m_view);
	}

	m_gameMap->Update(l_time.asSeconds());
	m_stateMgr->GetContext()->m_entityManager->Update(l_time.asSeconds());
}

void StateGame::Draw()
{
	m_gameMap->Draw();
	m_stateMgr->GetContext()->m_entityManager->Draw();
}

void StateGame::MainMenu(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void StateGame::Pause(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::Paused);
}
