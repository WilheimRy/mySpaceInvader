#pragma once
#include "Particle.h"
#include <vector>
#include "backbuffer.h"
#include "entity.h"
#include "EnemyParticle.h"


using namespace std;

class ParticlesEmitter
{
public:
	ParticlesEmitter();
	~ParticlesEmitter();
	//void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	//BackBuffer* m_pBackBuffer;
	Sprite* m_pSprite;
	

	float v_x = 0;
	float v_y;
};

