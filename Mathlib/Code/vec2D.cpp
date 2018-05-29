#include <algorithm>
#include <cmath>
#include "vec2D.h"
#include "mathhelper.h"

Vector2D Vector2D::Zero = Vector2D(0, 0);
Vector2D Vector2D::Unit = Vector2D(1, 1);
Vector2D Vector2D::UnitX = Vector2D(1, 0);
Vector2D Vector2D::UnitY = Vector2D(0, 1);

Vector2D::Vector2D() : X(0), Y(0)
{

}

Vector2D::Vector2D(float initX, float initY) : X(initX), Y(initY)
{

}

Vector2D::~Vector2D()
{

}

Vector2D Vector2D::Add(const Vector2D& one, const Vector2D& two)
{
	float newX = one.X + two.X;
	float newY = one.Y + two.Y;

	return Vector2D(newX, newY);
}

Vector2D Vector2D::Multiply(const Vector2D& one, const Vector2D& two)
{
	float newX = one.X * two.X;
	float newY = one.Y * two.Y;

	return Vector2D(newX, newY);
}

Vector2D Vector2D::Subtract(const Vector2D& one, const Vector2D& two)
{
	float newX = one.X - two.X;
	float newY = one.Y - two.Y;

	return Vector2D(newX, newY);
}

Vector2D Vector2D::Divide(const Vector2D& one, const Vector2D& two)
{
	float newX = one.X / two.X;
	float newY = one.Y / two.Y;

	return Vector2D(newX, newY);
}

Vector2D Vector2D::Clamp(Vector2D& value, const Vector2D& min, const Vector2D& max) 
{
	float x, y;

	x = ::Clamp(value.X, min.X, max.X);
	y = ::Clamp(value.Y, min.Y, max.Y);

	return Vector2D(x, y);
}

float Vector2D::Distance(const Vector2D& first, const Vector2D& second)
{
	float vX = first.X - second.X;
	float vY = first.Y - second.Y;

	return std::sqrtf((vX * vX) + (vY * vY));
}

float Vector2D::DistanceSquared(const Vector2D& first, const Vector2D& second)
{
	float vX = first.X - second.X;
	float vY = first.Y - second.Y;

	return (vX * vX) + (vY * vY);
}

float Vector2D::Dot(const Vector2D& first, const Vector2D& second)
{
	return (first.X * second.X) + (first.Y * second.Y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	X += other.X;
	Y += other.Y;;

	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D::Add(*this, other);
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	X -= other.X;
	Y -= other.Y;

	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	float newX = X - other.X;
	float newY = Y - other.Y;

	return Vector2D(newX, newY);
}

Vector2D& Vector2D::operator*=(const Vector2D& other)
{
	X *= other.X;
	Y *= other.Y;

	return *this;
}

Vector2D Vector2D::operator*(const Vector2D& other)
{
	return Vector2D::Multiply(*this, other);
}

Vector2D& Vector2D::operator/=(const Vector2D& other)
{
	X /= other.X;
	Y /= other.Y;

	return *this;
}

Vector2D Vector2D::operator/(const Vector2D& other)
{
	return Vector2D::Divide(*this, other);
}

Vector2D& Vector2D::operator*=(const float other)
{
	X *= other;
	Y *= other;

	return *this;
}

Vector2D Vector2D::operator*(const float other)
{
	float newX = X * other;
	float newY = Y * other;

	return Vector2D(newX, newY);
}

Vector2D& Vector2D::operator/=(const float other)
{
	X /= other;
	Y /= other;

	return *this;
}

Vector2D Vector2D::operator/(const float other)
{
	float newX = X / other;
	float newY = Y / other;

	return Vector2D(newX, newY);
}

float Vector2D::Distance(const Vector2D& other)
{
	float vX = X - other.X;
	float vY = Y - other.Y;

	return std::sqrtf((vX * vX) + (vY * vY));
}

float Vector2D::DistanceSquared(const Vector2D& other)
{
	float vX = X - other.X;
	float vY = Y - other.Y;

	return (vX * vX) + (vY * vY);
}

float Vector2D::Magnitude() const
{
	return std::sqrtf((X * X) + (Y * Y));
}

float Vector2D::Angle() const
{
	float rad = atanf(Y / X);
	return RAD2DEG(rad);
}

float Vector2D::Dot(const Vector2D& other) const
{
	return (X * other.X) + (Y * other.Y);
}

float Vector2D::AngleBetween(const Vector2D& other) const
{
	float dot = Dot(other);

	float cosTheta = dot / (Magnitude() * other.Magnitude());

	return RAD2DEG(std::acosf(cosTheta));
}


void Vector2D::Rotate(float degrees)
{
	float radians = (float)DEG2RAD(degrees);
	float cs = cosf(radians);
	float sn = sinf(radians);

	float newX = X * cs - Y * sn;
	float newY = X * sn + Y * cs;

	X = newX;
	Y = newY;
}

void Vector2D::Normalize()
{
	float absV = 1.0f / std::sqrtf((X * X) + (Y * Y));

	X *= absV;
	Y *= absV;
}

Vector2D Vector2D::Rotated(float degrees)
{
	float radians = (float)DEG2RAD(degrees);
	float cs = cosf(radians);
	float sn = sinf(radians);

	float newX = X * cs - Y * sn;
	float newY = X * sn + Y * cs;

	return Vector2D(newX, newY);
}

Vector2D Vector2D::Normalized()
{
	float absV = 1.0f / std::sqrtf((X * X) + (Y * Y));

	float newX = X * absV;
	float newY = Y * absV;

	return Vector2D(newX, newY);
}