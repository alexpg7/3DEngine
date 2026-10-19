#include "3DEngine.hpp"

Triangle2D::Triangle2D(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3,
Vector3 norm1, Vector3 norm2, Vector3 norm3,
float z1, float z2, float z3):
_p1(p1),
_p2(p2),
_p3(p3),
_norm1(norm1),
_norm2(norm2),
_norm3(norm3),
_z1(z1),
_z2(z2),
_z3(z3)
{

}

Triangle2D::Triangle2D():
_p1(0.0f, 0.0f),
_p2(0.0f, 0.0f),
_p3(0.0f, 0.0f),
_norm1(0.0f, 0.0f, 0.0f),
_norm2(0.0f, 0.0f, 0.0f),
_norm3(0.0f, 0.0f, 0.0f),
_z1(0.0f),
_z2(0.0f),
_z3(0.0f)
{
}

sf::Vector2f&	Triangle2D::getP1()
{
	return _p1;
}

sf::Vector2f&	Triangle2D::getP2()
{
	return _p2;
}

sf::Vector2f&	Triangle2D::getP3()
{
	return _p3;
}

Vector3&	Triangle2D::getNormal1()
{
	return _norm1;
}

Vector3&	Triangle2D::getNormal2()
{
	return _norm2;
}

Vector3&	Triangle2D::getNormal3()
{
	return _norm3;
}

float&	Triangle2D::getZ1()
{
	return _z1;
}

float&	Triangle2D::getZ2()
{
	return _z2;
}

float&	Triangle2D::getZ3()
{
	return _z3;
}

bool	Triangle2D::isInsideTriangle(float x, float y)
{
	sf::Vector2f p1 = getP1();
	sf::Vector2f p2 = getP2();
	sf::Vector2f p3 = getP3();

	float d1 = (x - p2.x) * (p1.y - p2.y)
			- (p1.x - p2.x) * (y - p2.y);

	float d2 = (x - p3.x) * (p2.y - p3.y)
			- (p2.x - p3.x) * (y - p3.y);

	float d3 = (x - p1.x) * (p3.y - p1.y)
			- (p3.x - p1.x) * (y - p1.y);

	bool hasNegative = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool hasPositive = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(hasNegative && hasPositive);
}