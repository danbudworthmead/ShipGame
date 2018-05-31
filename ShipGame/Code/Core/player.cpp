#include <SDL.h>
#include "player.h"
#include "gamestate.h"
#include "BMModel.h"
#include "mathhelper.h"

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

	float oldRotation = Rotation;

	if (ks.IsKeyDown(SDL_SCANCODE_A))
	{
		Rotation -= MAX_PLAYER_ROTATION_SPEED * deltaSeconds;
	}
	else if (ks.IsKeyDown(SDL_SCANCODE_D))
	{
		Rotation += MAX_PLAYER_ROTATION_SPEED * deltaSeconds;
	}

	Vector2D direction = Vector2D::FromRotation(Rotation).Normalized();

	if (ks.IsKeyDown(SDL_SCANCODE_W))
	{
		direction *= MAX_PLAYER_MOVE_SPEED;
		Position += direction * deltaSeconds;
	}

	float rotationDiff = Rotation - oldRotation;

	if (rotationDiff != 0.0f)
	{
		ship.m_bmModel->SetRotation(ship.m_bmModel->GetRotation() + rotationDiff);
	}

	ship.SetPosition(Position.X, Position.Y);
}