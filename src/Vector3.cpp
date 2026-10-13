#include "3DEngine.hpp"

Vector3::Vector3()
{

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

float	Vector3::norm()
{
	return (sqrt(_x * _x + _y * _y + _z * _z));
}

Vector3	Vector3::operator+(const Vector3& vec)
{
	return Vector3(_x + vec._x, _y + vec._y, _z + vec._z);
}

Vector3	Vector3::operator-(const Vector3& vec)
{
	return Vector3(_x - vec._x, _y - vec._y, _z - vec._z);
}