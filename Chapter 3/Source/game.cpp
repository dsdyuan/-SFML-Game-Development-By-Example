#include "game.h"

Game::Game()
	: m_window("Snake", sf::Vector2u(800, 600)), m_snake(Snake(m_world.GetBlockSize(), &m_textbox)), m_world(World(sf::Vector2u(800, 600), &m_textbox))
{
	m_textbox.Setup(5, 12, 350, sf::Vector2f(225, 0));
	m_textbox.Add("New game started!");
}

Game::~Game()
{
}

void Game::HandleInput()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && m_snake.GetPhysicalDirection() != Direction::Down)
	{
		m_snake.SetDirection(Direction::Up);
	} 
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && m_snake.GetPhysicalDirection() != Direction::Up)
	{
		m_snake.SetDirection(Direction::Down);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && m_snake.GetPhysicalDirection() != Direction::Right)
	{
		m_snake.SetDirection(Direction::Left);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && m_snake.GetPhysicalDirection() != Direction::Left)
	{
		m_snake.SetDirection(Direction::Right);
	}
}

void Game::Update()
{
	m_window.Update();

	float timestep = 1.0f / m_snake.GetSpeed();

	if (m_elapsed >= timestep)
	{
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;

		if (m_snake.HasLost())
			m_snake.Reset();
	}
}

void Game::Render()
{
	m_window.BeginDraw();

	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_textbox.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();
}

Window * Game::GetWindow()
{
	return &m_window;
}

float Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock() { 
	m_elapsed += m_clock.restart().asSeconds(); 
}
