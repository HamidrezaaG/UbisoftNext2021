// A simple spawner. Has a manifest of spawns to draw from.

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
		if (m_SpawnList.size() == index)
		return;

		m_SpawnTimer += deltaTime * 0.001f;

		if (m_SpawnTimer > m_SpawnList[index].spawnDelay)
		{
			Spawn(m_SpawnList[index]);
			index++;
			m_SpawnTimer = 0;
		}
	}

	unsigned int GetRemainingMonsterCount() { return static_cast<unsigned int>(m_SpawnList.size()); }

	void Restart()
	{
		index = 0;
	}

private:

	Scene* m_pScene = nullptr;
	float m_SpawnTimer = 0;
	unsigned int index;

	std::vector<SpawnData> m_SpawnList =
	{ 
		// spawn one squiddle from the left.
		SpawnData(0.0f, Mtype::Squiddle, false),

		SpawnData(1.0f, Mtype::Squiddle, false),
		SpawnData(1.0f, Mtype::Squiddle, false),

		// spawn from both right and left simultaneously, one second later.
		SpawnData(1.0f, Mtype::Squiddle, true ),
		SpawnData(0.0f, Mtype::Squiddle, false),

		SpawnData(1.0f, Mtype::Squiddle, true),
		SpawnData(0.0f, Mtype::Squiddle, false),

		SpawnData(1.0f, Mtype::Squiddle, true),
		SpawnData(0.0f, Mtype::Squiddle, false),

		SpawnData(1.0f, Mtype::Dasher, true),
		SpawnData(0.0f, Mtype::Dasher, false),

		SpawnData(0.2f, Mtype::Dasher, true),
		SpawnData(0.0f, Mtype::Dasher, false),
		SpawnData(0.2f, Mtype::Dasher, true),
		SpawnData(0.0f, Mtype::Dasher, false),
		SpawnData(0.2f, Mtype::Dasher, true),
		SpawnData(0.0f, Mtype::Dasher, false),
		SpawnData(0.2f, Mtype::Dasher, true),
		SpawnData(0.0f, Mtype::Dasher, false),
		SpawnData(0.2f, Mtype::Dasher, true),
		SpawnData(0.0f, Mtype::Dasher, false),

		SpawnData(1.0f, Mtype::Squiddle, true),
		SpawnData(0.0f, Mtype::Squiddle, false),
		SpawnData(1.0f, Mtype::Squiddle, true),
		SpawnData(0.0f, Mtype::Squiddle, false),
		SpawnData(1.0f, Mtype::Squiddle, true),
		SpawnData(0.0f, Mtype::Squiddle, false),

		SpawnData(1.0f, Mtype::Tanker)

	};

};

#endif