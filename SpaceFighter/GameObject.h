
#pragma once

#include "KatanaEngine.h"
#include "CollisionType.h"

using namespace KatanaEngine;


class Level;

/** @brief Represents a game object in the game.
	This is the base class for all objects that can be updated, rendered, and checked for collisions. */
class GameObject
{

public:

	/** @brief Instantiate a game object. */
	GameObject();
	virtual ~GameObject() { }

	/** @brief Set the current level.
		@param pLevel A pointer to the current level.
		@remark This is called automatically by the level class when a game object is added to it. */
	static void SetCurrentLevel(Level *pLevel) { s_pCurrentLevel = pLevel; }

	/** @brief Get the current level.
		@return A pointer to the current level. */
	static Level *GetCurrentLevel() { return s_pCurrentLevel; }

	/** @brief Update the object.
		@param gameTime A reference to the game time object. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Render the object.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch) = 0;

	/** @brief Flag to determine if the object is active.
		@return True if the object is active. */
	virtual bool IsActive() const { return m_isActive; }

	/** @brief Activate the object. */
	virtual void Activate() { m_isActive = true; }

	/** @brief Deactivate the object. */
	virtual void Deactivate() { m_isActive = false; }

	/** @brief Get the position of the object.
		@return The position of the object. */
	virtual Vector2 &GetPosition() { return m_position; }

	/** @brief Get the position of the object during the previous frame.
		@return The previous position of the object. */
	virtual Vector2 &GetPreviousPosition() { return m_previousPosition; }

	/** @brief Get the string representation of the object.
		@return The string representation of the object. */
	virtual std::string ToString() const = 0;

	/** @brief Get the half dimensions of the object.
		@return The half dimensions of the object.
		@remark Unless overridden, this will return a Vector2 with both coordinates set to the value of the CollisionRadius.
		@see GetCollisionRadius
	*/
	virtual Vector2 GetHalfDimensions() const;

	/** @brief Get the index of the object.
		Each object is assigned a unique ID when created, starting at 0.
		@return The index of the object. */
	virtual uint32_t GetIndex() const { return m_index; }

	/** @brief Get the collision type of the object.
		@return The collision type of the object. */
	virtual CollisionType GetCollisionType() const = 0;

	/** @brief Get the collision radius of the object.
		@return The collision radius of the object. */
	virtual float GetCollisionRadius() const { return m_collisionRadius; }

	/** @brief Hits the object with a specified amount of damage.
		@param damage The amount of damage to apply. */
	virtual void Hit(const float damage) { }

	/** @brief Check if the object has a specific collision bit-mask.
		@param mask The bit-mask to check.
		@return True if the object has the specified bit-mask. */
	virtual bool HasMask(CollisionType mask) const { return mask.Contains(GetCollisionType()); }

	virtual bool IsMask(CollisionType mask) const { return (GetCollisionType() == mask); }

	virtual bool IsDrawnByLevel() const { return true; }


protected:

	virtual void SetCollisionRadius(const int radius) { m_collisionRadius = radius; }

	virtual void SetPosition(const float x, const float y);

	virtual void SetPosition(const Vector2 &position);

	virtual void TranslatePosition(const float x, const float y);

	virtual void TranslatePosition(const Vector2 &offset);

	virtual bool IsOnScreen() const;


private:
	
	static Level *s_pCurrentLevel;
	static uint32_t s_count;

	uint32_t m_index = 0;

	bool m_isActive = false;

	Vector2 m_position;
	Vector2 m_previousPosition;

	float m_collisionRadius = 0;
};

