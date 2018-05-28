#pragma once
#include "gamestate.h"

class BMObject
{
public:
	BMObject();
	~BMObject();

	virtual void Step(const GameState& state) = 0;
	virtual void Render(const GameState& state) = 0;
};