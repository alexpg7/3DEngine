#include "3DEngine.hpp"

Triangle2D::Triangle2D(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3): _p1(p1), _p2(p2), _p3(p3)
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