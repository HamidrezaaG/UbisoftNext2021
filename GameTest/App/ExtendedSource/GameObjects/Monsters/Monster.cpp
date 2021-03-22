// A basic Monster class.

#include "stdafx.h"
#include "Monster.h"
#include "..\Camera.h"
#include "..\..\Scene.h"
#include "..\..\Meshes\Mesh.h"

Monster::Monster(Scene* pScene): GameObject(pScene)
{
    m_Position = -200; // position offscreen until waypoints granted.
    m_ragdollVelocity = Vec2(50 * ((float)(rand() % 11) - 5.f), 300.f);
    m_bMove = false;
}

Monster::~Monster()
{
}

void Monster::Update(float deltaTime)
{
    if (m_bDeleted || m_wayPoints.size() == 0)
    {
        return;
    }

    if (m_slowdownTimer > 0)
    {
        m_slowdownTimer -= deltaTime * 0.001f;

        if (m_slowdownTimer <= 0)
        {
            m_speedFactor = 1;
            m_slowdownTimer = 0;
        }
    }

    if (m_DamageColorTimer > 0)
    {
        m_DamageColorTimer -= deltaTime * 0.001f;

        if (m_DamageColorTimer <= 0)
        {
            m_DamageColorTimer = 0;
        }

        m_MainColor = Color::Interpolate(m_AltColor, m_DamageColor, m_DamageColorTimer / m_DamageColorDuration);
    }

    switch (m_currentState)
    {
    case Monster::MonsterState::Alive:

        // A quick fix for cases where a 180 / 360 degree jump occurs. just snap it to the desired rotation.
        if (abs(m_Rotation - m_TargetRotation) > 90.f)
            m_Rotation = m_TargetRotation;

        m_Rotation = Math::Interpolate(m_Rotation, m_TargetRotation, deltaTime * 0.004f);

        if (m_bMove)
        {
            m_Position += m_direction * 0.001f * m_speed * m_speedFactor;

            if (m_Position.DistanceSquared(m_wayPoints[m_NextWaypointIndex]) < 100)
            {
                AtWaypoint();
            }
        }
        break;

    case Monster::MonsterState::Dead:

        m_ragdollVelocity += Vec2(0, -1000) * deltaTime * 0.001f;
        m_Position += m_ragdollVelocity * deltaTime * 0.001f;
        m_Rotation = m_ragdollVelocity.EulerAngle() - 90;

        if (m_Position.y < -100)
        {
            Despawn();
        }

        break;
    default:
        break;
    }
}

Monster::MonsterType Monster::GetType()
{
    return m_monsterType;
}

Monster::MonsterState Monster::GetState()
{
    return m_currentState;
}

void Monster::SetState(MonsterState state)
{
    m_currentState = state;
}

float Monster::GetDamage()
{
    return m_damage;
}

void Monster::AtWaypoint()
{
    m_CurrentWaypointIndex = m_NextWaypointIndex;
    m_NextWaypointIndex++;

    if (m_NextWaypointIndex == m_wayPoints.size())
    {
        m_pScene->OnMonsterReachedEnd(this);
        OnDeath();
    }
    else 
    {
        m_direction = m_Position.DirectionTo(m_wayPoints[m_NextWaypointIndex]);

        if (m_bFollowDirection)
        {
            m_TargetRotation = m_direction.EulerAngle() - 90.f;
        }
    }
}

void Monster::TakeDamage(float damage, Color color)
{
    TakeDamage(damage, color, 1.f);
}

void Monster::TakeDamage(float damage, Color color, float colorChangeDuration)
{
    m_AltColor = m_MainColor;
    m_DamageColor = color;
    m_DamageColorTimer = m_DamageColorDuration = colorChangeDuration;
    TakeDamage(damage);
}

void Monster::SlowDown(float factor, float duration)
{
    m_speedFactor = factor;
    m_slowdownTimer = duration;
}

void Monster::TakeDamage(float damage)
{
    if (m_currentState == MonsterState::Dead)
        return;

    m_health = Math::Max(m_health - damage, 0.0f);

    if (m_health == 0)
    {
        m_pScene->OnMonsterKill(this);
        OnDeath();
    }
}

void Monster::OnDeath()
{
    if (m_currentState == MonsterState::Dead)
        return;

    m_pScene->DecommissionMonster(this);
    SetMainColor(GetMainColor() * 0.7f);
    SetState(Monster::MonsterState::Dead);
}

void Monster::Despawn()
{
    m_bMove = false;
    m_pScene->RemoveGameObject(this);
    m_bDeleted = true;
}

void Monster::SetWaypoints(std::vector<Vec2> waypoints)
{
    m_wayPoints = waypoints;

    if (m_wayPoints.size() > 1)
    {
        m_Position = m_wayPoints[0];
        m_bMove = true;
        m_NextWaypointIndex = 1;
        m_direction = m_Position.DirectionTo(m_wayPoints[m_NextWaypointIndex]);
        m_TargetRotation = m_direction.EulerAngle() - 90;
    }
}

unsigned int Monster::GetRewardValue()
{
    return m_RewardValue;
}

//Vec2 BaseMonster::GetTranslatedPoint(Vec2 inWaypoint)
//{
//    Camera* camera = m_pScene->GetCamera();
//    
//    Vec2 vertToReturn = inWaypoint;
//    float cameraAngleRads = camera->GetRotation() * DEG2RAD;
//    
//    vertToReturn.x = cos(cameraAngleRads) * inWaypoint.x - sin(cameraAngleRads) * inWaypoint.y;
//    vertToReturn.y = sin(cameraAngleRads) * inWaypoint.x + cos(cameraAngleRads) * inWaypoint.y;
//    
//    return (camera->GetPosition() + vertToReturn);
//}