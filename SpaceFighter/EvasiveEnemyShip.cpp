
#include "EvasiveEnemyShip.h"
#include "Level.h"
#include <vector>


EvasiveEnemyShip::EvasiveEnemyShip()
{
	SetSpeed(200);
	SetMaxHitPoints(2);
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
		if (!started)
		{
			desiredX = std::rand() % width + 1;
			desiredY = std::rand() % height + 1;
			SetRandomX(desiredX);
			SetRandomY(desiredY);

			EnemyStarted();
			AddMoveChange();
		}

		// Run if the enemy hasn't changed it's target location more than 10 times
		if (GetMoveChange() <= 10)
		{
			// Run if the enemy is within 25 pixels of their desired X value
			if (position.X - desiredX >= -25 && position.X - desiredX <= 25)
			{
				desiredX = std::rand() % width + 1;
				SetRandomX(desiredX);
				AddMoveChange();
			}
			// Run if the enemy is within 25 pixels of their desired Y value
			if (position.Y - desiredY >= -25 && position.Y - desiredY <= 25)
			{
				desiredY = std::rand() % height + 1;
				SetRandomY(desiredY);
				AddMoveChange();
			}

			float x = 1;
			float y = 1;

			// Checks if the enemy needs to move left, right, up, or down
			// Move left check
			if (position.X > desiredX)
			{
				x *= GetSpeed() * gameTime.GetElapsedTime() * -1;
			}
			// Move right
			else
			{
				x *= GetSpeed() * gameTime.GetElapsedTime();
			}
			// Move up check
			if (position.Y > desiredY)
			{
				y *= GetSpeed() * gameTime.GetElapsedTime() * -1;
			}
			// Move down
			else
			{
				y *= GetSpeed() * gameTime.GetElapsedTime();
			}

			TranslatePosition(x, y);
		}
		// Makes the enemy move straight down after changing it's target location more than 10 times
		else
		{
			float x = 0;
			TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());
		}

		// Debug Dialog, uncomment if changing movement to see target coordinates.
		//std::cout << "Desired X:" << desiredX << "          " << "Desired Y:" << desiredY << "          " << GetMoveChange() <<"\n";

		// Count debug dialog
		//std::cout << GetCount() << "\n";

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