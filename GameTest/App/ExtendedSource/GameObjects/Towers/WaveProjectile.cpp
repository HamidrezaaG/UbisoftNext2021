// A basic Monster class.

#include "stdafx.h"
#include "..\..\Scene.h"
#include "WaveProjectile.h"
#include "..\..\Helpers\ResourceManager.h"

WaveProjectile::WaveProjectile(Scene* pScene, Vec2 position, float radius): BaseProjectile(pScene, position, Vec2(0,0))
{
    SetMesh(pScene->GetResourceManager()->GetMesh("Circle"));

    SetPosition(position);
    SetScale(Vec2(0));

    m_MaxRadius = radius;

    SetMainColor(Color(0, 1, 1));
    m_damage = 0.05f;
    m_lifetime = 1;
    m_EllipseRatio = 0.5f;

    m_DamageFrequency = 5.f; // how many times a second do we apply damage?
}

WaveProjectile::~WaveProjectile()
{
}


void WaveProjectile::Update(float deltaTime)
{
    if (m_bDeleted)
        return;

    m_timeSinceSpawn += deltaTime * 0.001f;
    m_DamageTimer += m_DamageFrequency * deltaTime * 0.001f;

    float currentRadius = Math::Interpolate(0, m_MaxRadius, m_timeSinceSpawn / m_lifetime);

    SetScale(Vec2(currentRadius * 0.1f, currentRadius * 0.1f * m_EllipseRatio));

    if (m_DamageTimer > 1)
    {
        for (size_t i = 0; i < m_pScene->GetMonsterList()->size(); i++)
        {
            float distance = m_Position.SimpleEllipseDistance(m_pScene->GetMonsterList()->at(i)->GetPosition(), m_EllipseRatio);

            if (distance * 1.2f < currentRadius)
            {
                OnHitTarget(m_pScene->GetMonsterList()->at(i));
            }
        }
        m_DamageTimer = 0;
    }

    if (m_timeSinceSpawn > m_lifetime)
    {
        OnDestroyProjectile();
    }
}

void WaveProjectile::OnHitTarget(Monster* target)
{
    target->TakeDamage(m_damage, m_MainColor, 0.2f);
    target->SlowDown(0.5f,1.0f);
}
