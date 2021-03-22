

#include "stdafx.h"
#include "MonsterSquiddle.h"

#include "..\..\Scene.h"
#include "..\..\Helpers\ResourceManager.h"

MonsterSquiddle::MonsterSquiddle(Scene* pScene): Monster(pScene)
{

    m_monsterType = MonsterType::Squiddle;

    SetMesh(pScene->GetResourceManager()->GetMesh("MonsterSquiddle"));

    SetMainColor(Color(1, 0, 0));
    SetAltColor(GetMainColor());

    m_Scale = Vec2(20, 20);

    m_speed = 1000;
    m_damage = 2;
    m_health = 10;

    m_RewardValue = 50;

}

MonsterSquiddle::~MonsterSquiddle()
{
}
