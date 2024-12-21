
#include "BioEnemyShip.h"
#include "Level.h"


BioEnemyShip::BioEnemyShip()
{
	SetSpeed(150);
	SetMaxHitPoints(3);
	SetCollisionRadius(20);
}


void BioEnemyShip::Update(const GameTime& gameTime)
{
	float rand = (Math::GetRandomFloat() - 0.5) * 4;
	int count = 0;
	if (IsActive())
	{
		float x = sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
		x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f + rand;
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());
		if (count > (Math::GetRandomInt(30, 180))) { rand *= -1; }
		count++;
		if (!IsOnScreen()) Deactivate();
	}

	EnemyShip::Update(gameTime);
}


void BioEnemyShip::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
