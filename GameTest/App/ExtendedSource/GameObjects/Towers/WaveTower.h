/// DESCRIPTION: A tower with slowing capabilities that fires in an ellipse shape.

#ifndef _WAVETOWER_H_
#define _WAVETOWER_H_


#include "Tower.h"

class Monster;

class WaveTower : public Tower
{
public:

	WaveTower(Scene* pScene, Vec2 position);
	virtual ~WaveTower();

	virtual void Fire() override;
	virtual void Update(float deltaTime) override;


	static unsigned int GetCost() { return 300; };

protected:

	virtual Monster* GetFirstMonsterInRange() override;
};

#endif