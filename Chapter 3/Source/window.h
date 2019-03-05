#pragma once

#include "SFML/Graphics.hpp"
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

	sf::Vector2u GetWindowSize();

	void ToggleFullScreen();

	void Draw(sf::Drawable & l_drawable);

	sf::RenderWindow * GetRenderWindow() { return & m_window; }

private:
	void Setup(const std::string & l_title, const sf::Vector2u & l_size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};