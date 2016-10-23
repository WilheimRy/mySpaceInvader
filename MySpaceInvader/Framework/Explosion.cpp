#include "Explosion.h"
#include <cassert>
#include "animatedsprite.h"

Explosion::Explosion()
{
}

Explosion::Explosion(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
}

Explosion::~Explosion()
{

}

bool Explosion::Initialise(AnimatedSprite* animatedSprite)
{
	//assert(animatedSprite);
	m_pAnimatedSprite = animatedSprite;
	return (true);
}

void Explosion::Draw(BackBuffer& backBuffer)
{
	m_pAnimatedSprite->Draw(backBuffer);
}
