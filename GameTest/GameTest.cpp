//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "App\Hamidreza\Scene.h"
//------------------------------------------------------------------------
// Data....
//------------------------------------------------------------------------

Scene* SCENE;

bool LMB = false;
//------------------------------------------------------------------------

void Init()
{
	SCENE = new Scene();
	SCENE->Init();
}

void Update(float deltaTime)
{
	if (App::IsKeyPressed(VK_LBUTTON))
	{
		if (!LMB)
		{
			SCENE->HandleMouseClick();
			LMB = true;
		}
		//SCENE->HandleMouseHeld();
	}
	else
	{
		if (LMB)
		{
			SCENE->HandleMouseRelease();
			LMB = false;
		}
	}


	SCENE->Update(deltaTime);
}

void Render()
{	
	SCENE->Render();
}

void Shutdown()
{	
	SCENE->Shutdown();
	delete SCENE;
}