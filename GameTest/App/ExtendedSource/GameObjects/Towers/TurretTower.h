/// DESCRIPTION: A basic tower that fires at the furthest along enemy within its range.

#ifndef _TURRETTOWER_H_
#define _TURRETTOWER_H_


#include "Tower.h"

class TurretTower : public Tower
{
public:

	TurretTower(Scene* pScene, Vec2 position);
	virtual ~TurretTower();

	virtual void Fire() override;
	virtual void Update(float deltaTime) override;

	static unsigned int GetCost() { return 100; };

};

#endif