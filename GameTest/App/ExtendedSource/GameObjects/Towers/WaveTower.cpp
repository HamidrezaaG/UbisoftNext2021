// A basic tower class.

#include "stdafx.h"
#include "WaveTower.h"

#include "..\..\Scene.h"
#include "..\Monsters\Monster.h"
#include "WaveProjectile.h"
#include "..\..\Helpers\ResourceManager.h"

WaveTower::WaveTower(Scene* pScene, Vec2 position): Tower(pScene, position)
{
    SetMesh(pScene->GetResourceManager()->GetMesh("TowerWave"));
    SetScale(Vec2(1, 1));

    m_Range = 200;
    m_TowerHeight = 30.f;
    m_FireRate = 1.f;
    m_pRangeCircle->SetScale(Vec2(m_Range * 0.1f, m_Range * 0.5f * 0.1f));
    m_pExclusionCircle->SetScale(m_ExclusionRange * 0.1f);
}

WaveTower::~WaveTower()
{
}

void WaveTower::Fire()
{
    m_FireTimer = 0;
    WaveProjectile* projectile = new WaveProjectile(m_pScene, m_Position + Vec2(0, m_TowerHeight), m_Range);
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
        if (m_PickedTarget && !m_bBeingPlaced)
        {
            Fire();
        }
    }
}

Monster* WaveTower::GetFirstMonsterInRange()
{
    std::vector<Monster*>* monsterlist = m_pScene->GetMonsterList();
    std::vector<Monster*> listToReturn;

    for (size_t i = 0; i < monsterlist->size(); i++)
    {
        float distance = m_Position.SimpleEllipseDistance(m_pScene->GetMonsterList()->at(i)->GetPosition(), 0.5f);

        if (distance < m_Range)
        {
            return monsterlist->at(i);
        }
    }

    return nullptr;
}
