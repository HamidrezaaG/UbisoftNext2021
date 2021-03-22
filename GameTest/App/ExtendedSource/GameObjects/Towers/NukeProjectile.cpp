// A basic Monster class.

#include "stdafx.h"
#include "..\..\Scene.h"
#include "NukeProjectile.h"
#include "..\..\Helpers\ResourceManager.h"

NukeProjectile::NukeProjectile(Scene* pScene, Vec2 position): WaveProjectile(pScene, position, 0)
{
    SetMesh(pScene->GetResourceManager()->GetMesh("Circle"));

    SetPosition(position);
    SetScale(Vec2(0));

    m_MaxRadius = 400;

    SetMainColor(Color(1, 1, 1));
    m_damage = 10.0f;
    m_lifetime = 3;
    m_EllipseRatio = 0.5f;

    m_DamageFrequency = 3.f; // how many times a second do we apply damage?
}

NukeProjectile::~NukeProjectile()
{
}

void NukeProjectile::OnHitTarget(Monster* target)
{
    target->TakeDamage(m_damage, Color(1,1,1), 0.2f);
    target->SlowDown(0.5f,1.0f);
}
