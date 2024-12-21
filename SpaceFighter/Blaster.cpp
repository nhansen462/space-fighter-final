
#include "Blaster.h"

void Blaster::Update(const GameTime & gameTime)
{
	if (m_cooldown > 0) m_cooldown -= gameTime.GetElapsedTime();
}

void Blaster::Fire(TriggerType triggerType)
{
	if (!IsActive()) return;
	if (!CanFire()) return;
	if (!triggerType.Contains(GetTriggerType())) return;

	Projectile* pMiddle = GetProjectile();
	if (!pMiddle) return;
	Vector2 currentPos = GetPosition();
	pMiddle->Activate(currentPos, IsAttachedToPlayer());

	Projectile* pLeft = GetProjectile();
	if (!pLeft) return;
	currentPos.X += 10;
	pLeft->Activate(currentPos, IsAttachedToPlayer());

	Projectile* pRight = GetProjectile();
	if (!pRight) return;
	currentPos.X -= 20;
	pRight->Activate(currentPos, IsAttachedToPlayer());

	AudioSample* pAudio = GetFireSound();
	if (pAudio) pAudio->Play();

	m_cooldown = m_cooldownSeconds;
}