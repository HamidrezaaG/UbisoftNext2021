/// A simple wrapper for the provided Line Draw

#include "stdafx.h"
#include "..\..\app.h"

#include "Mesh.h"
#include "..\GameObjects\GameObject.h"
#include <assert.h>

#include "..\Scene.h"
#include "..\GameObjects\Camera.h"
#include "OBJLoader.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::Render(GameObject* parent)
{
    if (m_verts.size() < 2)
        return;

    for (size_t i = 0; i < m_verts.size() - 1; i += 2)
    {
        DrawLine(GetTransformedVert(m_verts[i], parent), GetTransformedVert(m_verts[(i + 1)], parent), parent->GetMeshSegmentColor(static_cast<unsigned int>(i) , static_cast<unsigned int>(m_verts.size())));
    }
}

// This method applies the parent transform to the requested vert.
// Would be better in matrix form.
Vec2 Mesh::GetTransformedVert(Vec2 vert, GameObject* parent)
{
    Camera* camera = parent->GetScene()->GetCamera();

    float parentAngleDeg = parent->GetRotation();
    float cameraAngleDeg = camera->GetRotation();

    Vec2 vertToReturn = vert.Rotate(parentAngleDeg + cameraAngleDeg);
    Vec2 cameraOffset = camera->GetPosition();

    vertToReturn *= parent->GetScale();
    vertToReturn += parent->GetPosition();
    vertToReturn = vertToReturn.RotateAround(cameraAngleDeg, parent->GetPosition() - parent->GetScene()->GetScreenCenter());
    vertToReturn += camera->GetPosition();

    return vertToReturn;
}

void Mesh::DrawLine(Vec2 start, Vec2 end, Color color)
{
    App::DrawLine(start.x, start.y, end.x, end.y, color.r, color.g, color.b);
}

// Getters and setters:
void Mesh::LoadFromOBJ(const char* filepath)
{
    m_verts = OBJLoader::LoadLineOBJ(filepath);
}

void Mesh::MakeCircle(unsigned int sides, float radius)
{
    std::vector<Vec2> verts;

    sides = Math::Max(sides, 3);

    float initAngle = M_PI * 0.5f;
    float anglePerSide = M_PI * 2.f / sides;

    for (size_t i = 0; i < sides; i++)
    {
        verts.push_back(Vec2(initAngle + anglePerSide * i));
    }

    m_verts = verts;
}


std::vector<Vec2> Mesh::GetVerts()
{
    return m_verts;
}

void Mesh::SetVerts(std::vector<Vec2> verts)
{
    m_verts = verts;
}
