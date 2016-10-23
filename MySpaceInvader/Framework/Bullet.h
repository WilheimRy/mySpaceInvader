#pragma once
#include "entity.h"

class Enemy;

class Bullet: public Entity
{
public:
	Bullet(int x,int y);
	~Bullet();
	void Process(float deltaTime);

};

