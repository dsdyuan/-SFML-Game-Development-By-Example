#include "game.h"

Game::Game()
	: m_window("Chapter 4", sf::Vector2u(800, 600))
{
	m_clock.restart();
	srand(static_cast<int>(time(nullptr)));

	m_booTexture.loadFromFile("Boo.png");
	m_boo.setTexture(m_booTexture);
	m_boo.setOrigin(m_booTexture.getSize().x / 2, m_booTexture.getSize().y / 2);
	m_boo.setPosition(m_window.GetWindowSize().x / 2, m_window.GetWindowSize().y / 2);

	m_backgroundTexture.loadFromFile("Background.png");
	m_background.setTexture(m_backgroundTexture);
	m_background.setPosition(0, 0);

	m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);
}

Game::~Game()
{
}

void Game::Update()
{
	m_window.Update();
}

void Game::Render()
{
	m_window.BeginDraw();

	m_window.Draw(m_background);
	m_window.Draw(m_boo);

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
	m_clock.restart();
}

void Game::MoveSprite(EventDetails* l_details)
{
	sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
	m_boo.setPosition(mousepos.x, mousepos.y);
	std::cout << "Moved sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
}
