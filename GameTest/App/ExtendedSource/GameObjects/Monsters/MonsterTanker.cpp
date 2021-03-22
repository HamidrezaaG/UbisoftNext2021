// A basic MonsterSquiddle class.

#include "stdafx.h"
#include "MonsterTanker.h"

#include "..\..\Scene.h"
#include "..\..\Helpers\ResourceManager.h"

MonsterTanker::MonsterTanker(Scene* pScene): Monster(pScene)
{
    m_monsterType = MonsterType::Tanker;
    
    SetMesh(pScene->GetResourceManager()->GetMesh("MonsterTanker"));

    SetMainColor(Color(0.6f, 0.3f, 0.3f));
    SetAltColor(GetMainColor());

    m_Scale = Vec2(20, 20);

    m_speed = 500;
    m_damage = 3;
    m_health = 40;

    m_RewardValue = 100;

}

MonsterTanker::~MonsterTanker()
{
}
