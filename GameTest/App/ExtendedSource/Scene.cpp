
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
#include "GameObjects\Monsters\MonsterTanker.h"
#include "GameObjects\Monsters\MonsterDasher.h"

#include "GameObjects\Towers\Tower.h"
#include "GameObjects\Towers\NukeProjectile.h"

#include "GameObjects\Towers\CubeTower.h"
#include "GameObjects\Towers\TurretTower.h"
#include "GameObjects\Towers\WaveTower.h"

#include "Helpers\Spawner.h"
#include "Helpers\Button.h"
#include "Helpers\ShopButton.h"


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

		ShopButton* Button_TurretTower = new ShopButton("Turret", TurretTower::GetCost(), Vec2(500, 500), Vec2(70, 20), this);
		m_Buttons.push_back(Button_TurretTower);

		ShopButton* Button_WaveTower = new ShopButton("Wave", WaveTower::GetCost(), Vec2(500, 550), Vec2(70, 20), this);
		m_Buttons.push_back(Button_WaveTower);

		ShopButton* Button_Nuke = new ShopButton("Nuke", m_PriceOfNuke, Vec2(500, 600), Vec2(70, 20), this);
		m_Buttons.push_back(Button_Nuke);

		m_pPlayButton = new Button("Play", GetScreenCenter() + Vec2(0, -200), Vec2(40, 20), this);
		m_pPlayButton->Hide(false);
		m_Buttons.push_back(m_pPlayButton);

	//Make some game objects
	//{

		GameObject* GO_path = new GameObject(this);
		GO_path->SetMesh(m_pResourceManager->GetMesh("ScenePath"));
		GO_path->SetPosition(GetScreenCenter());
		GO_path->SetScale(1);
		GO_path->SetMainColor(Color(0, 1, 0));
		m_SceneObjects.push_back(GO_path);

		GameObject* GO_frame = new GameObject(this);
		GO_frame->SetMesh(m_pResourceManager->GetMesh("SceneFrame"));
		GO_frame->SetPosition(GetScreenCenter());
		GO_frame->SetScale(1);
		GO_frame->SetMainColor(Color(0, 1, 0));
		m_SceneObjects.push_back(GO_frame);

		m_pCursor = new GameObject(this);
		m_pCursor->SetMesh(m_pResourceManager->GetMesh("CursorMesh"));
		m_pCursor->SetScale(Vec2(1, 1));
		m_pCursor->SetMainColor(Color(0, 1, 1));
		m_SceneObjects.push_back(m_pCursor);

		m_pCubeTower = new CubeTower(this);
		m_pCubeTower->SetMesh(m_pResourceManager->GetMesh("TowerCube"));
		m_pCubeTower->SetScale(Vec2(40, 40));
		m_pCursor->SetMainColor(Color(0, 1, 0));
		m_pTowerList->push_back(m_pCubeTower);
		m_SceneObjects.push_back(m_pCubeTower);

		m_pCamera = new Camera(this);
		m_pCamera->SetPosition(0,0);
		m_SceneObjects.push_back(m_pCamera);

	//}
}

void Scene::Update(float deltaTime)
{
	m_pCursor->SetPosition(GetMousePos());

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
	if (m_pTowerBeingPlaced)
	{
		m_pTowerBeingPlaced->SetPosition(GetMousePos());
		m_pTowerBeingPlaced->SetPlacementColor(GetCanPlaceTowerAt(GetMousePos()) ? m_pTowerBeingPlaced->GetMainColor() * 0.7f : m_pTowerBeingPlaced->GetMainColor() + Color(0.6f, -1, 0));
	}
	if (m_notEnoughCashIndicator > 0)
	{
		m_notEnoughCashIndicator -= deltaTime * 0.001f;

		if (m_notEnoughCashIndicator <= 0)
		{
			m_PlayerDisplayCashColor = m_PlayerOriginalCashColor;
			m_notEnoughCashIndicator = 0;
		}

		m_PlayerDisplayCashColor = Color::Interpolate(m_PlayerOriginalCashColor, Color(1, 0, 0), m_notEnoughCashIndicator);
	}

	switch (m_CurrentGameState)
	{
		case GameState::Pause:
			break;
		case GameState::Play:
			m_pSpawner->Update(deltaTime);
			break;
		case GameState::Win:
			break;
		case GameState::Lose:
			break;

		default:
			break;
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

	for (size_t i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->Render();
	}

	App::Print(100 + GetCamera()->GetPosition().x, 665 + GetCamera()->GetPosition().y, ("Cash: " + std::to_string(m_PlayerCash)).c_str(), m_PlayerDisplayCashColor.r, m_PlayerDisplayCashColor.g, m_PlayerDisplayCashColor.b);

	if (m_CurrentGameState == GameState::Win)
	{
		App::Print(GetScreenCenter().x - 40, 200 + GetScreenCenter().y, "You Won!", 0, 1, 1);
	}
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

	delete WaypointsMesh_Left;
	delete WaypointsMesh_Right;
}

Camera* Scene::GetCamera()
{
	return m_pCamera;
}

void Scene::ShakeCamera(float intensity)
{
	m_pCamera->ShakeCamera(intensity);
}

Vec2 Scene::GetScreenCenter()
{
	return Vec2(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT) * 0.5f;
}

void Scene::OnMonsterReachedEnd(Monster* pMonster)
{
	m_pCamera->ShakeCamera(10);
	m_pCubeTower->TakeDamage(pMonster->GetDamage());

	if (!m_pCubeTower->GetIsAlive())
	{
		SetGameState(GameState::Lose);
	}
}

std::vector<Monster*>* Scene::GetMonsterList()
{
	return m_pMonsterList;
}

void Scene::SpawnMonster(Monster::MonsterType type, bool fromRight)
{
	Monster* GO_Monster = nullptr;

	switch (type)
	{
	case Monster::MonsterType::Squiddle:
		
		GO_Monster = new MonsterSquiddle(this);
		break;

	case Monster::MonsterType::Tanker:

		GO_Monster = new MonsterTanker(this);
		break;

	case Monster::MonsterType::Dasher:

		GO_Monster = new MonsterDasher(this);
		break;

	default:
		break;
	}

	if (GO_Monster)
	{
		GO_Monster->SetWaypoints(fromRight ? m_MonsterWaypoints_R : m_MonsterWaypoints_L);
		m_pMonsterList->push_back(GO_Monster);
		m_SceneObjects.push_back(GO_Monster);
	}

}

void Scene::DecommissionMonster(Monster* pMonster)
{

	for (size_t i = 0; i < m_pMonsterList->size(); i++)
	{
		if (pMonster == m_pMonsterList->at(i))
		{
			m_pMonsterList->erase(m_pMonsterList->begin() + i);
		}
	}

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

void Scene::RestartGame()
{
	m_PlayerCash = m_PlayerStartingCash;
	m_pCubeTower->Reset();
	m_pSpawner->Restart();


	for (size_t i = 0; i < m_pTowerList->size(); i++)
	{
		if (m_pTowerList->at(i) != m_pCubeTower)
			RemoveGameObject(m_pTowerList->at(i));
	}

	m_pTowerList->clear();
	m_pTowerList->push_back(m_pCubeTower);

}

void Scene::SetGameState(GameState state)
{
	if (m_CurrentGameState == state)
		return;

	switch (state)
	{

	case GameState::Pause:
		break;

	case GameState::Play:
		RestartGame();

		break;

	case GameState::Win:

		// drop any tower we may be placing.
		HandleRMBDown();
		m_pPlayButton->Hide(false);

			break;

	case GameState::Lose:

		// drop any tower we may be placing.
		HandleRMBDown();

		for (size_t i = 0; i < m_SceneObjects.size(); i++)
		{
			Monster* mptr = dynamic_cast<Monster*>(m_SceneObjects.at(i));
			if(mptr)
				mptr->OnDeath();
		}

		for (size_t i = 0; i < m_Buttons.size(); i++)
		{
			m_Buttons[i]->Hide(true);
		}

		m_pPlayButton->Hide(false);

			break;

		default:
			break;
	}

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

void Scene::HandleLMBDown()
{

	if (m_bPlayerMakingPurchase)
	{
		return;
	}

	for (size_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i]->CheckIsHovered())
		{
			m_Buttons[i]->OnPress();
		}
	}

	Tower* selectedTower = nullptr;
	for (size_t i = 0; i < m_pTowerList->size(); i++)
	{
		m_pTowerList->at(i)->Deselect();

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

void Scene::HandleLMBUp()
{
	if (m_bNukeArmed)
	{
		NukeProjectile* nuke = new NukeProjectile(this, GetMousePos());
		SpawnGameObject(nuke);
		RemoveCash(m_CostOfPurchase);
		m_bNukeArmed = false;
	}

	for (size_t i = 0; i < m_Buttons.size(); i++)
	{
		if (m_Buttons[i]->CheckIsHovered())
		{
			m_Buttons[i]->OnRelease();
		}
	}

	if (!m_bPlayerMakingPurchase)
	{
		Button* pressedButton = nullptr;

		for (size_t i = 0; i < m_Buttons.size(); i++)
		{
			if (m_Buttons[i]->CheckIsHovered())
			{
				pressedButton = m_Buttons[i];
				break;
			}
		}

		if (pressedButton)
		{
			// Play button
			const char* ButtonLabel = pressedButton->GetLabel();

			if (ButtonLabel == "Play")
			{
				SetGameState(GameState::Play);

				for (size_t i = 0; i < m_Buttons.size(); i++)
				{
					m_Buttons.at(i)->Hide(false);
				}

				pressedButton->Hide(true);
				return;
			}

			// Shop stuff
			Tower* pTowerToPlace = nullptr;
			bool MakingPurchase = false;

			if (ButtonLabel == "Turret" && m_PlayerCash >= TurretTower::GetCost())
			{
				m_CostOfPurchase = TurretTower::GetCost();
				pTowerToPlace = new TurretTower(this, GetMousePos());
				MakingPurchase = true;
			}
			else if (ButtonLabel == "Wave" && m_PlayerCash >= WaveTower::GetCost())
			{
				m_CostOfPurchase = WaveTower::GetCost();
				pTowerToPlace = new WaveTower(this, GetMousePos());
				MakingPurchase = true;
			}
			else if (ButtonLabel == "Nuke" && m_PlayerCash >= m_PriceOfNuke)
			{
				m_CostOfPurchase = m_PriceOfNuke;
				MakingPurchase = true;
			}

			// purchase successful!
			if (MakingPurchase)
			{
				if (pTowerToPlace)
				{
					m_bPlayerMakingPurchase = true;
					m_SceneObjects.push_back(pTowerToPlace);
					m_pTowerBeingPlaced = pTowerToPlace;

					for (size_t i = 0; i < m_pTowerList->size(); i++)
					{
						m_pTowerList->at(i)->ShowExclusionZone(true);
					}
				}
				else 
				{
					m_bNukeArmed = true;
				}
			}
			else
			{
				IndicateNotEnoughCash();
			}
		}
	}
	else // handle tower dropoff
	{
		if (GetCanPlaceTowerAt(GetMousePos()))
		{
			m_pTowerBeingPlaced->PlaceTower();

			for (size_t i = 0; i < m_pTowerList->size(); i++)
			{
				m_pTowerList->at(i)->ShowExclusionZone(false);
			}

			m_pTowerList->push_back(m_pTowerBeingPlaced);
			RemoveCash(m_CostOfPurchase);
			m_pTowerBeingPlaced = nullptr;
			m_bPlayerMakingPurchase = false;

			ShakeCamera(1);
		}
	}
}

void Scene::HandleRMBDown()
{
	// Cancel purchase
	if (m_bPlayerMakingPurchase)
	{
		for (size_t i = 0; i < m_pTowerList->size(); i++)
		{
			m_pTowerList->at(i)->ShowExclusionZone(false);
		}
		RemoveGameObject(m_pTowerBeingPlaced);
		m_bPlayerMakingPurchase = false;
	}
}

void Scene::HandleRMBUp()
{
}

void Scene::HandleRMBHeld()
{
	if (m_pCubeTower->GetIsSelected() && m_pCubeTower->GetIsAlive())
	{
		m_pCubeTower->Aim(GetMousePos());
		m_pCubeTower->Fire();
	}
}

bool Scene::GetCanPlaceTowerAt(Vec2 pos)
{

	for (size_t i = 0; i < m_MonsterWaypoints_L.size(); i++)
	{
		if (pos.Distance(m_MonsterWaypoints_L.at(i)) < 60)
		{
			return false;
		}
	}

	for (size_t i = 0; i < m_Buttons.size(); i++)
	{
		if(m_Buttons[i]->CheckIsHovered())
		return false;
	}

	for (size_t i = 0; i < m_MonsterWaypoints_R.size(); i++)
	{
		if (pos.Distance(m_MonsterWaypoints_R.at(i)) < 40)
		{
			return false;
		}
	}

	for (size_t i = 0; i < m_pTowerList->size(); i++)
	{
		if (pos.Distance(m_pTowerList->at(i)->GetPosition()) < m_pTowerList->at(i)->GetExclusionRange())
		{
			return false;
		}
	}

	return true;
}

void Scene::IndicateNotEnoughCash()
{
	m_notEnoughCashIndicator = 1.0f;
	m_PlayerDisplayCashColor = Color(1, 0, 0);
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

	for (size_t i = 0; i < m_Buttons.size(); i++)
	{
		delete m_Buttons[i];
	}

	delete m_pTowerList;
	delete m_pMonsterList;
	delete m_pResourceManager; // This deletes all loaded meshes as well.
	delete m_pSpawner;
}