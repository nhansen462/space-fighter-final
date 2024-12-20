

#include "Level03.h"
#include "BioEnemyShip.h"


void Level03::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

	const int COUNT = 24;

	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.1, 0.9, 0.2, 0.8, 0.3, 0.7, 0.4, 0.6, 0.5,
		0.5, 0.4, 0.6, 0.3, 0.7, 0.2, 0.8, 0.1, 0.9
	};

	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5,
		3.25, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0, 0.5, 0.0
	};

	float delay = 3.0; // start delay
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += delays[i];
		position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

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

