#include "Level03.h"
#include "BioEnemyShip.h"


void Level03::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

	const int COUNT = 10000;

	float delay = 3.0; // start delay
	float xPos = 0.01;
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += 0.001;
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
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground03.png"));

	Level::LoadContent(resourceManager);
}

