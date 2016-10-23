#include "Enemy.h"
#include "sprite.h"


Enemy::Enemy()
{
	this->m_pSprite = 0;
	this->m_velocityX = 0.0f;
	this->m_velocityY = 0.0f;
	this->m_dead = false; //not dead
}

Enemy::Enemy(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
}

Enemy::~Enemy()
{

}

void Enemy::Process(float deltaTime)
{
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->SetX(static_cast<int>(m_x));
}
