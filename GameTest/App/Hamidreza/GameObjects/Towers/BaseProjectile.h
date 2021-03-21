/// A class to hold translation data and a mesh

#ifndef _BASEPROJECTILE_H_
#define _BASEPROJECTILE_H_

#include "..\GameObject.h"

class BaseProjectile : public GameObject
{
public:

	BaseProjectile(Scene* pScene, Vec2 position, Vec2 direction);
	virtual ~BaseProjectile();

	void SetDirection(Vec2 direction);
	virtual void Update(float deltaTime) override;

	void OnHitTarget(Monster* target);

	void OnDestroyProjectile();

protected:

	Vec2 m_direction = Vec2(1, 0);
	Vec2 m_velocity;

	float m_speed = 600;
	float m_projectileRadius = 20;
	float m_damage = 1;
	float m_lifetime = 0.5f;
	float m_timeSinceSpawn = 0; 

};

#endif
