// A basic tower class.

#include "stdafx.h"
#include "Tower.h"

#include "..\..\Scene.h"
#include "..\Monsters\Monster.h"
#include "..\..\Helpers\ResourceManager.h"

Tower::Tower(Scene* pScene, Vec2 position): GameObject(pScene, position)
{
    m_pExclusionCircle = new GameObject(pScene);
    m_pSelectionCircle = new GameObject(pScene);
    m_pRangeCircle     = new GameObject(pScene);

    m_pExclusionCircle->SetPosition(m_Position);
    m_pSelectionCircle->SetPosition(m_Position);

    m_pSelectionCircle->SetScale(Vec2(40,10));

    m_pRangeCircle->SetPosition(GetPosition());

    Mesh* circlemesh = pScene->GetResourceManager()->GetMesh("SelectionCircle");

    m_pExclusionCircle->SetMesh(circlemesh);
    m_pSelectionCircle->SetMesh(circlemesh);
    m_pRangeCircle->SetMesh(circlemesh);
}

Tower::~Tower()
{
    delete m_pExclusionCircle;
    delete m_pSelectionCircle;
    delete m_pRangeCircle;
}

void Tower::Fire()
{
    m_FireTimer = 0;
    BaseProjectile* projectile = new BaseProjectile(m_pScene, m_Position, m_AimDirection);
    m_pScene->SpawnGameObject(projectile);
}

void Tower::Render()
{
    GameObject::Render();

    if (m_bSelected)
    {
        m_pSelectionCircle->Render();
        m_pRangeCircle->Render();
    }
    else if(m_bPlayerPlacingTower)
    {
        m_pExclusionCircle->Render();
        m_pRangeCircle->Render();
    }
}

void Tower::Select()
{
    m_bSelected = true;
}

void Tower::Deselect()
{
    m_bSelected = false;
}

void Tower::Aim(Vec2 target)
{
    m_AimDirection = (m_Position + Vec2(0, m_TowerHeight)).DirectionTo(target);
}

Monster* Tower::GetFirstMonsterInRange()
{
    std::vector<Monster*>* monsterlist = m_pScene->GetMonsterList();
    std::vector<Monster*> listToReturn;

    for (size_t i = 0; i < monsterlist->size(); i++)
    {
        if (m_Position.DistanceSquared(monsterlist->at(i)->GetPosition()) < m_Range * m_Range)
        {
            return monsterlist->at(i);
        }
    }

    return nullptr;
}
