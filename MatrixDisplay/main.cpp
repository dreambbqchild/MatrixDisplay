#include <Magick++.h>
#include <cstdio>
//#include "SnakeGameState.h"
#include "SpaceInvadersGameState.h"

int main(int argc, char* argv[])
{
	Magick::InitializeMagick(*argv);

	//SnakeGameState game;
	SpaceInvadersGameState game;
	game.Play();
    return 0;
}