/// A class to hold translation data and a mesh

#include "stdafx.h"
#include "GameObject.h"
#include "..\Meshes\Mesh.h"

GameObject::GameObject(Scene* pScene)
{
    m_pScene = pScene;
}

GameObject::GameObject(Scene* pScene, Vec2 position)
{
    m_pScene = pScene;
    m_Position = position;
}

GameObject::~GameObject()
{
}

void GameObject::Render()
{
    if(m_pMesh)
    {
        m_pMesh->Render(this);
    }
}

Mesh* GameObject::GetMesh()
{
    return m_pMesh;
}

void GameObject::SetMesh(Mesh* mesh)
{
    m_pMesh = mesh;
}

Scene* GameObject::GetScene()
{
    return m_pScene;
}

void GameObject::SetScene(Scene* scene)
{
    m_pScene = scene;
}

Vec2 GameObject::GetScale()
{
    return m_Scale;
}

Vec2 GameObject::GetPosition()
{
    return m_Position;
}

float GameObject::GetRotation()
{
    return m_Rotation;
}

void GameObject::SetScale(Vec2 scale)
{
    m_Scale = scale;
}

void GameObject::SetPosition(float x, float y)
{
    m_Position = Vec2(x,y);
}

void GameObject::SetPosition(Vec2 position)
{
    m_Position = position;
}

void GameObject::SetRotation(float rotation)
{
    m_Rotation = rotation;
}

void GameObject::AnimateColor(float deltaTime)
{
    m_colorAnimationFactor += deltaTime * 0.001f * 60.f;
}

void GameObject::SetAnimateColor(bool b)
{
    m_bAnimateColor = b;
}

void GameObject::SetMainColor(Color color)
{
    m_MainColor = color;
}

void GameObject::SetAltColor(Color color)
{
    m_MainColor;
}

Color GameObject::GetAltColor()
{
    return m_AltColor;
}

Color GameObject::GetMainColor()
{
    return m_MainColor;
}

Color GameObject::GetMeshSegmentColor(unsigned int index, unsigned int vertCount)
{
    if (!m_bAnimateColor)
    {
        return m_MainColor;
    }

    // Calculate a factor based on how deep into the mesh indices we are.
    float factor = (float)((index + (int)m_colorAnimationFactor) % vertCount) / vertCount;

    // Use that factor to interpolate the color of the segment being drawn.
    return Color::Interpolate(m_MainColor, m_AltColor, factor);
}
