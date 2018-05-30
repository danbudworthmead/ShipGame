#pragma once

#include "component.h"
#include <vec2D.h>

template<typename T>
class BMPhysicsComponent : public BMComponent<T>
{
public:
	Vector2D Position, Velocity, Acceleration;

	virtual void Update(const GameState& state, T& obj) = 0;
};