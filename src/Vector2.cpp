#include "3DEngine.hpp"

Vector2::Vector2()
{

}

Vector2::Vector2(const Vector2& copy)
{
	*this = copy;
}

Vector2::Vector2(float x, float y): _x(x), _y(y)
{

}

Vector2::~Vector2()
{

}

Vector2&	Vector2::operator=(const Vector2& vec)
{
	if (this != &vec)
	{
		_x = vec._x;
		_y = vec._y;
	}
	return (*this);
}

float	Vector2::norm()
{
	return (sqrt(_x * _x + _y * _y + _z * _z));
}

Vector2	Vector2::operator+(const Vector2& vec)
{
	return Vector2(_x + vec._x, _y + vec._y);
}

Vector2	Vector2::operator-(const Vector2& vec)
{
	return Vector2(_x - vec._x, _y - vec._y);
}