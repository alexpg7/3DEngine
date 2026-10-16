#include "3DEngine.hpp"

Player::Player(): _position(0.0f, 5.0f, 0.0f),
_theta(1.57079632679f),
_phi(-1.57079632679f),
focal(640.0),
fov(M_PI / 2)
{
	_vz = 0.0f;
	_onGround = true;
	_lastSpeed = Vector3();
}

Player::Player(Vector3 position, float theta, float phi, float focal, float fov):
_position(position),
_theta(theta),
_phi(phi),
focal(focal),
fov(fov)
{
	_vz = 0.0f;
	_onGround = true;
	_lastSpeed = Vector3();
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

float Player::getTheta()
{
	return _theta;
}

float Player::getPhi()
{
	return _phi;
}

bool	Player::isOnGround()
{
	return _onGround;
}

void	Player::setOnGround(bool state)
{
	_onGround = state;
}

void	Player::setVerticalVelocity(float v)
{
	_vz = v;
}

float	Player::getVerticalVelocity()
{
	return _vz;
}

void	Player::setLastSpeed(Vector3 speed)
{
	_lastSpeed = speed;
}

Vector3	Player::getLastSpeed()
{
	return _lastSpeed;
}