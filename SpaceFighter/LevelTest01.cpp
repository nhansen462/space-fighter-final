#include "LevelTest01.h"
#include "BioEnemyShip.h"
#include "EvasiveEnemyShip.h"
#include "AnnoyingEnemyShip.h"
#include "Boss.h"
#include "BossBlaster.h"

#include <cstdlib>

void LevelTest01::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");
	Texture* pBossTexture = resourceManager.Load<Texture>("Textures\\BioEnemyBoss.png");

	AudioSample* pBackground = resourceManager.Load<AudioSample>("Audio\\Music\\NightOfNights.mp3");
	pBackground->SetVolume(0.15f);
	pBackground->SetLooping(true);
	SetBackgroundAudio(pBackground);
	pBackground->Play();

	const int COUNT = 1000;
	int randomNum = rand() % 3 + 1;
	std::vector<Projectile*> projectiles;
	float delay = 2.0; // start delay
	float xPos = 0.01;
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += 0.003;
		position.Set(xPos * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		xPos += 0.05;
		if (xPos >= 1) { xPos = 0.01; }

		if (randomNum == 1) { 
			BioEnemyShip* pEnemy = new BioEnemyShip();

			pEnemy->SetTexture(pTexture);
			pEnemy->SetCurrentLevel(this);
			pEnemy->Initialize(position, (float)delay);
			AddGameObject(pEnemy);
		}
		if (randomNum == 2) { 
			EvasiveEnemyShip* pEnemy = new EvasiveEnemyShip();

			pEnemy->SetTexture(pTexture);
			pEnemy->SetCurrentLevel(this);
			pEnemy->Initialize(position, (float)delay);
			AddGameObject(pEnemy);
		}
		if (randomNum == 3) { 
			AnnoyingEnemyShip* pEnemy = new AnnoyingEnemyShip();

			pEnemy->SetTexture(pTexture);
			pEnemy->SetCurrentLevel(this);
			pEnemy->Initialize(position, (float)delay);
			AddGameObject(pEnemy);
		}
		randomNum = rand() % 3 + 1;
	}


	Vector2 bossSpawn;
	bossSpawn.Set(800, 200);
	m_pBossShip->SetTexture(pBossTexture);
	m_pBossShip->SetCurrentLevel(this);
	m_pBossShip->Initialize(bossSpawn, (float)delay + 10);
	
	AddGameObject(m_pBossShip);
	

	// Setup background
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground02.png"));

	//Set the number to whatever the level index is
	Level::SetLevelNum(-1);

	Level::LoadContent(resourceManager);
}

