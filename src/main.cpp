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
			float		zs[3];
			bool valid = true;

			for (int k = 0; k < 3; k++)
			{
				Vector3 relative = vertices[k] - camera;

				float xCamera = relative.dot(right);
				float yCamera = relative.dot(up);
				float zCamera = relative.dot(player.getDirection());

				if (zCamera <= 0.00001f)
				{
					valid = false;
					break;
				}

				projected[k].x = screen.X / 2.0f
					+ focal * xCamera / zCamera;

				projected[k].y = screen.Y / 2.0f
					- focal * yCamera / zCamera;

				zs[k] = zCamera;
			}

			if (valid)
			{
				object.addTriangle2D(Triangle2D(projected[0], projected[1], projected[2],
										tri.getNormal1(), tri.getNormal2(), tri.getNormal3(),
										zs[0], zs[1], zs[2]));
			}
		}
	}
}

int	game_loop(ObjectsList& objects, sf::RenderWindow& window, screen& screen, Player& player)
{
	sf::Clock clock;

	sf::Image image;
	image.create(screen.X, screen.Y, sf::Color::Black);

	sf::Texture texture;
	if (!texture.create(screen.X, screen.Y))
		return -1;

	sf::Sprite sprite(texture);

	std::vector<float> depthBuffer(screen.X * screen.Y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.restart().asSeconds();

		updatePlayer(window, player, deltaTime);
		calculate_2D(objects, screen, player);

		// Limpiar la imagen
		image.create(screen.X, screen.Y, sf::Color::Black);

		// Rasterizar los triángulos
		paint_all_triangles(objects, image, screen, depthBuffer);

		// Actualizar la textura y mostrarla
		texture.update(image);

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
		std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::infinity());
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