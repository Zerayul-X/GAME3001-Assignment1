//Course: GAME 3001 Assignment 1
//Name: Wanhao (Jerry) Sun and Zijie (Louis) Zhang
#pragma once
#ifndef __Background__
#define __Background__

#include "GameObject.h"
#include "TextureManager.h"

class Background : public GameObject {
public:
	Background();
	~Background();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
private:
	void m_move();

	void m_checkBounds();

	void m_reset();
};


#endif /* defined (__Background__) */