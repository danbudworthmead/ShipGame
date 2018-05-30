#pragma once

#include "ship.h"

class BMModel;
class PlayerPhysicsComponent;

#define MAX_PLAYER_ROTATION_SPEED 30.0f // 20 degrees per second
#define MAX_PLAYER_MOVE_SPEED 70.0f // 30 units per second

class PlayerShip : public Ship
{
public:
	PlayerShip(ShipPhysicsComponent<PlayerShip> *phys, BMModel* model);
	~PlayerShip();

	void SetPosition(const float x, const float y);

	void Update(const GameState& state);

	friend PlayerPhysicsComponent;

private:
	BMModel *m_bmModel;
};

class PlayerPhysicsComponent : public ShipPhysicsComponent<PlayerShip>
{
	void Update(const GameState& state, PlayerShip& obj);
};