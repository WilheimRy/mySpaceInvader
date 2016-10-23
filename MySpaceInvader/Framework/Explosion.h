#pragma once
#include "entity.h"

class AnimatedSprite;

class Explosion: public Entity
{

public:
	Explosion();
	Explosion(int x,int y);
	~Explosion();

	bool Initialise(AnimatedSprite* animatedSprite);
	void Draw(BackBuffer& backBuffer);

	AnimatedSprite* m_pAnimatedSprite;

};

