#ifndef __VEC2D_H_
#define __VEC2D_H_

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();

	float X, Y;

	static Vector2D Add(const Vector2D& one, const Vector2D& two);
	static Vector2D Multiply(const Vector2D& one, const Vector2D& two);
	static Vector2D Subtract(const Vector2D& one, const Vector2D& two);
	static Vector2D Divide(const Vector2D& one, const Vector2D& two);

	static Vector2D Clamp(Vector2D& value, const Vector2D& min, const Vector2D& max);
	static float Distance(const Vector2D& first, const Vector2D& second);
	static float DistanceSquared(const Vector2D& first, const Vector2D& second);
	static float Dot(const Vector2D& first, const Vector2D& second);

	Vector2D& operator+=(const Vector2D& other);
	Vector2D operator+(const Vector2D& other);
	
	Vector2D& operator-=(const Vector2D& other);
	Vector2D operator-(const Vector2D& other);

	Vector2D& operator*=(const Vector2D& other);
	Vector2D operator*(const Vector2D& other);

	Vector2D& operator/=(const Vector2D& other);
	Vector2D operator/(const Vector2D& other);

	Vector2D& operator*=(const float other);
	Vector2D operator*(const float other);

	Vector2D& operator/=(const float other);
	Vector2D operator/(const float other);

	float Distance(const Vector2D& other);
	float DistanceSquared(const Vector2D& other);

	float Magnitude() const;
	float Angle() const;

	float Dot(const Vector2D& other) const;
	float AngleBetween(const Vector2D& other) const;

	void Rotate(float degrees);
	void Normalize();

	Vector2D Rotated(float degrees);
	Vector2D Normalized();

	// cannot initialize these to be const because the type hasn't been completed yet by this time of compilation
	// solution: don't touch them!
	static Vector2D Zero;
	static Vector2D Unit;
	static Vector2D UnitX;
	static Vector2D UnitY;
};

#endif //__VEC2D_H_