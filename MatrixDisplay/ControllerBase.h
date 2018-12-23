#pragma once
#include "Interfaces.h"
#include <vector>

class ControllerBase : public IController
{
private:
	std::vector<std::function<void(Movement movement)>> movementCallbacks;
	std::vector<std::function<void(Button button)>> buttonCallbacks;

protected:
	void FireMovementChanged(Movement newMovement);
	void FireButtonChanged(Button button);

public:
	void RegisterMovementChangedCallback(std::function<void(Movement movement)> callback) { movementCallbacks.push_back(callback); }
	void RegisterButtonsChangedCallback(std::function<void(Button button)> callback) { buttonCallbacks.push_back(callback); }
};