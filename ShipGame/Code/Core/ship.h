#pragma once
#include <physicscomponent.h>
#include <bmobject.h>

class GameState;

template<typename T>
class ShipPhysicsComponent : public BMPhysicsComponent<T>
{
public:
	float Rotation;
};

class Ship : public BMObject
{
public:
	Ship(ShipPhysicsComponent<Ship>* phys);
	virtual ~Ship();

	float GetRotation() const;
	Vector2D& GetPosition();

	virtual void Update(const GameState& state) = 0;

protected:
	ShipPhysicsComponent<Ship>* m_physics;
};