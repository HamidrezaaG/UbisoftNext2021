/// A class to hold translation data and a mesh

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "..\GameObject.h"

#include <vector>

class Scene;

class Monster : public GameObject
{

public:

	enum class MonsterType
	{
		Squiddle,
		Tanker,
		Dasher,
		MAX
	};

	enum class MonsterState
	{
		Alive,
		Dead
	};

	Monster(Scene* pScene);
	virtual ~Monster();

	virtual void Update(float deltaTime) override;

	MonsterType GetType();

	MonsterState GetState();
	void SetState(MonsterState state);

	float GetDamage();

	void TakeDamage(float damage);
	void TakeDamage(float damage, Color color);
	void TakeDamage(float damage, Color color, float colorChangeDuration);

	void OnDeath();

	void Despawn();

	void SetWaypoints(std::vector<Vec2> waypoints);

	void SlowDown(float factor, float duration);

	unsigned int GetRewardValue();

protected:

	void AtWaypoint();


	MonsterType m_monsterType;
	MonsterState m_currentState;

	std::vector<Vec2> m_wayPoints;

	Vec2 m_direction = Vec2(1, 0);

	bool m_bFollowDirection = true;
	bool m_bMove = true;

	float m_speed = 0;
	float m_damage = 0;
	float m_timeSinceSpawn = 0;
	float m_health = 10;
	float m_TargetRotation = 0;

	float m_DamageColorDuration = 0;
	float m_DamageColorTimer = 0;
	Color m_DamageColor;

	unsigned int m_CurrentWaypointIndex = 0;
	unsigned int m_NextWaypointIndex = 0;

	unsigned int m_RewardValue = 0;

	float m_slowdownTimer = 0;
	float m_speedFactor = 1;

	Vec2 m_ragdollVelocity; // ragdoll is an exaggeration.
};

#endif