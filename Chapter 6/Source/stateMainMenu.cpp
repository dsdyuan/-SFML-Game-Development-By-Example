#include <iostream>
#include <string>
#include "stateMainMenu.h"
#include "stateManager.h"

StateMainMenu::StateMainMenu(StateManager * l_stateManager)
	: BaseState(l_stateManager)
{
}

StateMainMenu::~StateMainMenu()
{
}

void StateMainMenu::OnCreate()
{
	std::cout << "'StateMainMenu' loaded." << std::endl;

	m_font.loadFromFile("Lora.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU"));
	m_text.setCharacterSize(16);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(400, 100);

	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(400.0f, 200.0f);
	m_buttonPadding = 4;	// pixel

	std::string str[3] = { "PLAY", "CREDITS", "EXIT" };

	for (int i = 0; i < 3; ++i)
	{
		sf::Vector2f buttonPosition(m_buttonPos.x, m_buttonPos.y + (i * (m_buttonSize.y + m_buttonPadding)));
		
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color(234, 91, 12, 255));
		m_rects[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(14);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::MainMenu, "Mouse_Left", &StateMainMenu::MouseClick, this);
}

void StateMainMenu::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void StateMainMenu::Activate()
{
	if (m_stateMgr->HasState(StateType::Game) && m_labels[0].getString() == "PLAY")
	{
		m_labels[0].setString(sf::String("RESUME"));
		sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	}
}

void StateMainMenu::Deactivate()
{
}

void StateMainMenu::Update(const sf::Time & l_time)
{
}

void StateMainMenu::Draw()
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	
	window->draw(m_text);

	for (int i = 0; i < 3; ++i)
	{
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void StateMainMenu::MouseClick(EventDetails * l_details)
{
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;

	for (int i = 0; i < 3; ++i)
	{
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			switch (i)
			{
			case 0:
				m_stateMgr->SwitchTo(StateType::Game);
				break;
			case 1:
				// credits state
				break;
			case 2:
				m_stateMgr->GetContext()->m_wind->Close();
				break;
			default:
				std::cout << "StateMainMenu::Mouseclick(): Invalid value." << std::endl;
				break;
			}
		}
	}
}
