// COMP710 GP 2D Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <cmath>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	//assert(sprite);
	m_pSprite = sprite;
	return (true);
}

void
Entity::Process(float deltaTime)
{
	if (GetHorizontalVelocity() == 0)
	{
		m_pSprite->SetX(static_cast<int>(m_x));
		m_pSprite->SetY(static_cast<int>(m_y));
	}
	else
	{
		// W02.1: Generic position update, based upon velocity (and time).
		m_x = m_x + this->GetHorizontalVelocity()*deltaTime;
		m_y = m_y + this->GetVerticalVelocity()*deltaTime;

		m_pSprite->SetX(static_cast<int>(m_x));
		m_pSprite->SetY(static_cast<int>(m_y));

		// W02.1: Boundary checking and position capping. 
		if (m_x<50)
		{
			m_x = 50;
		}
		if (m_x>750)
		{
			m_x = 750;
		}

		if (m_y<50)
		{
			m_y = 50;
		}

		if (m_y>750)
		{
			m_y = 750;
		}
	}
}

void
Entity::Draw(BackBuffer& backBuffer)
{
	//assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// W02.3: Generic Entity Collision routine.
	// W02.3: Does this object collide with the e object?
	// W02.3: Create a circle for each entity (this and e).

	//get absolute center coordinate of current entity
	int centerX = (this->GetPositionX() + this->m_pSprite->GetWidth() / 2);
	int centerY = (this->GetPositionY() + this->m_pSprite->GetHeight() / 2);
	int r = (this->m_pSprite->GetWidth() > this->m_pSprite->GetHeight()) ? (this->m_pSprite->GetWidth() / 2) : (this->m_pSprite->GetHeight() / 2);

	int centerEX = (e.GetPositionX() + e.m_pSprite->GetWidth() / 2);
	int centerEY = (e.GetPositionY() + e.m_pSprite->GetHeight() / 2);
	int rE = (e.m_pSprite->GetWidth() > e.m_pSprite->GetHeight()) ? (e.m_pSprite->GetWidth() / 2) : (e.m_pSprite->GetHeight() / 2);
	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.
	// W02.3: Return result of collision.
	//collision condition
	double collideResult = sqrt(pow((centerEX - centerX), 2) + pow((centerEY - centerY), 2)) - r - rE;
	bool collisionCondition = collideResult < 0;
	if (collisionCondition)
	{
		return true;
	}
	return (false); // W02.4 Change return value!
}

void
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool Entity::IsDead() const
{
	return (m_dead);
}

float
Entity::GetPositionX()
{
	return (m_x);
}

float
Entity::GetPositionY()
{
	return (m_y);
}

float
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

