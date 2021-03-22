// A basic MonsterSquiddle class.

#include "stdafx.h"
#include "MonsterDasher.h"

#include "..\..\Scene.h"
#include "..\..\Helpers\ResourceManager.h"

MonsterDasher::MonsterDasher(Scene* pScene): Monster(pScene)
{
    m_monsterType = MonsterType::Dasher;

    SetMesh(pScene->GetResourceManager()->GetMesh("MonsterDasher"));
    SetMainColor(Color(0.8f, 0.3f, 0.0f));
    SetAltColor(GetMainColor());

    m_Scale = Vec2(20, 20);

    m_speed = 2000;
    m_damage = 1;
    m_health = 2;

    m_RewardValue = 10;

}

MonsterDasher::~MonsterDasher()
{
}
