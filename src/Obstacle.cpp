#include "Obstacle.h"


#include "SoundManager.h"
#include "TextureManager.h"

Obstacle::Obstacle()
{
	TextureManager::Instance()->load("../Assets/textures/stone_wall.png", "stone");

	auto size = TextureManager::Instance()->getTextureSize("stone");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/ding.ogg", "ding", SOUND_SFX);
}

Obstacle::~Obstacle()
= default;

void Obstacle::draw()
{
	TextureManager::Instance()->draw("stone", 
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
