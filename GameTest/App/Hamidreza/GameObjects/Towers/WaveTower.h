/// A class to hold translation data and a mesh

#ifndef _WAVETURRETTOWER_H_
#define _WAVETURRETTOWER_H_

#include "Tower.h"

#include "BaseProjectile.h"
#include <vector>

class Scene;
class Monster;

class WaveTower : public Tower
{
public:

	WaveTower(Scene* pScene, Vec2 position);
	virtual ~WaveTower();

	virtual void Fire() override;
	virtual void Update(float deltaTime) override;

protected:

};

#endif