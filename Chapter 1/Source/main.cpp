#include "SFML/Graphics.hpp"

int main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");

	// Creating our shape
	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(320, 240);
	rectangle.setOrigin(64.0, 64.0f); 
	// 'rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);' if the exact size is not known

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();	// Close window button clicked
			}
		}

		window.clear(sf::Color::Black);

		window.draw(rectangle);	// Drawing our shape

		window.display();
	}

	return 0;
}