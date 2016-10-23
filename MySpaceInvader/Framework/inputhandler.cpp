// COMP710 GP 2D Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	//assert(m_pGameController);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// W02.1: Receive Input Events below...
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			// W02.3: Tell the game to fire a player bullet...  A button
			if (e.jbutton.button == 10)
			{			
				game.FireSpaceShipBullet();
				game.PlayBulletSound();
			}

			// W02.1: Tell the game to move the space ship left...
			//down 1 up 0 left 2 right 3
			if (e.jbutton.button == 2)
			{
				game.MoveSpaceShipLeft();
				
			}
			// W02.1: Tell the game to move the space ship right...
			if (e.jbutton.button == 3)
			{
				game.MoveSpaceShipRight();
			}
		}
		else if (e.type == SDL_JOYBUTTONUP)
		{
			// W02.1: Tell the game to stop
			//down 1 up 0 left 2 right 3
			if (e.jbutton.button == 2 || e.jbutton.button == 3)
			{
				game.StopSpaceShip();

			}
		}

		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_LEFT) //keyboard left 
			{
				game.MoveSpaceShipLeft();
			}
			if (e.key.keysym.sym == SDLK_RIGHT) //keyboard right 
			{
				game.MoveSpaceShipRight();
			}
			if (e.key.keysym.sym == SDLK_SPACE) //keyboard space
			{
				game.FireSpaceShipBullet();
				game.PlayBulletSound();
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) //keyboard left/right 
			{
				game.StopSpaceShip();
			}
		}
	}
}
