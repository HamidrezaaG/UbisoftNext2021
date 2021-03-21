// A basic tower class.

#include "stdafx.h"

#include "Scene.h"

#include "Meshes\AnimatedMesh.h" 
#include "Meshes\Mesh.h" 

#include "Helpers\ResourceManager.h" 

#include "GameObjects\Camera.h"

#include "..\app.h"

#include "GameObjects\GameObject.h"
#include "GameObjects\Monsters\Monster.h"
#include "GameObjects\Monsters\MonsterSquiddle.h"

#include "GameObjects\Towers\Tower.h"

#include "GameObjects\Towers\CubeTower.h"
#include "GameObjects\Towers\TurretTower.h"

#include "Helpers\Spawner.h"

Scene::Scene()
{}

Scene::~Scene()
{}

void Scene::Init()
{

		SetupMonsterWaypoints();
		m_pMonsterList = new std::vector<Monster*>();
		m_pTowerList = new std::vector<Tower*>();

		m_pResourceManager = new ResourceManager();
		m_pResourceManager->LoadMeshes();
		m_SceneAnimatedMeshes = m_pResourceManager->GetAnimatedMeshes(); // We need a list of animated meshes specifically in order to animate them.

		m_pSpawner = new Spawner(this);

	//Make some game objects
	//{

		GameObject* GO_path = new GameObject(this);
		GO_path->SetMesh(m_pResourceManager->GetMesh("ScenePath"));
		GO_path->SetPosition(GetScreenCenter());
		GO_path->SetScale(1);
		GO_path->SetColorA(Color(0, 1, 0));
		m_SceneObjects.push_back(GO_path);

		GameObject* GO_frame = new GameObject(this);
		GO_frame->SetMesh(m_pResourceManager->GetMesh("SceneFrame"));
		GO_frame->SetPosition(GetScreenCenter());
		GO_frame->SetScale(1);
		GO_frame->SetColorA(Color(0, 1, 0));
		m_SceneObjects.push_back(GO_frame);

		TurretTower* GO_turretTower = new TurretTower(this, Vec2(50,100));
		GO_turretTower->SetMesh(m_pResourceManager->GetMesh("TowerTurret"));
		GO_turretTower->SetScale(Vec2(1, 1));
		GO_turretTower->SetColorA(Color(0, 1, 0));
		m_pTowerList->push_back(GO_turretTower);
		m_SceneObjects.push_back(GO_turretTower);

		m_pCursor = new GameObject(this);
		m_pCursor->SetMesh(m_pResourceManager->GetMesh("CursorMesh"));
		m_pCursor->SetScale(Vec2(1, 1));
		m_pCursor->SetColorA(Color(0, 1, 1));
		m_SceneObjects.push_back(m_pCursor);

		m_pCubeTower = new CubeTower(this);
		m_pCubeTower->SetMesh(m_pResourceManager->GetMesh("TowerCube"));
		m_pCubeTower->SetScale(Vec2(40, 40));
		m_pCursor->SetColorA(Color(0, 1, 0));
		m_pTowerList->push_back(m_pCubeTower);
		m_SceneObjects.push_back(m_pCubeTower);

		m_pCamera = new Camera(this);
		m_pCamera->SetPosition(0,0);
		m_SceneObjects.push_back(m_pCamera);

	//}
}

void Scene::Update(float deltaTime)
{
	//m_pCamera->SetRotation(m_pCamera->GetRotation() + deltaTime * 0.02f);

	m_pCursor->SetPosition(GetMousePos());

	if (m_CurrentGameState == GameState::Play)
	{
		m_pSpawner->Update(deltaTime);
	}

	if (m_DeletedObjects.size() > 0)
	{
		ClearRemovedObjectsList();
	}

	for (size_t i = 0; i < m_SceneObjects.size(); i++)
	{
		m_SceneObjects[i]->Update(deltaTime);
	}

	for (size_t i = 0; i < m_SceneAnimatedMeshes->size(); i++)
	{
		m_SceneAnimatedMeshes->at(i)->Animate(deltaTime);
	}

}

Vec2 Scene::GetMousePos()
{
	Vec2 VectorToReturn;
	App::GetMousePos(VectorToReturn.x, VectorToReturn.y);

	if (m_pCamera != nullptr)
	{
		VectorToReturn -= m_pCamera->GetPosition();//VectorToReturn.RotateAround( m_pCamera->GetRotation(), GetScreenCenter() - m_pCamera->GetPosition());
	}

	return VectorToReturn;
}

void Scene::Render()
{
	for (size_t i = 0; i < m_SceneObjects.size(); i++)
	{
		m_SceneObjects[i]->Render();
	}

	App::Print(35 + GetCamera()->GetPosition().x, 665 + GetCamera()->GetPosition().y, ("Cash: " + std::to_string(m_PlayerCash)).c_str(), 1, 255, 1);
}

void Scene::SetupMonsterWaypoints()
{
	Mesh* WaypointsMesh_Left = new Mesh();
	WaypointsMesh_Left->LoadFromOBJ(".\\data\\Waypoints_L.obj");

	Vec2 ScreenCenter = GetScreenCenter();

	for (size_t i = 0; i < WaypointsMesh_Left->GetVerts().size(); i++)
	{
		m_MonsterWaypoints_L.push_back(ScreenCenter + WaypointsMesh_Left->GetVerts()[i]);
	}

	Mesh* WaypointsMesh_Right = new Mesh();
	WaypointsMesh_Right->LoadFromOBJ(".\\data\\Waypoints_R.obj");

	for (size_t i = 0; i < WaypointsMesh_Right->GetVerts().size(); i++)
	{
		m_MonsterWaypoints_R.push_back(ScreenCenter + WaypointsMesh_Right->GetVerts()[i]);
	}

	//m_MonsterWaypoints_L.push_back(Vec2(500, 500));
	//m_MonsterWaypoints_L.push_back(Vec2(400, 400));
	//m_MonsterWaypoints_L.push_back(Vec2(400, 600));
	//m_MonsterWaypoints_L.push_back(Vec2(600, 600));
	//m_MonsterWaypoints_L.push_back(Vec2(600, 400));

	delete WaypointsMesh_Left;
	delete WaypointsMesh_Right;
}

Camera* Scene::GetCamera()
{
	return m_pCamera;
}

void Scene::ShakeCamera()
{
	m_pCamera->ShakeCamera();
}

Vec2 Scene::GetScreenCenter()
{
	return Vec2(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT) * 0.5f;
}

void Scene::OnMonsterReachedEnd(Monster* pMonster)
{
	m_pCamera->ShakeCamera();
	m_pCubeTower->TakeDamage(pMonster->GetDamage());
}

std::vector<Monster*>* Scene::GetMonsterList()
{
	return m_pMonsterList;
}

void Scene::SpawnMonster(Monster::MonsterType type, bool fromRight)
{
	Monster* GO_Monster;

	switch (type)
	{
	case Monster::MonsterType::Squiddle:
		
		GO_Monster = new MonsterSquiddle(this);
		GO_Monster->SetWaypoints(fromRight ? m_MonsterWaypoints_R : m_MonsterWaypoints_L);
		GO_Monster->SetColorA(Color(1, 0, 0));
		m_pMonsterList->push_back(GO_Monster);
		m_SceneObjects.push_back(GO_Monster);
		break;

	case Monster::MonsterType::Tanker:
		break;

	case Monster::MonsterType::Darty:
		break;

	default:
		break;
	}

}

void Scene::DecommissionMonster(Monster* pMonster)
{
	auto it = std::find(m_pMonsterList->begin(), m_pMonsterList->end(), pMonster);
	m_pMonsterList->erase(it);

	if (m_CurrentGameState != GameState::Lose)
	{
		if (m_pMonsterList->size() == 0 && m_pSpawner->GetRemainingMonsterCount() == 0)
		{
			SetGameState(GameState::Win);
		}
	}
}

ResourceManager* Scene::GetResourceManager()
{
	return m_pResourceManager;
}

GameState Scene::GetCurrentGameState()
{
	return m_CurrentGameState;
}

void Scene::SetGameState(GameState state)
{
	m_CurrentGameState = state;
}

void Scene::GrantCash(unsigned int cash)
{
	m_PlayerCash = Math::Clamp(m_PlayerCash + cash, 0, 9999);
}

void Scene::RemoveCash(unsigned int cash)
{
	m_PlayerCash = Math::Clamp(m_PlayerCash - cash, 0, 9999);
}

void Scene::OnMonsterKill(Monster* pMonster)
{
	GrantCash(pMonster->GetRewardValue());
}

void Scene::SpawnGameObject(GameObject* pGameObject)
{
	m_SceneObjects.push_back(pGameObject);
}

void Scene::RemoveGameObject(GameObject* pGameObject)
{
	// We don't have an event system so let's use a list to ensure proper object removal.
	m_DeletedObjects.push_back(pGameObject);
}

void Scene::HandleMouseClick()
{
	if (!m_bPlayerPlacingTower)
	{
		Tower* selectedTower = nullptr;
		for (size_t i = 0; i < m_pTowerList->size(); i++)
		{
			m_pTowerList->at(i)->Deselect();

			//if (m_pTowerList->at(i)->GetPosition().Distance(GetMousePos()) < 100) // circular
			//m_pTowerList->at(i)->GetPosition().Distance()

			if (GetMousePos().SimpleEllipseDistance(m_pTowerList->at(i)->GetPosition(), 0.25f) < 15.f) // circular
			{
				selectedTower = m_pTowerList->at(i); // this will only select the last eligible tower on the list.
			}
		}

		if(selectedTower)
		{
			selectedTower->Select();
		}
	}
}

void Scene::HandleMouseRelease()
{

}

void Scene::ClearRemovedObjectsList()
{
	for (size_t i = 0; i < m_DeletedObjects.size(); i++)
	{
		for (size_t j = 0; j < m_SceneObjects.size(); j++)
		{
			if ( m_DeletedObjects[i] == m_SceneObjects[j] )
			{
				GameObject* pObjectToRemove = m_SceneObjects[j];
				
				auto it = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), pObjectToRemove);
				m_SceneObjects.erase(it);

				delete pObjectToRemove;
				pObjectToRemove = nullptr;

				break;
			}
		}
	}

	(void)m_DeletedObjects.clear();
}

void Scene::Shutdown()
{
	for (size_t i = 0; i < m_SceneObjects.size(); i++)
	{
		delete m_SceneObjects[i];
	}

	delete m_pTowerList;
	delete m_pMonsterList;
	delete m_pResourceManager; // This deletes all loaded meshes as well.
	delete m_pSpawner;
}