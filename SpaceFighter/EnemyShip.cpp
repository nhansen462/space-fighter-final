
#include "EnemyShip.h"

int EnemyShip::s_count = 0;

EnemyShip::EnemyShip()
{
	SetMaxHitPoints(1);
	SetCollisionRadius(20);
	AddCount();
}

void EnemyShip::Deactivate()
{
	GameObject::Deactivate();
	SubCount();
}

void EnemyShip::Update(const GameTime& gameTime)
{
	if (m_delaySeconds > 0)
	{
		m_delaySeconds -= gameTime.GetElapsedTime();

		if (m_delaySeconds <= 0)
		{
			GameObject::Activate();
		}
	}

	if (IsActive())
	{
		m_activationSeconds += gameTime.GetElapsedTime();
		if (m_activationSeconds > 2 && !IsOnScreen()) { 
			Deactivate(); 
		};
	}

	Ship::Update(gameTime);
}


void EnemyShip::Initialize(const Vector2 position, const double delaySeconds)
{
	SetPosition(position);
	m_delaySeconds = delaySeconds;

	Ship::Initialize();
}


void EnemyShip::Hit(const float damage)
{
	Ship::Hit(damage);
	if (GetHP() <= 0) SubCount();
}