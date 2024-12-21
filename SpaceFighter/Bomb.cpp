#include "Bomb.h"

void Bomb::Update(const GameTime& gameTime)
{
	if (m_cooldown > 0) m_cooldown -= gameTime.GetElapsedTime();
}

void Bomb::Fire(TriggerType triggerType)
{
	if (!IsActive()) return;
	if (!CanFire()) {
		AudioSample* pRecharging = GetChargingSound();
		if (pRecharging) pRecharging->Play();
		return;
	}
	if (!triggerType.Contains(TriggerType::Secondary)) return;
	Vector2 location;

	for (int y = 900; y > 700; y -= 10) {
		for (int x = 20; x < 1600; x+=20) {
			location.Set(x, y);

			Projectile* pProjectile = GetProjectile();
			if (!pProjectile) return;

			AudioSample* pAudio = GetFireSound();
			if (pAudio) pAudio->Play();

			pProjectile->Activate(location, IsAttachedToPlayer());
		}
	}
	m_cooldown = m_cooldownSeconds;
}