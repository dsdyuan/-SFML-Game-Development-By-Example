#include "game.h"

Game::Game()
	: m_window("Chapter 6", sf::Vector2u(800, 600)), m_stateManager(&m_context)
{
	m_clock.restart();
	srand(static_cast<int>(time(nullptr)));

	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game()
{
}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_elapsed);
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

Window * Game::GetWindow()
{
	return &m_window;
}

sf::Time Game::GetElapsed()
{
	return m_clock.getElapsedTime();
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}
