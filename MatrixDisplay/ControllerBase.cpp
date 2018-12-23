#include "ControllerBase.h"
#include <algorithm>

using namespace std;

void ControllerBase::FireMovementChanged(Movement newMovement)
{
	for_each(movementCallbacks.begin(), movementCallbacks.end(), [&](function<void(Movement movement)> callback)
	{
		callback(newMovement);
	});
}

void ControllerBase::FireButtonChanged(Button button)
{
	for_each(buttonCallbacks.begin(), buttonCallbacks.end(), [&](function<void(Button button)> callback)
	{
		callback(button);
	});
}