#pragma once
#include "entity.h"
#include "Sprite.h"

class PlayerShip:public Entity
{
public:
	PlayerShip();
	~PlayerShip();


protected:
	Sprite* m_pSprite=0;
};

