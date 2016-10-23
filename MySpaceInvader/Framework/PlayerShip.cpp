#include "PlayerShip.h"


PlayerShip::PlayerShip()
{
	/*m_pSprite(0)
		, m_x(0.0f)
		, m_y(0.0f)
		, m_velocityX(0.0f)
		, m_velocityY(0.0f)
		, m_dead(false)*/
	this->m_pSprite = 0;
	this->m_x = 400.0f;
	this->m_y = 500.0f;
	this->m_velocityX = 0.0f;
	this->m_velocityY = 0.0f;
	this->m_dead = false;
}


PlayerShip::~PlayerShip()
{

}




