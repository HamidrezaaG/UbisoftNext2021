// A basic tower class.

#include "stdafx.h"
#include "TurretTower.h"

#include "..\..\Scene.h"

#include "BaseProjectile.h"
#include "..\..\Helpers\ResourceManager.h"

TurretTower::TurretTower(Scene* pScene, Vec2 position): Tower(pScene, position)
{
    SetMesh(pScene->GetResourceManager()->GetMesh("TowerTurret"));
    SetScale(Vec2(1, 1));

    m_Range = 250;
    m_TowerHeight = 60.f;
    m_pRangeCircle->SetScale(m_Range * 0.1f);
    m_pExclusionCircle->SetScale(m_ExclusionRange * 0.1f);
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
        if (m_PickedTarget && !m_bBeingPlaced)
        {
            Aim(m_PickedTarget->GetPosition());
            Fire();
        }
    }
}
