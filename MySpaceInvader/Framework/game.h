// COMP710 GP 2D Framework
#ifndef __GAME_H__
#define __GAME_H__
#include "PlayerShip.h"
#include "Enemy.h"
#include <vector>
#include "Bullet.h"
#include "Explosion.h"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <conio.h>
#include "ParticlesEmitter.h"
#include <map>

using namespace std;

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();
	void InitialisePlayerShip();
	void InitialiseEnemies();
	void InitialiseBulletSound();
	void InitialiseExplosionSound();
	void InitialiseFmodSystem();
	bool InitialiseBackBuffer(bool& value1);
	bool InitialiseInputHandler(bool& value1);
	void SpawnEnemyParticles(char* spriteAddress, int positionX, int positionY);
	bool Initialise();
	bool DoGameLoop();

	//Process method
	void ProcessEnemies(float deltaTime);
	void ProcessBullets(float deltaTime);
	void CheckCollision();
	void ProcessExplosions(float deltaTime);
	void ProcessPlayerShip(float deltaTime);
	void ProcessEnemyParticleVector(float deltaTime);
	void RemoveDeadBullets();
	void RemoveDeadEnemies();
	void InitialiseEnemyParticles(size_t i);
	void RemoveDeadExplosions();
	void RemoveDeadParticles();
	void Quit();

	void MoveSpaceShipLeft();
	void StopSpaceShip();
	void MoveSpaceShipRight();
	void FireSpaceShipBullet();

	//sound
	void PlayBulletSound();
	void PlayExplosionSound();

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);
	
protected:
	void Process(float deltaTime);
	void DrawEnemies();
	void DrawBullets();
	void DrawPlayerShip();
	void DrawExplosions();
	void DrawEnemyParticles();
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

	FMOD::System *system;
	FMOD::Sound *bulletSound,*explosionSound;
	FMOD::Channel *channel = 0;

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;
	int enemyParticleNum;

	// Game Entities:
	// W02.1: Add a PlayerShip field.    
	PlayerShip* pPlayerShip;
	// W02.2: Add an alien enemy container field.
	vector<Enemy*> enemyContainer;
	// W02.3: Add a bullet container field.
	vector<Bullet*> bulletContainer;

	//  add an Explosion container field.
	vector<Explosion*>explosionContainer;

	ParticlesEmitter* particlesemitter;

	//relates between index and EnemyparticleContainers
	vector<vector<EnemyParticle*>> particleContainersVector;
	vector<EnemyParticle*> particleContainer;

private:

};

#endif // __GAME_H__
