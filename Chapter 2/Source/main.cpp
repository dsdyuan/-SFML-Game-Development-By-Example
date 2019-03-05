#include "game.h"
#include "window.h"

int main(int argc, void** argv[])
{
	// program entry point
	Game game;

	while (!game.GetWindow()->IsDone())
	{
		// game loop
		game.HandleInput();
		game.Update();
		game.Render();
		// sf::sleep(sf::seconds(0.2));
		game.RestartClock(false);	// restarting our clock
	}

	return 0;
}