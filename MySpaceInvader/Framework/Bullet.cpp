#include "Bullet.h"
#include "sprite.h"
#include <cmath>

Bullet::Bullet(int x, int y)
{
	m_pSprite = 0;
	m_x = x;
	m_y = y;
	this->SetDead(false); //not dead
}


Bullet::~Bullet()
{
}

void Bullet::Process(float deltaTime)
{
	// W02.1: Generic position update, based upon velocity (and time).
	// Attention, m_x is fixed.
	m_y = m_y + this->GetVerticalVelocity()*deltaTime;
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->SetX(static_cast<int>(m_x));
	
}

