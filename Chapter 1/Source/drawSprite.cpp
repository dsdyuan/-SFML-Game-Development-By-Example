// slightly modified listing from page 13
#include "SFML/Graphics.hpp"
#include <iostream>

int main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Bouncing Boo");

	sf::Texture booTexture;

	// added error checking
	if (!booTexture.loadFromFile("Boo.png"))
	{
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	sf::Sprite boo(booTexture);

	sf::Vector2u size = booTexture.getSize();

	boo.setOrigin(size.x / 2.0f, size.y / 2.0f);

	sf::Vector2f increment(0.02f, 0.02f);	// modified values, original was 0.4f

	bool countAlphaUp;
	float alphaValue = 255.0f;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// playing around with 'setColor()' and alpha values
		if (boo.getColor().a >= 255)
		{
			countAlphaUp = false;
		}
		else if (boo.getColor().a <= 100)
		{
			countAlphaUp = true;
		}

		countAlphaUp ? alphaValue += 0.01f : alphaValue -= 0.01f;


		boo.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alphaValue)));

		if ((boo.getPosition().x + (size.x / 2) > window.getSize().x && increment.x > 0) ||
			(boo.getPosition().x - (size.x / 2) < 0 && increment.x < 0))
		{
			// reverse the direction on x axis
			increment.x *= -1;
		}

		if ((boo.getPosition().y + (size.y / 2) > window.getSize().y && increment.y > 0) ||
			(boo.getPosition().y - (size.y / 2) < 0 && increment.y < 0))
		{
			// reverse the direction on y axis
			increment.y *= -1;
		}

		boo.setPosition(boo.getPosition() + increment);

		window.clear(sf::Color(16, 16, 16, 255));	// dark gray

		window.draw(boo);

		window.display();
	}
}