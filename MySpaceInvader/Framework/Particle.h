#pragma once
#include "entity.h"

class Particle:public Entity
{
public:
	Particle();
	Particle(int x,int y);
	~Particle();

//public:
	float m_x;
	float m_y;
	float m_velocityX;
	float m_velocityY;
	float m_acceleration;
	float m_age;
};

