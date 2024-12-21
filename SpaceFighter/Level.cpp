
#include "Level.h"
#include "EnemyShip.h"
#include "Blaster.h"
#include "Bomb.h"
#include "GameplayScreen.h"
#include "PlayerShip.h"

std::vector<Explosion *> Level::s_explosions;

int Level::s_levelNum = 1;

// Collision Callback Functions

/** brief Callback function for when the player shoots an enemy. */
void PlayerShootsEnemy(GameObject *pObject1, GameObject *pObject2)
{
	bool m = pObject1->HasMask(CollisionType::Enemy);
	EnemyShip *pEnemyShip = (EnemyShip *)((m) ? pObject1 : pObject2);
	Projectile *pPlayerProjectile = (Projectile *)((!m) ? pObject1 : pObject2);
	pEnemyShip->Hit(pPlayerProjectile->GetDamage());
	pPlayerProjectile->Deactivate();
}

/** brief Callback function for when the player collides with an enemy. */
void PlayerCollidesWithEnemy(GameObject *pObject1, GameObject *pObject2)
{
	bool m = pObject1->HasMask(CollisionType::Player);
	PlayerShip *pPlayerShip = (PlayerShip *)((m) ? pObject1 : pObject2);
	EnemyShip *pEnemyShip = (EnemyShip *)((!m) ? pObject1 : pObject2);
	pPlayerShip->Hit(std::numeric_limits<float>::max());
	pEnemyShip->Hit(std::numeric_limits<float>::max());
}


Level::Level()
{
	m_sectorSize.X = 64;
	m_sectorSize.Y = 64;

	m_sectorCount.X = (float)((Game::GetScreenWidth() / (int)m_sectorSize.X) + 1);
	m_sectorCount.Y = (float)((Game::GetScreenHeight() / (int)m_sectorSize.Y) + 1);

	m_totalSectorCount = m_sectorCount.X * m_sectorCount.Y;

	m_pSectors = new std::vector<GameObject *>[m_totalSectorCount];
	m_pCollisionManager = new CollisionManager();
	
	GameObject::SetCurrentLevel(this);


	// Setup player ship
	m_pPlayerShip = new PlayerShip();
	Blaster *pBlaster = new Blaster("Main Blaster");
	pBlaster->SetProjectilePool(&m_projectiles);
	m_pPlayerShip->AttachItem(pBlaster, Vector2::UNIT_Y * -20);

	Bomb* pBomb = new Bomb("Screen Nuke");
	pBomb->SetTriggerType(TriggerType::Secondary);
	pBomb->SetProjectilePool(&m_projectiles);
	m_pPlayerShip->AttachItem(pBomb, Vector2::UNIT_Y * -20);

	for (int i = 0; i < 1500; i++)
	{
		Projectile *pProjectile = new Projectile();
		m_projectiles.push_back(pProjectile);
		AddGameObject(pProjectile);
	}
	
	m_pPlayerShip->Activate();
	AddGameObject(m_pPlayerShip);

	// Setup collision types
	CollisionManager *pC = GetCollisionManager();

	CollisionType playerShip = (CollisionType::Player | CollisionType::Ship);
	CollisionType playerProjectile = (CollisionType::Player | CollisionType::Projectile);
	CollisionType enemyShip = (CollisionType::Enemy | CollisionType::Ship);

	pC->AddNonCollisionType(playerShip, playerProjectile);
	pC->AddCollisionType(playerProjectile, enemyShip, PlayerShootsEnemy);
	pC->AddCollisionType(playerShip, enemyShip, PlayerCollidesWithEnemy);
}

Level::~Level()
{
	delete[] m_pSectors;
	delete m_pCollisionManager;
	
	
	m_gameObjectIt = m_gameObjects.begin();
	for (; m_gameObjectIt != m_gameObjects.end(); m_gameObjectIt++)
	{
		delete (*m_gameObjectIt);
	}
}


void Level::LoadContent(ResourceManager& resourceManager)
{
	m_pPlayerShip->LoadContent(resourceManager);


	// Setup explosions if they haven't been already
	Explosion* pExplosion;
	if (s_explosions.size() == 0) {
		AudioSample* pExplosionSound = resourceManager.Load<AudioSample>("Audio\\Effects\\Explosion.ogg");
		Animation* pAnimation = resourceManager.Load<Animation>("Animations\\Explosion.anim");
		pAnimation->Stop();

		for (int i = 0; i < 10; i++)
		{
			pExplosion = new Explosion();
			pExplosion->SetAnimation((Animation *)pAnimation->Clone());
			pExplosion->SetSound(pExplosionSound);
			s_explosions.push_back(pExplosion);
		}
	}
}


void Level::HandleInput(const InputState& input)
{
	if (IsScreenTransitioning()) return;

	m_pPlayerShip->HandleInput(input);
	//if (input.IsKeyDown(Key::X)) {
	//	SpawnSuperExplosion(m_pPlayerShip);
	//}
}


void Level::Update(const GameTime& gameTime)
{
	for (unsigned int i = 0; i < m_totalSectorCount; i++)
	{
		m_pSectors[i].clear();
	}

	m_gameObjectIt = m_gameObjects.begin();
	for (; m_gameObjectIt != m_gameObjects.end(); m_gameObjectIt++)
	{
		GameObject *pGameObject = (*m_gameObjectIt);
		pGameObject->Update(gameTime);
	}

	for (unsigned int i = 0; i < m_totalSectorCount; i++)
	{
		if (m_pSectors[i].size() > 1)
		{
			CheckCollisions(m_pSectors[i]);
		}
	}
	
	for (Explosion *pExplosion : s_explosions) pExplosion->Update(gameTime);

	if (!m_pPlayerShip->IsActive()) GetGameplayScreen()->Exit();

	// Exits the level upon the last enemy dying
	if (EnemyShip::GetCount() <= 0) 
	{
		AddLevelNum();
		// Change the number to the current amount of levels
		if (GetLevelNum() >= 5)
		{
			GetGameplayScreen()->Exit();
		}
		else
		{
			GetGameplayScreen()->GameplayScreen::LoadLevel(GetLevelNum());
		}
		
	}

}


void Level::UpdateSectorPosition(GameObject *pGameObject)
{
	Vector2 position = pGameObject->GetPosition();
	//Vector2 previousPosition = pGameObject->GetPreviousPosition();
	Vector2 halfDimensions = pGameObject->GetHalfDimensions();

	int minX = (int)(position.X - halfDimensions.X - 0.5f);
	int maxX = (int)(position.X + halfDimensions.X + 0.5f);
	int minY = (int)(position.Y - halfDimensions.Y - 0.5f);
	int maxY = (int)(position.Y + halfDimensions.Y + 0.5f);

	//// Expand to contain the previous positions
	//minX = Math::Min(minX, (int)(previousPosition.X - halfDimensions.X - 0.5f));
	//maxX = Math::Max(maxX, (int)(previousPosition.X + halfDimensions.X + 0.5f));
	//minY = Math::Min(minY, (int)(previousPosition.Y - halfDimensions.Y - 0.5f));
	//maxY = Math::Max(maxY, (int)(previousPosition.Y + halfDimensions.Y + 0.5f));

	minX = Math::Clamp<int>(0, m_sectorCount.X - 1, minX / (int)m_sectorSize.X);
	maxX = Math::Clamp<int>(0, m_sectorCount.X - 1, maxX / (int)m_sectorSize.X);
	minY = Math::Clamp<int>(0, m_sectorCount.Y - 1, minY / (int)m_sectorSize.Y);
	maxY = Math::Clamp<int>(0, m_sectorCount.Y - 1, maxY / (int)m_sectorSize.Y);


	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			int index = y * (int)m_sectorCount.X + x;

			m_pSectors[index].push_back(pGameObject);
		}
	}
}


void Level::SpawnExplosion(GameObject *pExplodingObject)
{
	Explosion *pExplosion = nullptr;

	for (unsigned int i = 0; i < s_explosions.size(); i++)
	{
		if (!s_explosions[i]->IsActive())
		{
			pExplosion = s_explosions[i];
			break;
		}
	}

	if (!pExplosion) return;

	const float aproximateTextureRadius = 120;
	const float objectRadius = pExplodingObject->GetCollisionRadius();
	const float scaleToObjectSize = (1 / aproximateTextureRadius) * objectRadius * 2;
	const float dramaticEffect = 2.2f;
	const float scale = scaleToObjectSize * dramaticEffect;
	pExplosion->Activate(pExplodingObject->GetPosition(), scale);
}

void Level::SpawnSuperExplosion(GameObject* pExplodingObject)
{
	Explosion* pExplosion = nullptr;

	for (unsigned int i = 0; i < s_explosions.size(); i++)
	{
		if (!s_explosions[i]->IsActive())
		{
			pExplosion = s_explosions[i];
			break;
		}
	}

	if (!pExplosion) return;

	const float aproximateTextureRadius = 2;
	const float objectRadius = 100;
	const float scaleToObjectSize = (1 / aproximateTextureRadius) * objectRadius * 2;
	const float dramaticEffect = 2.2f;
	const float scale = scaleToObjectSize * dramaticEffect;
	pExplosion->Activate(pExplodingObject->GetPosition(), scale);
}


float Level::GetAlpha() const
{
	return GetGameplayScreen()->GetAlpha();
}


void Level::CheckCollisions(std::vector<GameObject *> &gameObjects)
{
	const unsigned int objectCount = (unsigned int)gameObjects.size();

	GameObject *pFirst, *pSecond;

	for (unsigned int i = 0; i < objectCount - 1; i++)
	{
		pFirst = gameObjects[i];
		if (pFirst->IsActive())
		{
			for (unsigned int j = i + 1; j < objectCount; j++)
			{
				if (!pFirst->IsActive()) continue;

				pSecond = gameObjects[j];
				if (pSecond->IsActive())
				{
					m_pCollisionManager->CheckCollision(pFirst, pSecond);
				}
			}
		}
	}
}

void Level::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	const float alpha = GetGameplayScreen()->GetAlpha();

	if (m_pBackground) spriteBatch.Draw(m_pBackground, Vector2::ZERO, Color::WHITE * alpha);

	m_gameObjectIt = m_gameObjects.begin();
	for (; m_gameObjectIt != m_gameObjects.end(); m_gameObjectIt++)
	{
		GameObject *pGameObject = (*m_gameObjectIt);
		pGameObject->Draw(spriteBatch);
	}

	spriteBatch.End();

	// Explosions use additive blending so they need to be drawn after the main sprite batch
	spriteBatch.Begin(SpriteSortMode::Deferred, BlendState::Additive);
	for (Explosion* pExplosion : s_explosions) pExplosion->Draw(spriteBatch);
	spriteBatch.End();
}