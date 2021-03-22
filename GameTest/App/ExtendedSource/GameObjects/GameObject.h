/// DESCRIPTION: A class to hold translation data and a mesh

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "..\Helpers\SimpleMath.h"

class Mesh;
class Scene;

class GameObject
{
public:

	GameObject(Scene* pScene);
	GameObject(Scene* pScene, Vec2 position);
	virtual ~GameObject();

	virtual void Render();

	Mesh* GetMesh();
	void SetMesh(Mesh* mesh);

	Scene* GetScene();
	void SetScene(Scene* scene);

	Vec2  GetScale();
	Vec2  GetPosition();
	float GetRotation();

	void SetScale(Vec2 scale);

	void SetPosition(float x, float y);
	void SetPosition(Vec2 position);

	void SetRotation(float rotation);

	virtual void Update(float deltaTime) {};

	virtual Color GetMeshSegmentColor(unsigned int index, unsigned int vertCount);
	
	Color GetMainColor();
	Color GetAltColor();

	void SetMainColor(Color color);
	void SetAltColor(Color color);

	void AnimateColor(float deltaTime);
	void SetAnimateColor(bool b);

protected:

	Mesh* m_pMesh;

	Vec2 m_Scale = 100;
	Vec2 m_Position = Vec2(500,500);
	float m_Rotation = 0;

	Scene* m_pScene;

	bool m_bDeleted = false;

	Color m_MainColor = Color(0, 1, 0);
	Color m_AltColor = Color(1, 0, 0);

	bool m_bAnimateColor = false;
	float m_colorAnimationFactor;
};

#endif