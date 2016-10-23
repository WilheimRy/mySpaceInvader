#include "Particle.h"


Particle::Particle()
{
	m_x = 0.0f;
	m_acceleration = 0.0f;
	m_age = 0.0f;
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
	m_y = 0.0f;
}

Particle::Particle(int x, int y)
{
	m_x = x;
	m_y = y;
	m_acceleration = 0.0f;
	m_age = 0.0f;
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
}

Particle::~Particle()
{

}

