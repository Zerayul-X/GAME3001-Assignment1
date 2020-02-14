//Course: GAME 3001 Assignment 1
//Name: Wanhao (Jerry) Sun and Zijie (Louis) Zhang
#pragma once
#ifndef __STEERING_STATE__
#define __STEERING_STATE__

enum SteeringState {
	IDLE,
	SEEK,
	ARRIVE,
	AVOID,
	FLEE,
	AVOIDLEFT,
	AVOIDRIGHT,
	NUM_OF_STATES
};

#endif /* defined (__STEERING_STATE__)*/