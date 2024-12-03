
#include "EvasiveEnemyShip.h"
#include "Level.h"
#include <vector>


EvasiveEnemyShip::EvasiveEnemyShip()
{
	SetSpeed(150);
	SetMaxHitPoints(1);
	SetCollisionRadius(20);
}


void EvasiveEnemyShip::Update(const GameTime& gameTime)
{
	float rand = (Math::GetRandomFloat() - 0.5) * 4;
	int count = 0;
	if (IsActive())
	{
	

		// Initializing variables
		int desiredX = GetRandomX();
		int desiredY = GetRandomY();
		int width = Game::GetScreenWidth();
		int height = Game::GetScreenHeight();
		bool started = GetStarted();
		Vector2 position = GetPosition();
		
		// Run once when the enemy is created
		if (started = false)
		{
			desiredX = std::rand() % width + 1;
			desiredY = std::rand() % height + 1;
			SetRandomX(desiredX);
			SetRandomY(desiredY);
		}

		std::cout << position.X;


		float x = 0;//sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
		x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f;// + rand;
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());
		//if (count > (Math::GetRandomInt(30, 180))) { rand *= -1; }
		//count++;
		if (!IsOnScreen()) Deactivate();
		
	}

	EnemyShip::Update(gameTime);
}


void EvasiveEnemyShip::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}