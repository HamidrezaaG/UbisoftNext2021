/// A class to hold translation data and a mesh

#ifndef _TURRETTOWER_H_
#define _TURRETTOWER_H_


#include "Tower.h"

#include "BaseProjectile.h"
#include <vector>

class Scene;
class Monster;

class TurretTower : public Tower
{
public:

	TurretTower(Scene* pScene, Vec2 position);
	virtual ~TurretTower();

	virtual void Fire() override;
	virtual void Update(float deltaTime) override;

};

#endif