#include "game.h"

Game::Game()
	: m_window("Chapter 2", sf::Vector2u(800, 600))
{
	m_booTexture.loadFromFile("Boo.png");
	m_boo.setTexture(m_booTexture);
	m_increment = sf::Vector2f(400.0f, 400.0f);
}

Game::~Game()
{
	// nothing to clean up yet
}

void Game::HandleInput()
{
}

void Game::Update()
{
	m_window.Update();	// update window events
	MoveBoo();
}

void Game::Render()
{
	m_window.BeginDraw();	// clear
	m_window.Draw(m_boo);
	m_window.EndDraw();		// display
}

Window * Game::GetWindow()
{
	return &m_window;
}

sf::Time Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock(bool fixed)
{
	if (fixed)
		m_elapsed += m_clock.restart();
	else	
		m_elapsed = m_clock.restart();
}

void Game::MoveBoo()
{
	sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_booTexture.getSize();

	if ((m_boo.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
		(m_boo.getPosition().x < 0 && m_increment.x < 0))
	{
		m_increment.x *= -1.0f;
	}

	if ((m_boo.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_boo.getPosition().y < 0 && m_increment.y < 0))
	{
		m_increment.y *= -1.0f;
	}

	float fElapsed = m_elapsed.asSeconds();

	m_boo.setPosition(
		m_boo.getPosition().x + (m_increment.x * fElapsed),
		m_boo.getPosition().y + (m_increment.y * fElapsed)
	);
}
