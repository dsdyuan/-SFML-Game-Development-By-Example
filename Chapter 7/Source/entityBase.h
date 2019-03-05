#pragma once

#include <string>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


enum class EntityType { Base, Enemy, Player };
enum class EntityState { Idle, Walking, Jumping, Attacking, Hurt, Dying };

struct TileInfo;

struct CollisionElement
{
	CollisionElement(float l_area, TileInfo* l_info, const sf::FloatRect& l_bounds)
		: m_area(l_area), m_tile(l_info), m_tileBounds(l_bounds)
	{
	}

	float m_area;
	TileInfo* m_tile;
	sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;

inline bool SortCollisions(const CollisionElement& l_one, const CollisionElement& l_two)
{
	return l_one.m_area > l_two.m_area;
}

class EntityManager;

class EntityBase
{
	friend class EntityManager;

public:
	EntityBase(EntityManager* l_entityMgr);
	virtual ~EntityBase();

	const sf::Vector2f& GetPosition()const;
	const sf::Vector2f& GetSize()const;
	EntityState GetState()const;
	std::string GetName()const;
	unsigned int GetID()const;
	EntityType GetType()const;

	void SetPosition(float l_x, float l_y);
	void SetPosition(const sf::Vector2f& l_pos);
	void SetSize(float l_x, float l_y);
	void SetState(const EntityState& l_state);

	void Move(float l_x, float l_y);
	void AddVelocity(float l_x, float l_y);
	void Accelerate(float l_x, float l_y);
	void SetAcceleration(float l_x, float l_y);
	void ApplyFriction(float l_x, float l_y);

	virtual void Update(float l_dT);
	virtual void Draw(sf::RenderWindow* l_wind) = 0;

protected:
	void UpdateAABB();
	void CheckCollisions();
	void ResolveCollisions();

	virtual void OnEntityCollision(EntityBase* l_collider, bool l_attack) = 0;

	std::string m_name;
	
	sf::Vector2f m_position;		// current position 
	sf::Vector2f m_positionOld;		// position before entity moved
	sf::Vector2f m_velocity;		// current velocity
	sf::Vector2f m_maxVelocity;		// maximum velocity
	sf::Vector2f m_speed;			// value of acceleration
	sf::Vector2f m_acceleration;	// current acceleration
	sf::Vector2f m_friction;		// default friction value
	sf::Vector2f m_size;			// size of the collision box

	sf::FloatRect m_AABB;			// the bounding box for collisions

	TileInfo* m_referenceTile;		// tile underneath entity
	EntityState m_state;			// current entity state
	EntityType m_type;
	Collisions m_collisions;
	EntityManager* m_entityManager;

	unsigned int m_ID;				// entity ID for the entity manager
	bool m_collidingOnX;
	bool m_collidingOnY;
};
