#include "window.h"

Window::Window()
{
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string & l_title, const sf::Vector2u & l_size)
{
	Setup(l_title, l_size);
}

Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color(16, 16, 16, 255));
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}

		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullscreen()
{
	return m_isFullscreen;
}

bool Window::IsFocused()
{
	return m_isFocused;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

EventManager * Window::GetEventManager()
{
	return &m_eventManager;
}

void Window::ToggleFullScreen(EventDetails* l_details)
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}

void Window::Setup(const std::string & l_title, const sf::Vector2u & l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	m_window.setFramerateLimit(60);
	m_isFocused = true;	// default value for focused flag

	m_eventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullScreen, this);
	m_eventManager.AddCallback("Window_close1", &Window::Close, this);
	m_eventManager.AddCallback("Window_close2", &Window::Close, this);

	Create();
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}
