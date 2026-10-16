#include "3DEngine.hpp"

Vector3::Vector3()
{

}

Vector3::Vector3(const Vector3& copy)
{
	*this = copy;
}

Vector3::Vector3(float x, float y, float z): _x(x), _y(y), _z(z)
{

}

Vector3::~Vector3()
{

}

Vector3&	Vector3::operator=(const Vector3& vec)
{
	if (this != &vec)
	{
		_x = vec._x;
		_y = vec._y;
		_z = vec._z;
	}
	return (*this);
}

Vector3	Vector3::operator+(const Vector3& vec)
{
	return Vector3(_x + vec._x, _y + vec._y, _z + vec._z);
}

Vector3	Vector3::operator-(const Vector3& vec)
{
	return Vector3(_x - vec._x, _y - vec._y, _z - vec._z);
}

float	Vector3::norm()
{
	return (sqrt(_x * _x + _y * _y + _z * _z));
}

Vector3 Vector3::cross(const Vector3& other) const
{
	return Vector3(
		_y * other._z - _z * other._y,
		_z * other._x - _x * other._z,
		_x * other._y - _y * other._x
	);
}

float Vector3::dot(const Vector3& other) const
{
	return _x * other._x + _y * other._y + _z * other._z;
}

void Vector3::normalize()
{
	float length = norm();

	if (length > 0.0f)
	{
		_x /= length;
		_y /= length;
		_z /= length;
	}
}