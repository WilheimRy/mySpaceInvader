// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include <cassert>

AnimatedSprite::AnimatedSprite()
: m_frameSpeed(0.0f)
, m_frameWidth(0)
, m_timeElapsed(0.0f)
, m_currentFrame(0)
, m_paused(false)
, m_loop(false)
, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);  // changed a little bit??

	StartAnimating();
	
	return (true);
}

void 
AnimatedSprite::AddFrame(int x)
{
	// W02.4: Add the x coordinate to the frame coordinate container.
	frameCoordinateContainer.push_back(x);
}

void 
AnimatedSprite::Process(float deltaTime)
{
	if (m_animating)
	{
		int CoordinateX = 0;
		// if first frame it's the actual x
		//	if (m_currentFrame == 0)
		//	{
		//		CoordinateX = this->GetX();
		//	}
		//	//else it's x+=64 pixel
		//	else
		//	{
		//		CoordinateX += 64;
		//	}

		// W02.4: If not paused...
		// W02.4: Count the time elapsed.
		if (!this->IsPaused())
		{
			m_timeElapsed += deltaTime;
		}

		// W02.4: If the time elapsed is greater than the frame speed.
		// W02.4: Move to the next frame.
		// W02.4: Reset the time elapsed counter.
		if (m_timeElapsed > m_frameSpeed)
		{
			m_currentFrame += 1;
			//AddFrame(CoordinateX);
			m_timeElapsed = 0.0f;
		}

		// W02.4: If the current frame is greater than the number 
		//          of frame in this animation...
		// W02.4: Reset to the first frame.
		if (m_currentFrame >= frameCoordinateContainer.size()) //4
		{
			// W02.4: Stop the animation if it is not looping...
//			if (!m_loop)
//			{
//				m_animating = false;
//			}
			m_currentFrame = 5;
			m_animating = false;
		}

		
	}
	
}

void 
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// W02.4: Draw the particular frame into the backbuffer.
	//          What is the current frame's x coordinate?
	//          What is the frame width?
	//this->SetFrameWidth(64);

	//assert(m_currentFrame>=0 && m_currentFrame<=4);

	if (m_currentFrame>=0&&m_currentFrame<=4)
	{
		int currentX = frameCoordinateContainer[m_currentFrame];
		backbuffer.DrawAnimatedSprite(*this, currentX);
	}
}

void 
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void 
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void 
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool  
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool 
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void 
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool 
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void 
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int AnimatedSprite::getCurrentFrame()
{
	return (m_currentFrame);
}

int AnimatedSprite::getFrameWidth()
{
	return (m_frameWidth);
}
