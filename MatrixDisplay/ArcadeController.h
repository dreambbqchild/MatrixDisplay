#pragma once
#include "ControllerBase.h"
#include <vector>
class ArcadeController : public ControllerBase
{
public:
	ArcadeController();

	virtual void Control();

	virtual ~ArcadeController();
};

