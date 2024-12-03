
#pragma once

#include "EnemyShip.h"
#include "Game.h"

/** @brief Represents an enemy ship that is biological in nature. */
class EvasiveEnemyShip : public EnemyShip
{

public:

	/** @brief Creates a new instance of BioEnemyShip. */
	EvasiveEnemyShip();
	virtual ~EvasiveEnemyShip() { }

	/** @brief Sets the texture that will be used to render the enemy ship.
		@param pTexture A pointer to the texture. */
	virtual void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	/** @brief Updates the enemy ship.
		@param gameTime A reference to the game time object. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Draws the enemy ship.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch);

	// Sets the m_targetX variable
	virtual void SetRandomX(int targetX) { m_targetX = targetX; };

	// Gets the m_targetX variable
	virtual int GetRandomX() { return m_targetX; }

	// Sets the m_targetY variable
	virtual void SetRandomY(int targetY) { m_targetY = targetY; };

	// Gets the m_targetY variable
	virtual int GetRandomY() { return m_targetY; }

	// Changes the m_started variable to show that the enemy has started
	virtual void EnemyStarted() { m_started = true; }

	// Gets whether the enemy has started or not
	virtual bool GetStarted() { return m_started; }

	// Gets how many times the enemy has changed their target location
	virtual int GetMoveChange() { return m_moveChange; }

	// Adds one to the moveChange variable
	virtual void AddMoveChange() { m_moveChange++; }

private:

	Texture* m_pTexture = nullptr;

	int m_targetX = 0;
	int m_targetY = 0;
	bool m_started = false;
	int m_moveChange = 0;

};