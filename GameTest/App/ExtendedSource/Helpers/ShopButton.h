// DESCRIPTION: A small class in charge of handling buttons onscreen. it builds on the base class and allows prices to be displayed.

#ifndef _SHOPBUTTON_H_
#define _SHOPBUTTON_H_

#include "Button.h"

class ShopButton: public Button
{
public:

	ShopButton(const char * label, unsigned int price, Vec2 position, Vec2 dimensions, Scene* pScene) : Button(label, position, dimensions, pScene)
	{
		m_DisplayText = label;
		m_DisplayText.append(" - " + std::to_string(price));
	}

	~ShopButton() {};

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
		App::Print(m_Position.x - m_Dimensions.x * 0.5f + CameraPos.x - m_DisplayText.length() * 2, m_Position.y + CameraPos.y - 7, m_DisplayText.c_str(), m_DrawColor.r, m_DrawColor.g, m_DrawColor.b);
	}

private:

	const char* m_Label;
	std::string m_DisplayText;
};

#endif
