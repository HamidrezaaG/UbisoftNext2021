/// A simple wrapper for the provided Line Draw

#ifndef _MESH_H_
#define _MESH_H_

#include "..\Helpers\SimpleMath.h"

class GameObject;

class Mesh
{
public:

	Mesh();
	virtual ~Mesh();

	virtual void Render(GameObject* parent);

	void DrawLine(Vec2 start, Vec2 end, Color color);
	Vec2 GetTransformedVert(Vec2 vert, GameObject* parent);

	void LoadFromOBJ(const char* filepath);
	void MakeCircle(unsigned int sides, float radius);

	std::vector<Vec2> GetVerts();

	void Mesh::SetVerts(std::vector<Vec2> verts);


protected:

	Color GetColor(unsigned int index, GameObject* parent);
	std::vector<Vec2> m_verts;
};

#endif