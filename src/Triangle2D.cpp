#include "3DEngine.hpp"

Triangle2D::Triangle2D(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3): _p1(p1), _p2(p2), _p3(p3)
{

}

void Triangle2D::draw(sf::RenderWindow& window) const
{
	sf::ConvexShape triangle(3);

	triangle.setPoint(0, _p1);
	triangle.setPoint(1, _p2);
	triangle.setPoint(2, _p3);

	triangle.setFillColor(sf::Color(180, 180, 180));
	triangle.setOutlineColor(sf::Color::Black);
	triangle.setOutlineThickness(1.0f);

	window.draw(triangle);
}