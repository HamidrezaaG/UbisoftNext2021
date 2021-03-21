/// A class to hold and control a level
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

#include <vector>
#include "Helpers/SimpleMath.h"

enum class GameState
{
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

	void HandleMouseClick();

	void HandleMouseRelease();

	void ClearRemovedObjectsList();

	void Shutdown();

	void Render();

	void SetupMonsterWaypoints();

	Camera* GetCamera();

	void ShakeCamera();

	Vec2 GetScreenCenter();

	void OnMonsterReachedEnd(Monster* pMonster);

	std::vector<Monster*>* GetMonsterList();

	void SpawnMonster(Monster::MonsterType type, bool fromRight);

	void DecommissionMonster(Monster* pMonster);

	ResourceManager* GetResourceManager();

	GameState GetCurrentGameState();
	void SetGameState(GameState state);

	void GrantCash(unsigned int cash);
	void RemoveCash(unsigned int cash);

	void OnMonsterKill(Monster* pMonster);

protected:

	GameState m_CurrentGameState = GameState::Play;


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

	bool m_bPlayerPlacingTower = false;
	unsigned int m_PlayerCash = 300;

};

#endif 
