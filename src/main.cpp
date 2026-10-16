#include "3DEngine.hpp"

void	calculate_2D(ObjectsList& objects, screen& screen, Player& player)
{
	//const float fov = player.fov;
	const float focal = player.focal;

	Vector3 forward = player.getDirection();

	Vector3 worldUp(0.0f, 0.0f, 1.0f);

	Vector3 right = forward.cross(worldUp);
	right.normalize();

	Vector3 up = right.cross(forward);
	up.normalize();

	Vector3 camera = player.getPosition();

	for (int i = 0; i < objects.size(); i++)
	{
		Object& object = objects[i];

		object.clearTriangles2D();

		for (int j = 0; j < object.triangleNum(); j++)
		{
			Triangle& tri = object.getTriangle(j);

			Vector3 vertices[3] = {
				tri.getP1(),
				tri.getP2(),
				tri.getP3()
			};

			sf::Vector2f projected[3];
			bool valid = true;

			for (int k = 0; k < 3; k++)
			{
				Vector3 relative = vertices[k] - camera;

				float xCamera = relative.dot(right);
				float yCamera = relative.dot(up);
				float zCamera = relative.dot(forward);

				// No proyectar puntos detrás o demasiado cerca
				// de la cámara.
				if (zCamera <= 0.001f)
				{
					valid = false;
					break;
				}

				projected[k].x = screen.X / 2.0f
					+ focal * xCamera / zCamera;

				projected[k].y = screen.Y / 2.0f
					- focal * yCamera / zCamera;
			}

			if (valid)
			{
				object.addTriangle2D(Triangle2D(projected[0], projected[1], projected[2]));
			}
		}
	}
}

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

int	game_loop(ObjectsList& objects, sf::RenderWindow& window, screen& screen, Player& player)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		calculate_2D(objects, screen, player);

		// Render
		window.clear(sf::Color::Black);

		paint_all_vertex(window, objects);//screen, objects);
		window.display();
		std::cout << "fps" << std::endl;
	}

	return 0;
}



int	main(int narg, char *argv[])
{
	if (narg < 2)
	{
		std::cerr << "No directory specified, please";
		std::cerr << " insert a directory as an argument (containing .obj files)" << std::endl;
	}
	screen screen;

	screen.X = 1280;
	screen.Y = 900;
	screen.fps = 60;

	ObjectsList o_list(argv[1]);

	sf::RenderWindow window(sf::VideoMode(screen.X, screen.Y), "Low Poly Engine");
	window.setFramerateLimit(screen.fps);

	Player player;

	game_loop(o_list, window, screen, player);
	return 0;
}