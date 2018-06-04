#include <SDL.h>
#include "player.h"
#include <gamestate.h>
#include "BMModel.h"
#include <mathhelper.h>
#include <iostream>

PlayerShip::PlayerShip(ShipPhysicsComponent<PlayerShip>* phys, BMModel *model) : Ship((ShipPhysicsComponent<Ship>*)phys), m_bmModel(model)
{
	m_bmModel->SetRotation(90);
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
	const KeyboardState& ks = state.GetKeys();

	float deltaSeconds = state.Delta() / 1000.0f;

	float rotationDiff = 0.f;

	if (ks.IsKeyDown(SDL_SCANCODE_A))
	{
		rotationDiff = -MAX_PLAYER_ROTATION_SPEED * deltaSeconds;
	}
	else if (ks.IsKeyDown(SDL_SCANCODE_D))
	{
		rotationDiff = MAX_PLAYER_ROTATION_SPEED * deltaSeconds;
	}

	if (ks.IsKeyDown(SDL_SCANCODE_W))

	{
		Vector2D direction = Vector2D::FromRotation(Rotation).Normalized();
		Acceleration += direction * PLAYER_ACCELERATION * deltaSeconds;
	}

	Acceleration.X = Clamp<float>(Acceleration.X, -MAX_PLAYER_ACCELERATION, MAX_PLAYER_ACCELERATION);
	Acceleration.Y = Clamp<float>(Acceleration.Y, -MAX_PLAYER_ACCELERATION, MAX_PLAYER_ACCELERATION);
	Velocity += Acceleration * deltaSeconds;

	Velocity *= FRICTION;

	Velocity.X = Clamp<float>(Velocity.X, -MAX_PLAYER_VELOCITY, MAX_PLAYER_VELOCITY);
	Velocity.Y = Clamp<float>(Velocity.Y, -MAX_PLAYER_VELOCITY, MAX_PLAYER_VELOCITY);
	Position += Velocity * deltaSeconds;

	// update ship

	if (rotationDiff != 0.0f)
	{
		ship.m_bmModel->SetRotation(ship.m_bmModel->GetRotation() + rotationDiff);
		Rotation += rotationDiff;
		Velocity.Rotate(rotationDiff);
		Acceleration.Rotate(rotationDiff);
	}

	ship.SetPosition(Position.X, Position.Y);
}