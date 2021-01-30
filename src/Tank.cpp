#include "Tank.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"


Tank::Tank()
{
	TextureManager::Instance()->load("../Assets/textures/tank.png", "tank");

	auto size = TextureManager::Instance()->getTextureSize("tank");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	
	setType(TANK);
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
}

Tank::~Tank() = default;

void Tank::draw()
{
	TextureManager::Instance()->draw("tank",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + getOrientation() * 60.0f));
}

void Tank::update()
{
	m_Move();
}

void Tank::clean()
{
}

void Tank::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void Tank::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 Tank::getOrientation() const
{
	return m_orientation;
}

void Tank::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float Tank::getRotation() const
{
	return m_rotationAngle;
}

void Tank::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = 0;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float Tank::getTurnRate() const
{
	return m_turnRate;
}

void Tank::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float Tank::getAccelerationRate() const
{
	return m_accelerationRate;
}

void Tank::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Tank::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using the formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}
