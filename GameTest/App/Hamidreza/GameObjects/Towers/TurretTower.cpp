// A basic tower class.

#include "stdafx.h"
#include "TurretTower.h"

#include "..\..\Scene.h"
#include "..\Monsters\Monster.h"
//#include "..\..\app.h"

TurretTower::TurretTower(Scene* pScene, Vec2 position): Tower(pScene, position)
{
    m_Cost = 100;
    m_TowerHeight = 45.f;
}

TurretTower::~TurretTower()
{
}

void TurretTower::Fire()
{
    m_FireTimer = 0;
    BaseProjectile* projectile = new BaseProjectile(m_pScene, m_Position + Vec2(0, m_TowerHeight), m_AimDirection);
    m_pScene->SpawnGameObject(projectile);
}

void TurretTower::Update(float deltaTime)
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
