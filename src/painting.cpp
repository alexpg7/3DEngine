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

void paint_triangle(Triangle2D& triangle, sf::Image& image, screen& screen, std::vector<float>& depthBuffer)
{
	sf::Vector2f p1 = triangle.getP1();
	sf::Vector2f p2 = triangle.getP2();
	sf::Vector2f p3 = triangle.getP3();

	// Luz direccional fija
	Vector3 lightDirection(1.0f, -2.0f, -3.0f);
	lightDirection.normalize();

	// Bounding box
	int xmin = static_cast<int>(std::floor(
		std::min({p1.x, p2.x, p3.x})));

	int xmax = static_cast<int>(std::ceil(
		std::max({p1.x, p2.x, p3.x})));

	int ymin = static_cast<int>(std::floor(
		std::min({p1.y, p2.y, p3.y})));

	int ymax = static_cast<int>(std::ceil(
		std::max({p1.y, p2.y, p3.y})));

	xmin = std::max(xmin, 0);
	ymin = std::max(ymin, 0);
	xmax = std::min(xmax, screen.X - 1);
	ymax = std::min(ymax, screen.Y - 1);

	// Rasterizar
	for (int y = ymin; y <= ymax; ++y)
	{
		for (int x = xmin; x <= xmax; ++x)
		{
			float px = x + 0.5f;
			float py = y + 0.5f;

			if (!triangle.isInsideTriangle(px, py))
				continue;

			float denom =
				(p2.y - p3.y) * (p1.x - p3.x) +
				(p3.x - p2.x) * (p1.y - p3.y);

			if (std::abs(denom) < 1e-6f)
				continue;

			float a =
				((p2.y - p3.y) * (px - p3.x) +
				(p3.x - p2.x) * (py - p3.y)) / denom;

			float b =
				((p3.y - p1.y) * (px - p3.x) +
				(p1.x - p3.x) * (py - p3.y)) / denom;

			float c = 1.0f - a - b;

			Vector3 normal =
				triangle.getNormal1() * a +
				triangle.getNormal2() * b +
				triangle.getNormal3() * c;

			normal.normalize();

			float intensity = std::max(
				0.0f,
				normal.dot(lightDirection * -1.0f)
			);

			const float ambientLight = 0.15f;
			intensity = ambientLight + (1.0f - ambientLight) * intensity;

			sf::Uint8 value = static_cast<sf::Uint8>(255.0f * intensity);
			sf::Color color(value, value, value);

			float invZ =
				a / triangle.getZ1() +
				b / triangle.getZ2() +
				c / triangle.getZ3();

			if (invZ <= 0.0f)
				continue;

			float z = 1.0f / invZ;

			int index = y * screen.X + x;

			if (z < depthBuffer[index])
			{
				depthBuffer[index] = z;
				image.setPixel(x, y, color);
			}
		}
	}
}

void paint_all_triangles(ObjectsList& objects, sf::Image& image, screen& screen, std::vector<float>& depthBuffer)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		Object& object = objects[i];

		for (int j = 0; j < object.triangleNum(); ++j)
		{
			Triangle2D& triangle = object.getTriangle2D(j);

			paint_triangle(triangle, image, screen, depthBuffer);
		}
	}
}