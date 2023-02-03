#include <iostream>
#include "Game.h"


int main()
{
	// Init Game
	Game game;

	// Game loop
	while (game.running())
	{
		
		// Updating
		game.update();
		

		// draw the game
		game.render();
	}


	// End of app
	return 0;
}