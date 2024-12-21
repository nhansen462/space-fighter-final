
#include "BossBlaster.h"

void BossBlaster::Update(const GameTime& gameTime)
{
	if (m_cooldown > 0) m_cooldown -= gameTime.GetElapsedTime();
}

void BossBlaster::Fire(TriggerType triggerType)
{
	Vector2 currentPos;

	Projectile* pMiddle = GetProjectile();
	if (!pMiddle) return;
	currentPos = GetPosition();
	pMiddle->Activate(currentPos, false);

	Projectile* pLeft = GetProjectile();
	if (!pLeft) return;
	currentPos.X += 30;
	pLeft->Activate(currentPos, false);

	Projectile* pLefter = GetProjectile();
	if (!pLefter) return;
	currentPos.X += 30;
	pLefter->Activate(currentPos, false);

	currentPos = GetPosition();
	Projectile* pRight = GetProjectile();
	if (!pRight) return;
	currentPos.X -= 30;
	pRight->Activate(currentPos, false);

	Projectile* pRighter = GetProjectile();
	if (!pRighter) return;
	currentPos.X -= 30;
	pRighter->Activate(currentPos, false);

	AudioSample* pAudio = GetFireSound();
	if (pAudio) pAudio->Play();
}