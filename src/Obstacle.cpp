//Course: GAME 3001 Assignment 1
//Name: Wanhao (Jerry) Sun and Zijie (Louis) Zhang
#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle()
{
	TheTextureManager::Instance()->load("../Assets/textures/Obstacle.png",
		"obstacle", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("obstacle");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(500.0f, 300.0f));
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::OBSTACLE);

	TheSoundManager::Instance()->load("../Assets/audio/bump.wav",
		"bump", sound_type::SOUND_SFX);
}

Obstacle::~Obstacle()
{

}

void Obstacle::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("obstacle", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Obstacle::update() 
{

}
void Obstacle::clean()
{

}