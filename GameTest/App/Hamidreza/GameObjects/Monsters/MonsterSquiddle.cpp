// A basic MonsterSquiddle class.

#include "stdafx.h"
#include "MonsterSquiddle.h"

#include "..\..\Scene.h"
#include "..\..\Helpers\ResourceManager.h"

MonsterSquiddle::MonsterSquiddle(Scene* pScene): Monster(pScene)
{
    m_monsterType = MonsterType::Squiddle;

    SetMesh(pScene->GetResourceManager()->GetMesh("MonsterSquid"));

    m_Scale = Vec2(20, 20);

    m_speed = 1000;
    m_damage = 1;
    m_health = 10;

    m_RewardValue = 100;

}

MonsterSquiddle::~MonsterSquiddle()
{
}
