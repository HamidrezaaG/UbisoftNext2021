/// A class to hold translation data and a mesh

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "GameObject.h"

class Camera : public GameObject
{
public:

	Camera(Scene* pScene);
	virtual ~Camera();

	virtual void Camera::Update(float deltaTime) override;

	void ShakeCamera();

	Vec2 HandleCameraShake(float deltaTime);

protected:

	float m_CameraShake_MaxIntensity = 10;
	float m_CameraShake_MaxDuration = 0.6f;
	float m_CameraShake_MaxFrequency = 60.0f; // locking it on 60 movements a second.
	float m_CameraShake_Intensity = 0.f;
	float m_CameraShake_Duration = 0.f;
	float m_CameraShake_FrequencyTimer = 0.f;

	float m_MouseDelta = 0.0f;
	float m_MovementFactorDeadzone = 500;

};

#endif