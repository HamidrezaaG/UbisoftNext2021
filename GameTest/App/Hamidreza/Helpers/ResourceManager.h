// A simple math library for the basics.
// This is absolutely a worthwhile investment for the project.
#ifndef _RESOURCEMAN_H_
#define _RESOURCEMAN_H_

#include <map>
#include "..\Meshes\Mesh.h"
#include "..\Meshes\AnimatedMesh.h"

class Mesh;
class ResourceManager
{
public:

	ResourceManager() {};
	~ResourceManager() 
	{
		for (std::pair<const char*, Mesh*> mesh : m_pMeshes)
		{
			delete mesh.second;
		}

		delete m_pAnimatedMeshes;
	};

	void LoadMeshes()
	{
		m_pAnimatedMeshes = new std::vector<AnimatedMesh*>();

		// Static meshes
		Mesh* mesh_Octagon = new Mesh();
		mesh_Octagon->LoadFromOBJ(".\\data\\Octagon.obj");
		AddMesh("Octagon", mesh_Octagon);

		Mesh* mesh_Triangle = new Mesh();
		mesh_Triangle->LoadFromOBJ(".\\data\\Triangle.obj");
		AddMesh("Triangle", mesh_Triangle);

		Mesh* mesh_SceneFrame = new Mesh();
		mesh_SceneFrame->LoadFromOBJ(".\\data\\Frame.obj");
		AddMesh("SceneFrame", mesh_SceneFrame);

		Mesh* mesh_ScenePath = new Mesh();
		mesh_ScenePath->LoadFromOBJ(".\\data\\Path.obj");
		AddMesh("ScenePath", mesh_ScenePath);


		// Animated meshes
		AnimatedMesh* mesh_MonsterSquid = new AnimatedMesh();
		mesh_MonsterSquid->SetInterpolationStyle(AnimatedMesh::InterpolationStyle::ExponentialInv);
		mesh_MonsterSquid->LoadFramesFromOBJ(".\\Data\\Monster.obj", 2);
		m_pAnimatedMeshes->push_back(mesh_MonsterSquid);
		AddMesh("MonsterSquid", mesh_MonsterSquid);



		AnimatedMesh* mesh_TowerCube = new AnimatedMesh();
		mesh_TowerCube->SetInterpolationStyle(AnimatedMesh::InterpolationStyle::Linear);
		mesh_TowerCube->LoadFramesFromOBJ(".\\Data\\Base.obj", 8);
		mesh_TowerCube->SetFrameRate(1);
		m_pAnimatedMeshes->push_back(mesh_TowerCube);
		AddMesh("TowerCube", mesh_TowerCube);

		AnimatedMesh* mesh_TowerTurret = new AnimatedMesh();
		mesh_TowerTurret->SetInterpolationStyle(AnimatedMesh::InterpolationStyle::SineSmooth);
		mesh_TowerTurret->LoadFramesFromOBJ(".\\Data\\Tower_Turret.obj", 3);
		mesh_TowerTurret->SetHardResetAtEnd(true);
		m_pAnimatedMeshes->push_back(mesh_TowerTurret);
		AddMesh("TowerTurret", mesh_TowerTurret);



		AnimatedMesh* mesh_SelectionCircle = new AnimatedMesh();
		mesh_SelectionCircle->SetFrameRate(1);
		mesh_SelectionCircle->SetInterpolationStyle(AnimatedMesh::InterpolationStyle::SineSmooth);
		mesh_SelectionCircle->LoadFramesFromOBJ(".\\Data\\SelectionCircle.obj", 3);
		mesh_SelectionCircle->SetHardResetAtEnd(true);
		m_pAnimatedMeshes->push_back(mesh_SelectionCircle);
		AddMesh("SelectionCircle", mesh_SelectionCircle);

		AnimatedMesh* mesh_Cursor = new AnimatedMesh();
		mesh_Cursor->SetFrameRate(3);
		mesh_Cursor->SetInterpolationStyle(AnimatedMesh::InterpolationStyle::Linear);
		mesh_Cursor->LoadFramesFromOBJ(".\\Data\\Cursor.obj", 3);
		mesh_Cursor->SetHardResetAtEnd(true);
		m_pAnimatedMeshes->push_back(mesh_Cursor);
		AddMesh("CursorMesh", mesh_Cursor);




	}

	void AddMesh(const char* name, Mesh* mesh) { m_pMeshes[name] = mesh; }
	Mesh* GetMesh(const char* name) { return m_pMeshes[name]; }
	std::vector<AnimatedMesh*>* GetAnimatedMeshes() { return m_pAnimatedMeshes; }

private:

	std::map<const char*, Mesh*> m_pMeshes;
	std::vector<AnimatedMesh*>* m_pAnimatedMeshes;
};

#endif