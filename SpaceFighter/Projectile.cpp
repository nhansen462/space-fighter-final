
#include "Projectile.h"
#include "Level.h"

Texture *Projectile::s_pTexture = nullptr;

Projectile::Projectile()
{
	SetDirection(-Vector2::UNIT_Y);
	SetCollisionRadius(9);
}

Projectile::Projectile(Vector2 direction)
{
	SetDirection(direction);
	SetCollisionRadius(9);
}

void Projectile::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		Vector2 translation = m_direction * m_speed * gameTime.GetElapsedTime() * (WasShotByPlayer() ? 1 : -1);
		TranslatePosition(translation);

		Vector2 position = GetPosition();
		Vector2 size = s_pTexture->GetSize();

		// Is the projectile off the screen?
		if (position.Y < -size.Y) Deactivate();
		else if (position.X < -size.X) Deactivate();
		else if (position.Y > Game::GetScreenHeight() + size.Y) Deactivate();
		else if (position.X > Game::GetScreenWidth() + size.X) Deactivate();
	}

	GameObject::Update(gameTime);
}

void Projectile::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(s_pTexture, GetPosition(), Color::WHITE * alpha, s_pTexture->GetCenter());
	}
}

void Projectile::Activate(const Vector2 &position, bool wasShotByPlayer)
{
	m_wasShotByPlayer = wasShotByPlayer;
	SetPosition(position);

	GameObject::Activate();
}

std::string Projectile::ToString() const
{
	return std::string((WasShotByPlayer()) ? "Player" : "Enemy").append(" Projectile");
}

CollisionType Projectile::GetCollisionType() const
{
	CollisionType shipType = WasShotByPlayer() ? CollisionType::Player : CollisionType::Enemy;
	return (shipType | GetProjectileType());
}