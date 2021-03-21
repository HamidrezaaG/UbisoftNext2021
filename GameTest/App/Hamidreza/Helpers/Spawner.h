// A simple math library for the basics.
// This is absolutely a worthwhile investment for the project.
#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "..\Scene.h"

#include "..\GameObjects\Monsters\Monster.h"
#include "..\GameObjects\Monsters\MonsterSquiddle.h"

#define Mtype Monster::MonsterType 

// Easier to tell the spawner what to spawn and when.
struct SpawnData
{
	// to specify every detail.
	SpawnData(float delay, Mtype type, bool right): monsterType(type), spawnDelay(delay), fromRight(right){}
	
	// to pick the direction randomly
	SpawnData(float delay, Mtype type) : monsterType(type), spawnDelay(delay) { fromRight = rand() % 2; } 

	// to pick the type and direction randomly
	SpawnData(float delay) : spawnDelay(delay) 
	{ 
		monsterType = static_cast<Mtype>(rand() % (int)Mtype::MAX);
		fromRight = rand() % 2; 
	}

	float spawnDelay = 0.0f;
	Mtype monsterType = Mtype::Squiddle; // default to squids.
	bool fromRight = false;
};

class Spawner
{
public:

	Spawner(Scene* pScene) : m_pScene(pScene) {};
	~Spawner() {};

	void Spawn(SpawnData spawnData)
	{
		m_pScene->SpawnMonster(spawnData.monsterType, spawnData.fromRight);
	}

	void Update(float deltaTime)
	{
		if (m_SpawnList.size() == 0)
		return;

		m_SpawnTimer += deltaTime * 0.001f;

		if (m_SpawnTimer > m_SpawnList[0].spawnDelay)
		{
			Spawn(m_SpawnList[0]);
			m_SpawnList.erase(m_SpawnList.begin());
			m_SpawnTimer = 0;
		}
	}

	unsigned int GetRemainingMonsterCount() { return static_cast<unsigned int>(m_SpawnList.size()); }

private:

	Scene* m_pScene = nullptr;
	float m_SpawnTimer = 0;

	std::vector<SpawnData> Stage1 = 
	{ 
		SpawnData(0.0f, Mtype::Squiddle),
		SpawnData(1.0f, Mtype::Squiddle),
		SpawnData(2.0f, Mtype::Squiddle),
		SpawnData(3.0f, Mtype::Squiddle),
		SpawnData(4.0f, Mtype::Squiddle),
		SpawnData(5.0f, Mtype::Squiddle),
		SpawnData(6.0f, Mtype::Squiddle),
		SpawnData(7.0f, Mtype::Squiddle)
	};

	std::vector<SpawnData> Stage2 =
	{
		SpawnData(0.0f, Mtype::Squiddle),
		SpawnData(1.0f, Mtype::Squiddle),
		SpawnData(2.0f, Mtype::Squiddle),
		SpawnData(3.0f, Mtype::Squiddle),
		SpawnData(4.0f, Mtype::Squiddle),
		SpawnData(5.0f, Mtype::Squiddle),
		SpawnData(6.0f, Mtype::Squiddle),
		SpawnData(7.0f, Mtype::Squiddle)
	};

	std::vector<SpawnData> Stage3 =
	{
		SpawnData(0.0f, Mtype::Squiddle),
		SpawnData(1.0f, Mtype::Squiddle),
		SpawnData(2.0f, Mtype::Squiddle),
		SpawnData(3.0f, Mtype::Squiddle),
		SpawnData(4.0f, Mtype::Squiddle),
		SpawnData(5.0f, Mtype::Squiddle),
		SpawnData(6.0f, Mtype::Squiddle),
		SpawnData(7.0f, Mtype::Squiddle)
	};

	std::vector<SpawnData> m_SpawnList = Stage1;
};

#endif