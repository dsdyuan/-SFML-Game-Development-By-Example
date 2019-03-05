#include "snake.h"

Snake::Snake(int l_blockSize, Textbox * l_textbox)
{
	m_textbox = l_textbox;
	m_size = l_blockSize;
	m_bodyRect.setSize(sf::Vector2f(static_cast<float>(m_size - 1), static_cast<float>(m_size - 1)));
	Reset();
}

Snake::~Snake()
{
}

void Snake::SetDirection(Direction l_dir)
{
	m_dir = l_dir;
}

Direction Snake::GetDirection()
{
	return m_dir;
}

Direction Snake::GetPhysicalDirection()
{
	if (m_snakeBody.size() <= 1)
		return Direction::None;

	SnakeSegment & head = m_snakeBody[0];
	SnakeSegment & neck = m_snakeBody[1];

	if (head.position.x == neck.position.x)
		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	else if (head.position.y == neck.position.y)
		return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);

	return Direction::None;
}

int Snake::GetSpeed()
{
	return m_speed;
}

sf::Vector2i Snake::GetPosition()
{
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::GetLives()
{
	return m_lives;
}

int Snake::GetScore()
{
	return m_score;
}

int Snake::GetLength()
{
	return m_snakeBody.size();
}

void Snake::IncreaseScore()
{
	m_score += 10;
	m_textbox->Add("You ate an apple. Your score: " + std::to_string(m_score));
}

bool Snake::HasLost()
{
	return m_lost;
}

void Snake::Lose()
{
	m_lost = true;
}

void Snake::ToggleLost()
{
	m_lost = !m_lost;
}

void Snake::Extend()
{
	if (m_snakeBody.empty())
		return;

	SnakeSegment & tail_head = m_snakeBody[m_snakeBody.size() - 1];

	if (m_snakeBody.size() > 1)
	{
		SnakeSegment & tail_bone = m_snakeBody[m_snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			}
			else
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			else
			{
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else
	{
		switch (m_dir)
		{
		case Direction::Up:
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			break;
		case Direction::Down:
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			break;
		case Direction::Left:
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			break;
		case Direction::Right:
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			break;
		default:
			break;
		}
	}
}

void Snake::Reset()
{
	m_snakeBody.clear();

	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None);	// start off still

	m_textbox->Clear();
	m_textbox->Add("You lost. Your previous score: " + std::to_string(m_score));
	m_textbox->Add("New game started!");

	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;

	
}

void Snake::Move()
{
	for (int i = m_snakeBody.size() - 1; i > 0; --i)
		m_snakeBody[i].position = m_snakeBody[i - 1].position;

	switch (m_dir)
	{
	case Direction::Up:
		--m_snakeBody[0].position.y;
		break;
	case Direction::Down:
		++m_snakeBody[0].position.y;
		break;
	case Direction::Left:
		--m_snakeBody[0].position.x;
		break;
	case Direction::Right:
		++m_snakeBody[0].position.x;
		break;
	default:
		break;
	}
}

void Snake::Tick()
{
	if (m_snakeBody.empty())
		return;

	if (m_dir == Direction::None)
		return;

	Move();
	CheckCollision();
}

void Snake::Cut(int l_segments)
{
	for (int i = 0; i < l_segments; ++i)
		m_snakeBody.pop_back();

	--m_lives;

	m_textbox->Add("You ate part of yourself. Remaining lives: " + std::to_string(m_lives));
	
	if (!m_lives)
	{
		Lose();
		return;
	}
}

void Snake::Render(sf::RenderWindow & l_window)
{
	if (m_snakeBody.empty())
		return;

	auto head = m_snakeBody.begin();

	m_bodyRect.setFillColor(sf::Color(183, 209, 103, 255));
	m_bodyRect.setPosition(static_cast<float>(head->position.x * m_size), static_cast<float>(head->position.y * m_size));
	l_window.draw(m_bodyRect);

	m_bodyRect.setFillColor(sf::Color(58, 170, 53, 255));
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		m_bodyRect.setPosition(static_cast<float>(itr->position.x * m_size), static_cast<float>(itr->position.y * m_size));
		l_window.draw(m_bodyRect);
	}
}

// snake collides with itself
void Snake::CheckCollision()
{
	if (m_snakeBody.size() < 5)	// no need to check for collisions if there are four or less segments
		return;

	SnakeSegment & head = m_snakeBody.front();

	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			int segments = m_snakeBody.end() - itr;
			Cut(segments);
			break;
		}
	}
}
