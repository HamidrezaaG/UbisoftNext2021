/// DESCRIPTION: A player-deployed projectile that expands outwards int a large ellipse shape and deals significant damage periodically to everyone in range.

#ifndef _NukeProjectile_H_
#define _NukeProjectile_H_

#include "WaveProjectile.h"

class NukeProjectile : public WaveProjectile
{
public:

	NukeProjectile(Scene* pScene, Vec2 position);
	virtual ~NukeProjectile();
	virtual void NukeProjectile::OnHitTarget(Monster* target) override;

};

#endif
