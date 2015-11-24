#include "Game.h"
#include "Vector2D.h"
#include <iostream>
#include <time.h>
using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000/FPS;
int main(int argc, char** argv)
{
	Uint32 frameStart, frameTime;
	srand(time(0));
	if (Game::Instance()->init("Battle city", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		760, 480))
	{
		cout << "game init success\n";
		while(Game::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}

	}
	else
	{
		cout << "game init failed\n";
		return 1;
	}
	cout << "game closing...\n";
	Game::Instance()->clean();
	return 0;
}