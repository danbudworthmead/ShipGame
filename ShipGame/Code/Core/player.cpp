#include <SDL.h>
#include "player.h"
#include "gamestate.h"
#include "BMModel.h"
#include "mathhelper.h"

PlayerShip::PlayerShip(ShipPhysicsComponent<PlayerShip>* phys, BMModel *model) : Ship((ShipPhysicsComponent<Ship>*)phys), m_bmModel(model)
{

}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::SetPosition(const float x, const float y)
{
	m_physics->Position.X = x;
	m_physics->Position.Y = y;

	m_bmModel->SetPosition((int)m_physics->Position.X, (int)m_physics->Position.Y);
}

void PlayerShip::Update(const GameState& state)
{
	m_physics->Update(state, *this);
}

void PlayerPhysicsComponent::Update(const GameState& state, PlayerShip& ship)
{
	float deltaSeconds = state.Delta() / 1000.0f;

	Position += Velocity * deltaSeconds; // units per second
	Velocity += Acceleration * deltaSeconds; // units per second per second

	if (state.IsKeyDown(SDL_SCANCODE_A))
	{
		Rotation -= MAX_PLAYER_ROTATION_SPEED * deltaSeconds;
	}
	else if (state.IsKeyDown(SDL_SCANCODE_D))
	{
		Rotation += MAX_PLAYER_ROTATION_SPEED * deltaSeconds;
	}
	

	ship.m_bmModel->SetRotation(Rotation);
	ship.SetPosition(Position.X, Position.Y);
}