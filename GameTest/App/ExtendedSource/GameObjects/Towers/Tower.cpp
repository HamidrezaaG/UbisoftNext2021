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

    m_pExclusionCircle->SetPosition(GetPosition());
    m_pSelectionCircle->SetPosition(GetPosition());
    m_pRangeCircle->SetPosition(GetPosition());

    m_pExclusionCircle->SetPosition(GetPosition());
    m_pSelectionCircle->SetPosition(GetPosition());
    m_pRangeCircle->SetPosition(GetPosition());

    m_pSelectionCircle->SetScale(Vec2(40,10));

    Mesh* dashedCircleMesh = pScene->GetResourceManager()->GetMesh("SelectionCircle");
    Mesh* circleMesh = pScene->GetResourceManager()->GetMesh("Circle");

    m_pExclusionCircle->SetMesh(circleMesh);
    m_pSelectionCircle->SetMesh(dashedCircleMesh);
    m_pRangeCircle->SetMesh(circleMesh);

    m_pExclusionCircle->SetMainColor(Color(0.3f, 0, 0));
    m_pRangeCircle->SetMainColor(Color(0, 0.8f, 0.8f));

    if (m_bBeingPlaced)
    {
        m_PlacementColor = m_MainColor * 0.8f; // dimmer until we place the tower.
    }
}



Tower::~Tower()
{
    delete m_pExclusionCircle;
    delete m_pSelectionCircle;
    delete m_pRangeCircle;
}

void Tower::PlaceTower()
{
    m_pExclusionCircle->SetPosition(GetPosition());
    m_pSelectionCircle->SetPosition(GetPosition());
    m_pRangeCircle->SetPosition(GetPosition());
    m_MainColor = m_ColorAfterPlacement;
    m_bBeingPlaced = false;
}

void Tower::Render()
{
    GameObject::Render();

    if (m_bSelected)
    {
        m_pSelectionCircle->Render();
        m_pRangeCircle->Render();
    }

    if (m_bShowExclusionZone)
    {
        m_pExclusionCircle->Render();
    }
}


Color Tower::GetMeshSegmentColor(unsigned int index, unsigned int vertCount)
{
    if (m_bBeingPlaced)
    {
        return m_PlacementColor;
    }
    else
    {
        return m_MainColor;
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

void Tower::ShowExclusionZone(bool b)
{
    m_bShowExclusionZone = b;
}

float Tower::GetExclusionRange()
{
    return m_ExclusionRange;
}

void Tower::SetPlacementColor(Color c)
{
    m_PlacementColor = c;
}

void Tower::Aim(Vec2 target)
{
    m_AimDirection = (m_Position + Vec2(0, m_TowerHeight)).DirectionTo(target);
}

bool Tower::GetIsSelected()
{
    return m_bSelected;
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
