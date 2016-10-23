#pragma once
#include "Particle.h"

class EnemyParticle: public Particle
{
public:
	EnemyParticle();
	~EnemyParticle();
	EnemyParticle(int x, int y);

	void Process(float deltaTime);

	Sprite* m_pSprite;

//	float m_velocityX;
//	float m_velocityY;

	float initialX;
	float initialY;
};

