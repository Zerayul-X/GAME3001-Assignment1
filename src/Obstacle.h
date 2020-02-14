//Course: GAME 3001 Assignment 1
//Name: Wanhao (Jerry) Sun and Zijie (Louis) Zhang
#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Obstacle :
	public GameObject
{
public:
	Obstacle();
	~Obstacle();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

private:

};


#endif /* defined (__OBSTACLE__) */

