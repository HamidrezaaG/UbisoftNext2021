/// DESCRIPTION: A type of projectile that expands outwards int an ellipse shape and deals damage periodically to everyone in range.

#ifndef _WAVEPROJECTILE_H_
#define _WAVEPROJECTILE_H_

#include "BaseProjectile.h"

class WaveProjectile : public BaseProjectile
{
public:

	WaveProjectile(Scene* pScene, Vec2 position, float radius);
	virtual ~WaveProjectile();

	virtual void Update(float deltaTime) override;

	virtual void WaveProjectile::OnHitTarget(Monster* target) override;

protected:
	
	float m_MaxRadius;
	float m_EllipseRatio;
	float m_DamageFrequency; 
	float m_DamageTimer = 0;
};

#endif
