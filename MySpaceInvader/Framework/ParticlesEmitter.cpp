#include "ParticlesEmitter.h"
#include "sprite.h"
#include "entity.h"
#include <cassert>
#include "EnemyParticle.h"
#include <ctime>

ParticlesEmitter::ParticlesEmitter()
{
	v_x = 0.0f;
	v_y = 0.0f;
	m_pSprite = 0;
}


ParticlesEmitter::~ParticlesEmitter()
{
	delete m_pSprite;
	m_pSprite = 0;
}



//void
//ParticlesEmitter::Process(float deltaTime)
//{
//	int initialX = 0;
//	int initialY = 0;
//	for (size_t i = 0; i < particleContainer.size(); i++)
//	{
//		if (particleContainer[i]->m_velocityX == 0)
//		{
//			// in absolute coordinate, used for calculating the distance
//			initialX = particleContainer[i]->m_x;
//			initialY = particleContainer[i]->m_y;
//			m_pSprite->SetX(static_cast<int>(particleContainer[i]->m_x));
//			m_pSprite->SetY(static_cast<int>(particleContainer[i]->m_y));
//		}
//		else
//		{
//			// W02.1: Generic position update, based upon velocity (and time).
//			particleContainer[i]->m_x = particleContainer[i]->m_x + this->particleContainer[i]->m_velocityX*deltaTime;
//			particleContainer[i]->m_y = particleContainer[i]->m_y + this->particleContainer[i]->m_velocityY*deltaTime;
//
//			m_pSprite->SetX(static_cast<int>(particleContainer[i]->m_x));
//			m_pSprite->SetY(static_cast<int>(particleContainer[i]->m_y));
//
//			double pDistance = sqrt((pow((particleContainer[i]->m_x - initialX), 2) + pow((particleContainer[i]->m_y - initialY), 2)));
//
//			//use the radius to calculate 
//			if (pDistance > 32)
//			{
//				particleContainer[i]->SetDead(true);
//			}
//		}
//	}
//
//
//}

void
ParticlesEmitter::Draw(BackBuffer& backBuffer)
{
	//assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}
