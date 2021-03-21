/// A class to hold translation data and a mesh

#include "stdafx.h"
#include "GameObject.h"
#include "..\Scene.h"
#include "Camera.h"

Camera::Camera(Scene* pScene) : GameObject(pScene)
{
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
		Vec2 MousePos = m_pScene->GetMousePos();
		Vec2 ScreenCenter = m_pScene->GetScreenCenter();

		m_MouseDelta = (ScreenCenter.x - MousePos.x) / (ScreenCenter.x * 2);
		SetRotation(m_MouseDelta);

		float CameraMovementFactor = Math::Max((m_MovementFactorDeadzone - MousePos.Distance(ScreenCenter)) / m_MovementFactorDeadzone, 0.0f);

		Vec2 target = Vec2::Interpolate(
			-ScreenCenter.DirectionTo(MousePos) * 20.f,
			 0,
			 CameraMovementFactor
		);

		Vec2 current = GetPosition();

		Vec2 origin = current - (current - target) * 0.001f * deltaTime;
		Vec2 shake = Vec2(0);

		if (m_CameraShake_Duration != 0)
		{
			shake = HandleCameraShake(deltaTime);
		}

		SetPosition(origin + shake);

}

Vec2 Camera::HandleCameraShake(float deltaTime)
{
	if (m_CameraShake_Duration > 0)
	{
		m_CameraShake_FrequencyTimer += deltaTime * 0.001f;
		m_CameraShake_Duration -= deltaTime * 0.001f;

		Vec2 cameraShakeToReturn;

		if (m_CameraShake_FrequencyTimer > 1 / m_CameraShake_MaxFrequency)
		{
			m_CameraShake_FrequencyTimer = 0;
			cameraShakeToReturn = Vec2::RandomInUnitCircle() * m_CameraShake_Intensity;
		}

		m_CameraShake_Intensity = m_CameraShake_MaxIntensity * (m_CameraShake_Duration / m_CameraShake_MaxDuration);

		return cameraShakeToReturn;
	}
	else
	{
		m_CameraShake_Duration = 0;
		return Vec2(0);
	}
}

void Camera::ShakeCamera()
{
    m_CameraShake_FrequencyTimer = 0;
    m_CameraShake_Duration = m_CameraShake_MaxDuration;
}
