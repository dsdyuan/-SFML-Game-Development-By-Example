#include "game.h"
#include <ctime>
#include <cstdlib>

int main(int argc, void** argv[])
{
	srand(static_cast<int>(time(nullptr)) % rand());

	Game game;

	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}