#pragma once

#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "eventManager.h"

#include <string>

class Window
{
public:
	Window();
	Window(const std::string & l_title, const sf::Vector2u & l_size);
	~Window();

	void BeginDraw();	// clear the window
	void EndDraw();		// display the changes

	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool IsFocused();

	EventManager* GetEventManager();
	void ToggleFullScreen(EventDetails* l_details);
	void Close(EventDetails* l_details = nullptr) { m_isDone = true; }

	sf::RenderWindow * GetRenderWindow() { return &m_window; }

	sf::Vector2u GetWindowSize();

	void Draw(sf::Drawable & l_drawable);

	sf::FloatRect GetViewSpace();

private:
	void Setup(const std::string & l_title, const sf::Vector2u & l_size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;

	EventManager m_eventManager;
	bool m_isFocused;
};