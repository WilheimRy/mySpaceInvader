// COMP710 GP 2D Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include "PlayerShip.h"
#include "Enemy.h"
#include <vector>
#include "animatedsprite.h"
#include "Explosion.h"

//bulletSound lib
#include <fmod.hpp>
#include <fmod_errors.h>
#include <conio.h>
#include "ParticlesEmitter.h"


using namespace std;

// Static Members:
Game* Game::sm_pInstance = 0;


Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
{
	pPlayerShip = new PlayerShip;
	particlesemitter = new ParticlesEmitter();
	enemyParticleNum = 50;

}

Game::~Game()
{

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete pPlayerShip;
	pPlayerShip = 0;

	delete particlesemitter;
	particlesemitter = 0;

	delete channel;
	channel = 0;

	delete sm_pInstance;
	sm_pInstance = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	bulletSound->release();
	explosionSound->release();
	system->release();

}

void Game::InitialisePlayerShip()
{
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\ArmsFortAsmodai.png");

	// W02.1: Create the player ship instance.
	pPlayerShip = new PlayerShip;
	pPlayerShip->Initialise(pPlayerSprite);
}

void Game::InitialiseEnemies()
{
	int enemyPositionY = 50;
	for (int i = 0; i < 4; i++)
	{
		int enemyPositionX = 100;
		for (int j = 0; j < 14; j++)
		{
			SpawnEnemy(enemyPositionX, enemyPositionY);
			enemyPositionX += 45;
		}
		enemyPositionY += 40;
	}
}

void Game::InitialiseBulletSound()
{
	system->createSound("sound/bullet.wav", FMOD_DEFAULT, 0, &bulletSound);
	bulletSound->setMode(FMOD_LOOP_OFF);
}

void Game::InitialiseExplosionSound()
{
	system->createSound("sound/explosion.wav", FMOD_DEFAULT, 0, &explosionSound);
	explosionSound->setMode(FMOD_LOOP_OFF);
}

void Game::InitialiseFmodSystem()
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
}

bool Game::InitialiseBackBuffer(bool& value1)
{
	const int width = 850;
	const int height = 600;


	m_pBackBuffer = new BackBuffer();

	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		value1 = (false);
		return true;
	}
	return false;
}

bool Game::InitialiseInputHandler(bool& value1)
{
	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		value1 = (false);
		return true;
	}
	return false;
}

void Game::InitialiseEnemyParticles(size_t i)
{
	int explosionCenterX = explosionContainer[i]->GetPositionX() + 32;
	int explosionCenterY = explosionContainer[i]->GetPositionY() + 32;

	for (size_t j = 0; j < enemyParticleNum; j++)
	{
		SpawnEnemyParticles("assets/alienfragment.png", explosionCenterX, explosionCenterY);
	}
	//save the particle containers in a vector 
	particleContainersVector.push_back(particleContainer);
}

bool
Game::Initialise()
{
	bool value1;
	if (InitialiseBackBuffer(value1)) return value1;

	bool value2;
	if (InitialiseInputHandler(value1)) return value2;

	// W02.1: Load the player ship sprite.
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");
	InitialisePlayerShip();

	// W02.2: Spawn four rows of 14 alien enemies.
	InitialiseEnemies();

	//Initialise sound

	InitialiseFmodSystem();

	//bulletSound
	InitialiseBulletSound();

	//Explosion Sound
	InitialiseExplosionSound();

	// W02.2: Fill the container with these new enemies.
	//needed??

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;


	return (true);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 600.0f;

	assert(m_pInputHandler);

	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize); //Process method

			m_lag -= stepSize;

			++m_numUpdates;
		}

		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void Game::ProcessEnemies(float deltaTime)
{
	for (size_t i = 0; i < enemyContainer.size(); i++)
	{
		enemyContainer[i]->Process(deltaTime);
	}
}

void Game::ProcessBullets(float deltaTime)
{
	for (size_t i = 0; i < bulletContainer.size(); ++i)
	{
		bulletContainer[i]->Process(deltaTime);
	}
}

void Game::CheckCollision()
{
	for (size_t i = 0; i < bulletContainer.size(); ++i)
	{
		for (size_t j = 0; j < enemyContainer.size(); ++j)
		{
			bool collide = bulletContainer[i]->IsCollidingWith(*enemyContainer[j]);
			if (collide)
			{
				bulletContainer[i]->SetDead(true);
				enemyContainer[j]->SetDead(true);
				int explosionPositionX = enemyContainer[j]->GetPositionX();
				int explosionPositionY = enemyContainer[j]->GetPositionY();
				SpawnExplosion(explosionPositionX, explosionPositionY);
				PlayExplosionSound();
			}
		}
	}
}

void Game::ProcessExplosions(float deltaTime)
{
	for (size_t i = 0; i < explosionContainer.size(); ++i)
	{
		explosionContainer[i]->m_pAnimatedSprite->Process(deltaTime);
	}
}

void Game::ProcessPlayerShip(float deltaTime)
{
	pPlayerShip->Process(deltaTime);
}

void Game::ProcessEnemyParticleVector(float deltaTime)
{
	for (size_t i = 0; i < particleContainersVector.size(); i++)
	{
		float xCounter = 0.0f;
		for (size_t j = 0; j < particleContainersVector[i].size(); j++)
		{
			//use xCounter to change initial velocity so to change directions for different particles
			particleContainersVector[i][j]->Process(deltaTime);

			if (j <= 25)
			{
				particleContainersVector[i][j]->m_velocityX = -100 + 4 * xCounter;
				particleContainersVector[i][j]->m_velocityY = sqrt(pow(104, 2) - pow((-100 + 4 * xCounter), 2));
			}
			else
			{
				particleContainersVector[i][j]->m_velocityX = -100 + 4 * xCounter;
				particleContainersVector[i][j]->m_velocityY = -sqrt(pow(104, 2) - pow((-100 + 4 * xCounter), 2));
			}

			xCounter++;
		}
	}
	

}

void Game::RemoveDeadBullets()
{
	for (size_t i = 0; i < bulletContainer.size(); ++i)
	{
		if (bulletContainer[i]->IsDead())
		{
			delete bulletContainer[i];
			bulletContainer.erase(bulletContainer.begin() + i);
		}
	}
}

void Game::RemoveDeadEnemies()
{
	for (size_t i = 0; i < enemyContainer.size(); ++i)
	{
		if (enemyContainer[i]->IsDead())
		{
			delete enemyContainer[i];
			enemyContainer.erase(enemyContainer.begin() + i);
		}
	}
}

void Game::RemoveDeadExplosions()
{
	for (size_t i = 0; i < explosionContainer.size(); ++i)
	{
		//when the explosion animation is finished, initialise the  Enemyparticles
		if (explosionContainer[i]->m_pAnimatedSprite->IsAnimating() == false)
		{
			//get the explosion center position
			InitialiseEnemyParticles(i);
			delete explosionContainer[i];
			explosionContainer.erase(explosionContainer.begin() + i);
		}
	}
}

void Game::RemoveDeadParticles()
{
 	for (size_t i = 0; i < particleContainersVector.size(); i++)
	{
		for (size_t j = 0; j < particleContainersVector[i].size(); j++)
		{
			if (particleContainersVector[i][j]->IsDead())
			{
				delete particleContainersVector[i][j]->m_pSprite;
				delete particleContainersVector[i][j]; //delete enemyparticle
				particleContainersVector[i].erase(particleContainersVector[i].begin() + j);
			}
		}
		if (particleContainersVector[i].size()==0)
		{
			particleContainersVector.erase(particleContainersVector.begin() + i);
		}
	}
}

void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:

	// Ex003.5: Process each alien enemy in the container.
	ProcessEnemies(deltaTime);

	// W02.3: Process each bullet in the container.
	ProcessBullets(deltaTime);

	// W02.1: Update player...
	ProcessPlayerShip(deltaTime);

	//process the explosion animatedSprite
	ProcessExplosions(deltaTime);

	//process the enemyParticles
	ProcessEnemyParticleVector(deltaTime);

	// W02.3: Check for bullet vs alien enemy collisions...
	// W02.3: For each bullet
	// W02.3: For each alien enemy
	// W02.3: Check collision between two entities.
	// W02.3: If collided, destory both and spawn explosion.
	CheckCollision();

	// W02.3: Remove any dead enemy aliens from the container...
	RemoveDeadEnemies();

	// W02.3: Remove any dead bullets from the container...
	RemoveDeadBullets();

	//remove dead particles
	RemoveDeadParticles();

	// W02.3: Remove any dead explosions from the container...
	RemoveDeadExplosions();


}

void Game::DrawEnemies()
{
	for (size_t i = 0; i < enemyContainer.size(); ++i)
	{
		if (enemyContainer[i]->IsDead() == false)
		{
			enemyContainer[i]->Draw(*m_pBackBuffer);
		}
	}
}

void Game::DrawBullets()
{
	for (size_t i = 0; i < bulletContainer.size(); ++i)
	{
		if (bulletContainer[i]->IsDead() == false)
		{
			bulletContainer[i]->Draw(*m_pBackBuffer);
		}
	}
}

void Game::DrawPlayerShip()
{
	pPlayerShip->Draw(*m_pBackBuffer);
}

void Game::DrawExplosions()
{
	for (size_t i = 0; i < explosionContainer.size(); ++i)
	{
		explosionContainer[i]->Draw(*m_pBackBuffer);
	}
}

void Game::DrawEnemyParticles()
{
	for (size_t i = 0; i < particleContainersVector.size(); i++)
	{
		for (size_t j = 0; j < particleContainersVector[i].size(); j++)
		{
			if (particleContainersVector[i][j]->IsDead() == false)
			{
				particleContainersVector[i][j]->Draw(*m_pBackBuffer);
			}
		}
	}
	
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	// W02.2: Draw all enemy aliens in container...
	DrawEnemies();

	// W02.3: Draw all bullets in container...
	DrawBullets();

	// W02.1: Draw the player ship...
	DrawPlayerShip();

	// draw the explosion
	DrawExplosions();

	//draw the EnemyParticles
	DrawEnemyParticles();

	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void
Game::MoveSpaceShipLeft()
{
	// W02.1: Tell the player ship to move left.
	pPlayerShip->SetHorizontalVelocity(-100);  //bug, the ship won't stop??
}

// W02.1: Add the method to tell the player ship to move right...
void
Game::MoveSpaceShipRight()
{
	// W02.1: Tell the player ship to move right.
	pPlayerShip->SetHorizontalVelocity(100);
}

void
Game::StopSpaceShip()
{
	pPlayerShip->SetHorizontalVelocity(0);
}

// W02.3: Space a Bullet in game.
void
Game::FireSpaceShipBullet()
{
	// W02.3: Load the player bullet sprite.      
	Sprite* pBulletSprite = m_pBackBuffer->CreateSprite("assets\\Bullet3350.png");
	int shipX = pPlayerShip->GetPositionX();
	int shipY = pPlayerShip->GetPositionY();
	//	pBulletSprite->SetX(shipX);
	//	pBulletSprite->SetY(shipY);

	// W02.3: Create a new bullet object.
	Bullet* bullet = new Bullet(shipX + 20, shipY);
	bullet->Initialise(pBulletSprite);
	// W02.3: Set the bullets vertical velocity.
	bullet->SetVerticalVelocity(-125);
	// W02.3: Add the new bullet to the bullet container.
	bulletContainer.push_back(bullet);
}

// W02.2: Spawn a Enemy in game.
void
Game::SpawnEnemy(int x, int y)
{
	// W02.2: Load the alien enemy sprite file.
	Sprite* pEnemySprite = m_pBackBuffer->CreateSprite("assets/Enemy5050black.png");
	pEnemySprite->SetX(x);
	pEnemySprite->SetY(y);

	// W02.2: Create a new Enemy object. 
	Enemy* enemy = new Enemy(x, y);
	enemy->Initialise(pEnemySprite);

	// W02.2: Add the new Enemy to the enemy container.
	enemyContainer.push_back(enemy);

}

//x,y are the coordinates of the explosion(the enemy)
void
Game::SpawnExplosion(int x, int y)
{
	//initialise the Explosion and Sprite
	AnimatedSprite* explosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\explosion.png");
	explosionSprite->SetX(x);
	explosionSprite->SetY(y);

	Explosion* explosion = new Explosion(x, y);
	explosion->Initialise(explosionSprite);

	explosionContainer.push_back(explosion);

}

void
Game::PlayBulletSound()
{
	system->playSound(bulletSound, 0, false, &channel);
	channel->setVolume(50.0f);
}

void
Game::PlayExplosionSound()
{
	system->playSound(explosionSound, 0, false, &channel);
	channel->setVolume(50.0f);
}

void 
Game::SpawnEnemyParticles(char* spriteAddress, int positionX, int positionY)
{
	Sprite* pEnemyParticleSprite = m_pBackBuffer->CreateSprite(spriteAddress);
	pEnemyParticleSprite->SetX(positionX);
	pEnemyParticleSprite->SetY(positionY);
	// W02.2: Create a new Enemy particle object. 
	EnemyParticle* enemyParticle = new EnemyParticle(positionX, positionY);
	enemyParticle->Initialise(pEnemyParticleSprite);

	// W02.2: Add the new Enemy particle to the enemy container.
	particleContainer.push_back(enemyParticle);
	
}
