#pragma once
#include "ControllerBase.h"
#include <vector>

class KeyboardController : public ControllerBase
{
public:
	KeyboardController();

	virtual void Control();

	virtual ~KeyboardController();
};

