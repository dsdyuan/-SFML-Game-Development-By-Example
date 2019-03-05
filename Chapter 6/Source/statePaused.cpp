#include "statePaused.h"
#include "stateManager.h"

StatePaused::StatePaused(StateManager * l_stateManager)
	: BaseState(l_stateManager)
{
}

StatePaused::~StatePaused()
{
}

void StatePaused::OnCreate()
{
	std::cout << "'StatePaused' loaded." << std::endl;

	SetTransparent(true);	// set the transparency flag
	
	m_font.loadFromFile("Lora.ttf");
	
	m_text.setFont(m_font);
	m_text.setString(sf::String("Paused"));
	m_text.setCharacterSize(16);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();

	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	
	m_rect.setSize(static_cast<sf::Vector2f>(windowSize));
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Paused, "Key_P", &StatePaused::Unpause, this);
}

void StatePaused::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Paused, "Key_P");
}

void StatePaused::Activate()
{
}

void StatePaused::Deactivate()
{
}

void StatePaused::Update(const sf::Time & l_time)
{
}

void StatePaused::Draw()
{
	sf::RenderWindow* wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	wind->draw(m_rect);
	wind->draw(m_text);
}

void StatePaused::Unpause(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::Game);
}
