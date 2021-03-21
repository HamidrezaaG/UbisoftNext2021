// A basic Monster class.

#include "stdafx.h"
#include "..\..\Scene.h"
#include "BaseProjectile.h"
#include "..\..\Helpers\ResourceManager.h"

BaseProjectile::BaseProjectile(Scene* pScene, Vec2 position, Vec2 direction): GameObject(pScene)
{
    SetMesh(pScene->GetResourceManager()->GetMesh("Triangle"));
    SetPosition(position);
    SetDirection(direction);

    SetScale(1.0f);
}

BaseProjectile::~BaseProjectile()
{
}

void BaseProjectile::SetDirection(Vec2 direction)
{
    m_direction = direction;
    m_direction = m_direction;
    m_velocity = m_direction * m_speed;
}

void BaseProjectile::Update(float deltaTime)
{
    if (m_bDeleted)
        return;

    m_Position += m_velocity * 0.001f * deltaTime;
    m_Rotation += -deltaTime * 6.0f;
    m_timeSinceSpawn += deltaTime * 0.001f;

    for (size_t i = 0; i < m_pScene->GetMonsterList()->size(); i++)
    {
        if (m_Position.DistanceSquared(m_pScene->GetMonsterList()->at(i)->GetPosition()) < m_projectileRadius * m_projectileRadius)
        {
            OnHitTarget(m_pScene->GetMonsterList()->at(i));
        }
    }

    if (m_timeSinceSpawn > m_lifetime)
    {
        OnDestroyProjectile();
    }
}

void BaseProjectile::OnHitTarget(Monster* target)
{
    target->TakeDamage(m_damage);
    OnDestroyProjectile();
}

void BaseProjectile::OnDestroyProjectile()
{
    m_pScene->RemoveGameObject(this);
    m_bDeleted = true;
}