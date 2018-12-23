#include "KeyboardController.h"
#include <signal.h>
#include <algorithm>
//#include <ncurses.h>
#include <termios.h>

volatile bool isRunning = true;
static void InterruptHandler(int signo)
{
	isRunning = false;
}

KeyboardController::KeyboardController()
{
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	struct termios term;
	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(fileno(stdin), TCSANOW, &term);
}

void KeyboardController::Control()
{
	while (isRunning)
	{
		auto c = getc(stdin);
		switch (c)
		{
		case 'W':
		case 'w':
			FireMovementChanged(Movement::Up);
			break;
		case 'S':
		case 's':
			FireMovementChanged(Movement::Down);
			break;
		case 'A':
		case 'a':
			FireMovementChanged(Movement::Left);
			break;
		case 'D':
		case 'd':
			FireMovementChanged(Movement::Right);
			break;
		case ';':
			FireButtonChanged(Button::A);
			break;
		case 'Q':
		case 'q':
			isRunning = false;
			return;
		}
	}
}

KeyboardController::~KeyboardController()
{
	struct termios term;
	tcgetattr(fileno(stdin), &term);
	term.c_lflag |= ~ICANON;
	term.c_lflag |= ~ECHO;
	tcsetattr(fileno(stdin), TCSANOW, &term);
}
