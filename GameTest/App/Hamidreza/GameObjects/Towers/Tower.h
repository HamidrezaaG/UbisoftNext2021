/// A class to hold translation data and a mesh

#ifndef _TOWER_H_
#define _TOWER_H_

#include "..\GameObject.h"

#include "BaseProjectile.h"
#include <vector>

class Scene;

class Tower : public GameObject
{
public:

	Tower(Scene* pScene, Vec2 position);

	virtual ~Tower();

	virtual void Fire();

	virtual void Render() override;

	virtual void Select();

	virtual void Deselect();

protected:

	virtual void Aim(Vec2 target);

	Monster* GetFirstMonsterInRange();
	Monster* m_PickedTarget;

	Vec2 m_AimDirection = Vec2(1, 0);
	float m_TowerHeight = 45.f;

	float m_FireRate = 2.f;
	float m_FireTimer = 0;

	float m_Range = 200;

	bool m_bFiring = false;
	bool m_bPlayerPlacingTower = false;;
	bool m_bSelected = false;

	int m_Cost = 100;

	GameObject* m_pExclusionCircle = nullptr;
	GameObject* m_pSelectionCircle = nullptr;
	GameObject* m_pRangeCircle = nullptr;
};

#endif