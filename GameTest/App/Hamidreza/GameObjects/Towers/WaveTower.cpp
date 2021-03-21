// A basic tower class.

#include "stdafx.h"
#include "WaveTower.h"
#include "..\..\Scene.h"

WaveTower::WaveTower(Scene* pScene, Vec2 position): Tower(pScene, position)
{

}

WaveTower::~WaveTower()
{

}

void WaveTower::Fire()
{
    m_FireTimer = 0;
    BaseProjectile* projectile = new BaseProjectile(m_pScene, m_Position + Vec2(0, m_TowerHeight), m_AimDirection);
    m_pScene->SpawnGameObject(projectile);
}

void WaveTower::Update(float deltaTime)
{
    m_PickedTarget = GetFirstMonsterInRange();

    if (m_FireTimer < 1 / m_FireRate)
    {
        m_FireTimer += deltaTime * 0.001f;
    }
    else
    {
        if (m_PickedTarget)
        {
            Aim(m_PickedTarget->GetPosition());
            Fire();
        }
    }
}
