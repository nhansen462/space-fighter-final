#include "LevelTest01.h"
#include "BioEnemyShip.h"


void LevelTest01::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

	AudioSample* pBackground = resourceManager.Load<AudioSample>("Audio\\Music\\NightOfNights.mp3");
	pBackground->SetVolume(0.15f);
	pBackground->SetLooping(true);
	SetBackgroundAudio(pBackground);
	pBackground->Play();

	const int COUNT = 3000;

	float delay = 3.0; // start delay
	float xPos = 0.01;
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += 0.003;
		position.Set(xPos * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		xPos += 0.05;
		if (xPos >= 1) { xPos = 0.01; }

		BioEnemyShip* pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);
	}

	// Setup background
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground02.png"));

	//Set the number to whatever the level index is
	Level::SetLevelNum(2);

	Level::LoadContent(resourceManager);
}

