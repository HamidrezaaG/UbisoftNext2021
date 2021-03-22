// A basic tower class.

#include "stdafx.h"
#include "CubeTower.h"

#include "..\..\Scene.h"
#include "..\Camera.h"
#include "..\..\Meshes\AnimatedMesh.h"
#include "..\..\..\app.h"

//#include "..\..\app.h"

CubeTower::CubeTower(Scene* pScene): Tower(pScene, pScene->GetScreenCenter())
{
    m_pSelectionCircle->SetScale(Vec2(40, 40));

    m_pExclusionCircle->SetPosition(m_Position);
    m_pSelectionCircle->SetPosition(m_Position);
    m_pRangeCircle->SetPosition(GetPosition());

    m_FireRate = 3.0f;
}

CubeTower::~CubeTower()
{
}

void CubeTower::Render()
{
    Tower::Render();
    
    Color col = GetMainColor();

    Vec2 pos = m_Position;
    pos += m_pScene->GetCamera()->GetPosition();

    App::Print(pos.x - 25, pos.y - 50, ("%" + std::to_string((int)(m_Health * 100 / m_MaxHealth))).c_str(), col.r, col.g, col.b);
}

void CubeTower::Fire()
{
    if (m_FireTimer < 1 / m_FireRate)
        return;

    m_FireTimer = 0;
    BaseProjectile* projectile = new BaseProjectile(m_pScene, m_Position, m_AimDirection);
    m_pScene->SpawnGameObject(projectile);
}

void CubeTower::Update(float deltaTime)
{
    if(m_damageAnimationtimer != 0)
    {
        m_damageAnimationtimer -= deltaTime * 0.001f;

        float interpolationFactor = m_damageAnimationtimer / m_damageAnimationDuration;
        float frameRate = Math::Interpolate(m_animationNormalFramerate, m_animationDamagedFramerate, interpolationFactor);
        SetAltColor(Color::Interpolate(GetMainColor(), GetAltColor(), interpolationFactor));
        AnimateColor(deltaTime);

        if (m_damageAnimationtimer <= 0)
        {
            SetAnimateColor(false);
        }
    }

    if (m_FireTimer < 1 / m_FireRate)
    {
        m_FireTimer += deltaTime * 0.001f;
    }
}

void CubeTower::Reset()
{
    m_Health = m_MaxHealth;
    SetMainColor(Color(0, 1, 0));
    SetAltColor (Color(1, 0, 0));
}

void CubeTower::TakeDamage(float damage)
{
    m_Health = Math::Max(m_Health - damage, 0.0f);

    m_damageAnimationtimer = m_damageAnimationDuration;
    SetAnimateColor(true);

    SetAltColor(Color(1,0,0));
    SetMainColor(Color::Interpolate(Color(1, 0, 0), Color(0, 1, 0), m_Health / m_MaxHealth));
}

bool CubeTower::GetIsAlive()
{
    return m_Health != 0;
}
