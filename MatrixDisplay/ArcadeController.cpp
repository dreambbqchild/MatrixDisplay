#include "ArcadeController.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <errno.h>

using namespace std;

ArcadeController::ArcadeController()
{
}

void ArcadeController::Control()
{
	struct termios tio = { 0 };
	tio.c_cflag = CS8 | CREAD | CLOCAL;
	tio.c_cc[VMIN] = 1;

	char state[32] = { 0 };
	auto stateIndex = 0;
	auto lastReportedButtonState = Button::None;
	auto lastReportedMovement = Movement::None;
	auto controller = open("/dev/ttyACM0", O_RDONLY);
	auto isRunning = controller != -1;
	if (!isRunning)
	{
		cout << "Unable to connect to controller: " << errno << endl;
		return;
	}

	cfsetispeed(&tio, B9600);
	tcsetattr(controller, TCSANOW, &tio);
	cout << "Controller started" << endl;
	while (isRunning)
	{
		Button currentButtons = Button::None;
		Movement currentMovement = Movement::None;
		
		memset(state, 0x0, sizeof(state));
		stateIndex = 0;
		do
		{
			read(controller, &state[stateIndex], 1);
		} while (state[stateIndex++] != '\n');

		for (auto i = 0; i < stateIndex; i++)
		{
			auto c = state[i];
			switch (c)
			{
			case 'B': currentButtons = currentButtons | Button::B;  break;
			case 'G': currentButtons = currentButtons | Button::A;  break;
			case 'W': 
				{
					isRunning = false;
					cout << "Start Pressed, Exiting" << endl;
					break;
				}
			case 'U': currentMovement = currentMovement | Movement::Up; break;
			case 'D': currentMovement = currentMovement | Movement::Down; break;
			case 'L': currentMovement = currentMovement | Movement::Left; break;
			case 'R': currentMovement = currentMovement | Movement::Right; break;
			}
		}

		if (currentMovement != lastReportedMovement)
		{
			cout << ((currentMovement & Movement::Up) != Movement::None ? "Up " : "")
				<< ((currentMovement & Movement::Down) != Movement::None ? "Down " : "")
				<< ((currentMovement & Movement::Left) != Movement::None ? "Left " : "")
				<< ((currentMovement & Movement::Right) != Movement::None ? "Right " : "")
				<< (currentMovement == Movement::None ? "None" : "")
				<< endl;

			FireMovementChanged(currentMovement);
			lastReportedMovement = currentMovement;
		}

		if (currentButtons != lastReportedButtonState)
		{
			cout << ((currentButtons & Button::B) != Button::None ? "B " : "")
				<< ((currentButtons & Button::A) != Button::None ? "A " : "")
				<< (currentButtons == Button::None ? "None " : "")
				<< endl;

			FireButtonChanged(currentButtons);
			lastReportedButtonState = currentButtons;
		}
	}
	close(controller);
}


ArcadeController::~ArcadeController()
{
}
