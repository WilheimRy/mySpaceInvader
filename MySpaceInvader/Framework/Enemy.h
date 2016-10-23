#pragma once
#include "entity.h"


class Enemy : public Entity
{
public:
	Enemy();
	Enemy(int x,int y);
	~Enemy();
	void Process(float deltaTime);
};

