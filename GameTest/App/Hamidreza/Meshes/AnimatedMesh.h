/// A simple wrapper for the provided Line Draw

#ifndef _ANIMATEDMESH_H_
#define _ANIMATEDMESH_H_

#include "Mesh.h"
#include <vector>

class AnimatedMesh: public Mesh
{

public:

	enum class InterpolationStyle
	{
		Linear,
		SineSmooth,
		Exponential,
		ExponentialInv
	};

	AnimatedMesh();
	~AnimatedMesh();

	void SetHardResetAtEnd(bool b);

	void AddSingleFrameFromOBJ(const char* filepath);
	void LoadFramesFromOBJ(const char* filepath, unsigned int frameCount);

	void Animate(float deltaTime);

	void SetInterpolationStyle(InterpolationStyle interpolation);

	void SetFrameRate(float framerate);
private:

	InterpolationStyle m_interpolationStyle = InterpolationStyle::Linear;

	bool m_HardResetAtEnd = false;
	float m_framerate = 2;
	float m_framePercentage;
	unsigned int m_currentFrameIndex = 0;
	unsigned int m_nextFrameIndex = 1;

	std::vector<std::vector<Vec2>> m_frames;
};

#endif