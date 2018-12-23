#include <Magick++.h>
#include <cstdio>
#include "SnakeGameState.h"

int main(int argc, char* argv[])
{
	Magick::InitializeMagick(*argv);

	SnakeGameState game;
	game.Play();
    return 0;
}