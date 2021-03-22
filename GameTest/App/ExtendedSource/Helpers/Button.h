// DESCRIPTION: A small class in charge of handling buttons onscreen.
// The label of the button is used to determine functionality.

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "..\..\app.h"
#include "..\Scene.h"
#include "..\GameObjects\GameObject.h"
#include "..\GameObjects\Camera.h"
#include "..\Meshes\Mesh.h"

#include <vector>

class Button: public GameObject
{
public:

	Button(const char * label, Vec2 position, Vec2 dimensions, Scene* pScene) : GameObject(pScene), m_Dimensions(dimensions)
	{
		m_Label = label;

		m_pMesh = new Mesh();
		m_OriginalPosition = m_Position = position;
		m_Scale = 1;

		// Simple rectangle
		std::vector<Vec2> verts =
		{
				Vec2(-m_Dimensions.x , m_Dimensions.y) ,	   m_Dimensions						,
					  m_Dimensions					   , Vec2( m_Dimensions.x, -m_Dimensions.y) ,
				Vec2( m_Dimensions.x , -m_Dimensions.y),	  -m_Dimensions						,
					 -m_Dimensions					   , Vec2(-m_Dimensions.x,	m_Dimensions.y)
		};

		m_AltColor = Color(0, 1, 0);
		m_MainColor = Color(0, 1, 1);

		m_pMesh->SetVerts(verts);
	}

	~Button() { delete m_pMesh; };

	virtual void Render() override
	{
		if (m_bHidden)
			return;

		if (CheckIsHovered())
		{
			OnHover();
		}
		else
		{
			OnRelease();
		}

		m_pMesh->Render(this);
		Vec2 CameraPos = m_pScene->GetCamera()->GetPosition();

		App::Print(m_Position.x - m_Dimensions.x * 0.5f + CameraPos.x - std::strlen(m_Label) * 2.5f, m_Position.y + CameraPos.y - 7, m_Label, m_DrawColor.r, m_DrawColor.g, m_DrawColor.b);
	}

	bool CheckIsHovered()
	{
		if (m_bHidden)
			return false;

		Vec2 MousePos = m_pScene->GetMousePos();
		return (MousePos.x < m_Position.x + m_Dimensions.x && MousePos.x > m_Position.x - m_Dimensions.x) &&
			   (MousePos.y < m_Position.y + m_Dimensions.y && MousePos.y > m_Position.y - m_Dimensions.y);
	}

	virtual Color GetMeshSegmentColor(unsigned int index, unsigned int vertCount) override
	{
		return m_DrawColor;
	}

	void OnHover()
	{
		m_DrawColor = m_AltColor;
	}

	void OnPress()
	{
		m_Position = m_OriginalPosition - Vec2(0, 4);
	}

	void OnRelease()
	{
		m_DrawColor = m_MainColor;
		m_Position = m_OriginalPosition;
	}

	const char * GetLabel()
	{
		return m_Label;
	}

	void Hide(bool b)
	{
		m_bHidden = b;
	}

protected:

	Vec2 m_Dimensions;
	Vec2 m_OriginalPosition;

	const char* m_Label;

	Color m_DrawColor;
	bool m_bHidden = true;
};

#endif