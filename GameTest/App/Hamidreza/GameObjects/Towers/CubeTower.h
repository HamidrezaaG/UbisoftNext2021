/// A class to hold translation data and a mesh

#ifndef _CUBETOWER_H_
#define _CUBETOWER_H_

#include "Tower.h"

#include "BaseProjectile.h"
#include <vector>

class Scene;

class CubeTower : public Tower
{
public:
	CubeTower(Scene* pScene);
	virtual ~CubeTower();

	virtual void Render() override;
	virtual void Fire() override;
	virtual void Update(float deltaTime) override;

	void TakeDamage(float damage);

protected:

	float m_MaxHealth = 5.f;
	float m_Health = m_MaxHealth;

	float m_damageAnimationDuration = 2.f;
	float m_damageAnimationtimer = 0;
	float m_animationNormalFramerate = 4;
	float m_animationDamagedFramerate = 8;
};

#endif
