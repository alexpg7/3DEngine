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