#include "ship.h"
#include <gamestate.h>

Ship::Ship(ShipPhysicsComponent<Ship>* phys) : m_physics(phys)
{

}

Ship::~Ship()
{
	delete m_physics;
}

float Ship::GetRotation() const
{
	return m_physics->Rotation;
}

Vector2D& Ship::GetPosition()
{
	return m_physics->Position;
}