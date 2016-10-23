#include "EnemyParticle.h"

#include "sprite.h"
#include <cmath>
#include <cassert>


EnemyParticle::EnemyParticle()
{
	this->m_x = 0;
	this->m_y = 0;
	this->m_age = 0;
	this->m_acceleration = 0;
	this->m_velocityX = 0;
	this->m_velocityY = 0;
}


EnemyParticle::~EnemyParticle()
{
}

EnemyParticle::EnemyParticle(int x, int y)
{
	m_x = x;
	m_y = y;
	initialX = 0.0f;
	initialY = 0.0f;
}

void EnemyParticle::Process(float deltaTime)
{
	//For every particle, every time set the initial position
	if (m_velocityX == 0)
	{
		initialX = m_x;
		initialY = m_y;

//		m_pSprite->SetX(static_cast<int>(m_x));
//		m_pSprite->SetY(static_cast<int>(m_y));
	}
	else
	{
		// W02.1: Generic position update, based upon velocity (and time).
		m_x = m_x + m_velocityX*deltaTime;
		m_y = m_y + m_velocityY*deltaTime;

		m_pSprite->SetX(static_cast<int>(m_x));
		m_pSprite->SetY(static_cast<int>(m_y));

		double pDistance = sqrt((pow((m_x - initialX), 2) + pow((m_y - initialY), 2)));

		//use the radius to calculate 
		if (pDistance > 40)
		{
			SetDead(true);
		}
	}
}
