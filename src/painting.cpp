#include "3DEngine.hpp"

void	paint_all_vertex(sf::RenderWindow&window, ObjectsList& objects)//screen& screen, ObjectsList& objects)
{
	const float radius = 20.0f;

	sf::CircleShape point(radius);
	point.setFillColor(sf::Color::Red);
	point.setOrigin(sf::Vector2f(radius, radius));

	for (int i = 0; i < objects.size(); i++)
	{
		Object& object = objects[i];

		for (int j = 0; j < object.triangleNum(); j++)
		{
			Triangle2D& tri = object.getTriangle2D(j);

			point.setPosition(tri.getP1());
			window.draw(point);

			point.setPosition(tri.getP2());
			window.draw(point);

			point.setPosition(tri.getP3());
			window.draw(point);
		}
	}
}

void paint_triangle(Triangle2D& triangle, sf::Image& image, screen& screen)
{
	sf::Vector2f p1 = triangle.getP1();
	sf::Vector2f p2 = triangle.getP2();
	sf::Vector2f p3 = triangle.getP3();

	// Bounding box
	int xmin = static_cast<int>(std::floor(
		std::min({p1.x, p2.x, p3.x})));

	int xmax = static_cast<int>(std::ceil(
		std::max({p1.x, p2.x, p3.x})));

	int ymin = static_cast<int>(std::floor(
		std::min({p1.y, p2.y, p3.y})));

	int ymax = static_cast<int>(std::ceil(
		std::max({p1.y, p2.y, p3.y})));

	// Recortar a los límites de la pantalla
	xmin = std::max(xmin, 0);
	ymin = std::max(ymin, 0);
	xmax = std::min(xmax, screen.X - 1);
	ymax = std::min(ymax, screen.Y - 1);

	// Rasterizar
	for (int y = ymin; y <= ymax; ++y)
	{
		for (int x = xmin; x <= xmax; ++x)
		{
			if (triangle.isInsideTriangle(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f))
			{
				image.setPixel(x, y, sf::Color::White);
			}
		}
	}
}

void paint_all_triangles(ObjectsList& objects, sf::Image& image, screen& screen)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		Object& object = objects[i];

		for (int j = 0; j < object.triangleNum(); ++j)
		{
			Triangle2D& triangle = object.getTriangle2D(j);

			paint_triangle(triangle, image, screen);
		}
	}
}