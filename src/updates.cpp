#include "3DEngine.hpp"

void updatePlayer(sf::RenderWindow& window, Player& player, float deltaTime)
{
	const float moveSpeed = 5.0f;
	const float mouseSensitivity = 0.002f;
	const float jumpSpeed = 5.0f;
	const float gravity = 10.0f;
	const float groundHeight = 0.0f;

	Vector3 forward = player.getDirection();
	forward[2] = 0.0f;
	forward.normalize();

	Vector3 worldUp(0.0f, 0.0f, 1.0f);
	Vector3 right = forward.cross(worldUp);
	right.normalize();

	Vector3 movement(0.0f, 0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement = movement + forward;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement = movement - forward;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement = movement + right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement = movement - right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	if (player.isOnGround())
	{
		movement.normalize();
		player.setPosition(
			player.getPosition() + movement * (moveSpeed * deltaTime)
		);
		player.setLastSpeed(movement * moveSpeed);
	}
	else
		player.setPosition(player.getPosition() + player.getLastSpeed() * deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		&& player.isOnGround())
	{
		player.setVerticalVelocity(jumpSpeed);
		player.setOnGround(false);
	}

	Vector3 position = player.getPosition();

	float verticalVelocity =
		player.getVerticalVelocity() - gravity * deltaTime;

	position[2] += verticalVelocity * deltaTime;

	if (position[2] <= groundHeight)
	{
		position[2] = groundHeight;
		verticalVelocity = 0.0f;
		player.setOnGround(true);
	}

	player.setVerticalVelocity(verticalVelocity);
	player.setPosition(position);

	sf::Vector2i center(
		static_cast<int>(window.getSize().x / 2),
		static_cast<int>(window.getSize().y / 2)
	);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	float deltaX = static_cast<float>(center.x - mousePosition.x);
	float deltaY = static_cast<float>(mousePosition.y - center.y);

	player.setPhi(player.getPhi() + deltaX * mouseSensitivity);
	player.setTheta(player.getTheta() + deltaY * mouseSensitivity);

	const float limit = 0.01f;
	player.setTheta(std::clamp(
		player.getTheta(), limit, 3.14159265f - limit
	));

	sf::Mouse::setPosition(center, window);
}