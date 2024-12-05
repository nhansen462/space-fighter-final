
#pragma once

#include "Ship.h"

/** @brief Represents an enemy ship. */
class EnemyShip : public Ship
{

public:

	/** @brief Creates a new instance of EnemyShip. */
	EnemyShip();
	virtual ~EnemyShip() { }

	/** @brief Loads the content for the enemy ship.
		@param resourceManager A reference to the game's resource manager,
		used for loading and managing game assets (resources). */
	virtual void Update(const GameTime& gameTime);

	/** @brief Draws the enemy ship.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch) = 0;

	/** @brief Initializes the enemy ship.
		@param position The starting position of the enemy ship.
		@param delaySeconds The delay before the enemy ship activates. */
	virtual void Initialize(const Vector2 position, const double delaySeconds);

	/** @brief Fires a weapon from the enemy ship. */
	virtual void Fire() { }

	/** @brief Applies damage to the ship.
		@param damage The amount of damage to apply. */
	virtual void Hit(const float damage);

	/** @brief Gets the string representation of the enemy ship.
		@return Returns the string "Enemy Ship". */
	virtual std::string ToString() const { return "Enemy Ship"; }

	/** @brief Gets the collision type of the enemy ship.
		@return Returns the collision type of the enemy ship. */
	virtual CollisionType GetCollisionType() const { return CollisionType::Enemy | CollisionType::Ship; }

	// Gets the current count of enemies
	static int GetCount() { return s_count; }

	// Increases the count of enemies by 1
	static void AddCount() { s_count++; }

	// Decreases the count of enemies by 1
	static void SubCount() { s_count--; }

	// Does the same thing as GameObject::Deactivate, and decreases the count by 1
	virtual void Deactivate();

protected:

	/** @brief Gets the delay before the enemy ship activates,
		to prevent all enemy ships from activating at the same time.
		@return Returns the delay before the enemy ship activates. */
	virtual double GetDelaySeconds() const { return m_delaySeconds; }


private:

	double m_delaySeconds = 0;

	double m_activationSeconds = 0;

	static int s_count;
};
