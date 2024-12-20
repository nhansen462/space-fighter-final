

#include "Level01.h"
#include "BioEnemyShip.h"


void Level01::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture *pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

	AudioSample* pBackground = resourceManager.Load<AudioSample>("Audio\\Music\\Voyage1969.mp3");
	pBackground->SetVolume(0.15f);
	pBackground->SetLooping(true);
	SetBackgroundAudio(pBackground);
	pBackground->Play();

	const int COUNT = 21;

	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55
	};
	
	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3
	};

	float delay = 3.0; // start delay
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += delays[i];
		position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		BioEnemyShip *pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);
	}

	// Setup background
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground02.png"));

	//Set the number to whatever the level index is
	Level::SetLevelNum(0);

	Level::LoadContent(resourceManager);
}

