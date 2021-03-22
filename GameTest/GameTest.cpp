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
#include "App\ExtendedSource\Scene.h"
//------------------------------------------------------------------------
// Data....
//------------------------------------------------------------------------

Scene* SCENE;

bool LMB = false;
bool RMB = false;

void ProcessMouseInput();
//------------------------------------------------------------------------

void Init()
{
	SCENE = new Scene();
	SCENE->Init();
}

void Update(float deltaTime)
{
	ProcessMouseInput();
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

void ProcessMouseInput()
{
	if (App::IsKeyPressed(VK_LBUTTON))
	{
		if (!LMB)
		{
			SCENE->HandleLMBDown();
			LMB = true;
		}
		// Handle LMB Held;
	}
	else
	{
		if (LMB)
		{
			SCENE->HandleLMBUp();
			LMB = false;
		}
	}

	if (App::IsKeyPressed(VK_RBUTTON))
	{
		if (!RMB)
		{
			SCENE->HandleRMBDown();
			RMB = true;
		}
		SCENE->HandleRMBHeld();
	}
	else
	{
		if (RMB)
		{
			SCENE->HandleRMBUp();
			RMB = false;
		}
	}
};