#include "ArcadeController.h"
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

using namespace std;

ArcadeController::ArcadeController()
{
}

void ArcadeController::Control()
{
	struct termios tio = { 0 };
	tio.c_cflag = CS8 | CREAD | CLOCAL;
	tio.c_cc[VMIN] = 1;

	auto buttonMask = Button::None;
	auto controller = open("/dev/ttyACM0", O_RDONLY);
	auto isRunning = controller != -1;
	if (!isRunning)
	{
		cout << "Unable to connect to controller" << endl;
		return;
	}

	cfsetispeed(&tio, B9600);
	tcsetattr(controller, TCSANOW, &tio);
	cout << "Controller started" << endl;
	while (isRunning)
	{
		char c = '\0';
		read(controller, &c, 1);
		if (c == 'B' || c == 'G' || c == 'W')
		{
			char stateChar = '\0';
			read(controller, &stateChar, 1);
			
			if (c == 'B')
				buttonMask = stateChar == '-' ? (buttonMask & ~(Button::B)) : (buttonMask | Button::B);

			if (c == 'G')
				buttonMask = stateChar == '-' ? (buttonMask & ~(Button::A)) : (buttonMask | Button::A);

			if (c == 'W' && stateChar == '_')
			{
				isRunning = false;
				cout << "Start Pressed, Exiting" << endl;
			}
			else
				FireButtonChanged(buttonMask);
		}
		else
		{
			char joystickState[8] = { 0 };
			auto movement = Movement::None;

			//VMIN = 1, rather than fiddle just read byte by byte.
			joystickState[0] = c;
			for(auto i = 0; i < 7; i++)
				read(controller, &joystickState[1 + i], 1);
	
			for(auto i = 1; i < 8; i += 2)
			{
				auto stateChar = joystickState[i];
				switch (joystickState[i - 1])
				{
				case 'u': movement = stateChar == '-' ? (movement & ~(Movement::Up)) : (movement | Movement::Up); break;
				case 'd': movement = stateChar == '-' ? (movement & ~(Movement::Down)) : (movement | Movement::Down); break;
				case 'l': movement = stateChar == '-' ? (movement & ~(Movement::Left)) : (movement | Movement::Left); break;
				case 'r': movement = stateChar == '-' ? (movement & ~(Movement::Right)) : (movement | Movement::Right); break;
				}
			}

			FireMovementChanged(movement);
		}
	}
	close(controller);
}


ArcadeController::~ArcadeController()
{
}
