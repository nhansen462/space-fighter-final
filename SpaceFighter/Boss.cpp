
#include "Boss.h"
#include "Level.h"

#include <cstdlib>

Boss::Boss()
{
	SetSpeed(0);
	SetMaxHitPoints(1000);
	SetCollisionRadius(100);
}


void Boss::Update(const GameTime& gameTime)
{
	float random = (Math::GetRandomFloat() - 0.5) * 4;
	int randomNum = rand() % 5 + 1;
	int count = 0;
	if (IsActive())
	{
		if(randomNum == 3)  FireWeapons(TriggerType::Primary);
		if (count > (Math::GetRandomInt(30, 180))) { random *= -1; }
		count++;
		if (!IsOnScreen()) Deactivate();
	}

	EnemyShip::Update(gameTime);
}


void Boss::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
