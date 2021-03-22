/// DESCRIPTION: Base class for all towers.
// it allows selection, placement, and basic functionality like rendering

#ifndef _TOWER_H_
#define _TOWER_H_

#include "..\GameObject.h"

#include <vector>

class Scene;
class Monster;

class Tower : public GameObject
{
public:

	Tower(Scene* pScene, Vec2 position);

	virtual ~Tower();

	virtual void Fire() = 0;

	void PlaceTower();

	virtual void Render() override;

	virtual void Select();

	virtual void Deselect();

	void ShowExclusionZone(bool b);

	float GetExclusionRange();

	void SetPlacementColor(Color c);

	Color GetMeshSegmentColor(unsigned int index, unsigned int vertCount) override;

	virtual void Aim(Vec2 target);

	bool GetIsSelected();

protected:


	bool m_bBeingPlaced = true;
	bool m_bShowExclusionZone = false;

	virtual Monster* GetFirstMonsterInRange();
	Monster* m_PickedTarget;

	Vec2 m_AimDirection = Vec2(1, 0);
	float m_TowerHeight = 45.f;

	float m_FireRate = 2.f;
	float m_FireTimer = 0;

	float m_Range = 200;
	float m_ExclusionRange = 100;

	bool m_bFiring = false;
	bool m_bSelected = false;

	GameObject* m_pExclusionCircle = nullptr;
	GameObject* m_pSelectionCircle = nullptr;
	GameObject* m_pRangeCircle = nullptr;

	Color m_ColorAfterPlacement = m_MainColor; // store color A so we can re-use it after placement
	Color m_PlacementColor;
};

#endif