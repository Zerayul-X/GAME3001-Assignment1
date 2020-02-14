//Course: GAME 3001 Assignment 1
//Name: Wanhao (Jerry) Sun and Zijie (Louis) Zhang
#include "Background.h"
#include "Game.h"

Background::Background()
{
	TheTextureManager::Instance()->load("../Assets/textures/Instruction.png",
		"instruction", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("instruction");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::TARGET);

	TheSoundManager::Instance()->load("../Assets/audio/backgroundMusic.mp3",
		"bgm", sound_type::SOUND_MUSIC);
}

Background::~Background()
{
}

void Background::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("instruction", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Background::update()
{
}

void Background::clean()
{
}

void Background::m_move()
{
}

void Background::m_checkBounds()
{
}

void Background::m_reset()
{
}
