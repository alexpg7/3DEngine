#include "3DEngine.hpp"

Player::Player(): _position(0.0f, 0.0f, 5.0f), _theta(1.57079632679f), _phi(-1.57079632679f)
{

}

Player::Player(Vector3 position, float theta, float phi): _position(position), _theta(theta), _phi(phi)
{

}

Player::~Player(){

}

Vector3 Player::getPosition() const
{
	return _position;
}

Vector3 Player::getDirection() const
{
	return Vector3(
		std::sin(_theta) * std::cos(_phi),
		std::sin(_theta) * std::sin(_phi),
		std::cos(_theta)
	);
}

void Player::setPosition(Vector3 position)
{
	_position = position;
}

void Player::setTheta(float theta)
{
	_theta = theta;
}

void Player::setPhi(float phi)
{
	_phi = phi;
}