#include "3DEngine.hpp"

int game_loop()
{
	sf::RenderWindow window(sf::VideoMode({1280, 720}), "Low Poly Engine");

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update

		// Render
		window.clear(sf::Color::Black);

		window.display();
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
	ObjectsList o_list(argv[1]);
	game_loop();
	return 0;
}