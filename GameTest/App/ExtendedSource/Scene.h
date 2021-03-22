// DESCRIPTION: A class in charge of handling the gamestate, keeping track of who's spawned and despawned, 
// initializing helper classes and buying/selling things.

#ifndef _SCENE_H_
#define _SCENE_H_

#include "GameObjects/Monsters/Monster.h"

class AnimatedMesh;
class GameObject;
class Camera;
class Mesh;
class Tower;

class CubeTower;

class ResourceManager;
class Spawner;
class Button;

#include <vector>
#include "Helpers/SimpleMath.h"

enum class GameState
{
	Pause,
	Play,
	Win,
	Lose
};

class Scene
{
public:
	Scene();
	~Scene();

	void Init();

	void Update(float deltaTime);

	Vec2 GetMousePos();

	void SpawnGameObject(GameObject* pGameObject);

	void RemoveGameObject(GameObject* pGameObject);

	void HandleLMBDown();
	void HandleLMBUp();

	void HandleRMBDown();
	void HandleRMBUp();

	void HandleRMBHeld();

	bool GetCanPlaceTowerAt(Vec2 pos);

	void ClearRemovedObjectsList();

	void Shutdown();

	void Render();

	void SetupMonsterWaypoints();

	Camera* GetCamera();

	void ShakeCamera(float intensity);

	Vec2 GetScreenCenter();

	void OnMonsterReachedEnd(Monster* pMonster);

	std::vector<Monster*>* GetMonsterList();

	void SpawnMonster(Monster::MonsterType type, bool fromRight);

	void DecommissionMonster(Monster* pMonster);

	ResourceManager* GetResourceManager();

	GameState GetCurrentGameState();

	void RestartGame();

	void SetGameState(GameState state);

	void GrantCash(unsigned int cash);
	void RemoveCash(unsigned int cash);
	void IndicateNotEnoughCash();

	void OnMonsterKill(Monster* pMonster);

protected:

	GameState m_CurrentGameState = GameState::Pause;

	ResourceManager* m_pResourceManager;
	Spawner* m_pSpawner;

	Camera* m_pCamera = nullptr;
	GameObject* m_pCursor = nullptr;
	CubeTower* m_pCubeTower = nullptr;

	std::vector<GameObject*> m_SceneObjects;
	std::vector<AnimatedMesh*>* m_SceneAnimatedMeshes;

	std::vector<GameObject*> m_DeletedObjects;

	std::vector<Monster*>* m_pMonsterList;
	std::vector<Tower*>* m_pTowerList;

	std::vector<Vec2> m_MonsterWaypoints_L;
	std::vector<Vec2> m_MonsterWaypoints_R;

	std::vector<Button*> m_Buttons;
	Button* m_pPlayButton;

	Tower* m_pTowerBeingPlaced = nullptr;
	bool m_bPlayerMakingPurchase = false;
	unsigned int m_CostOfPurchase = 0;
	unsigned int m_PlayerStartingCash = 1000;
	unsigned int m_PlayerCash = 0;

	unsigned int m_PriceOfNuke = 1000;
	bool m_bNukeArmed = false;

	float m_notEnoughCashIndicator = 0;
	Color m_PlayerOriginalCashColor = Color(0, 1, 1);
	Color m_PlayerDisplayCashColor = m_PlayerOriginalCashColor;
};

#endif 

