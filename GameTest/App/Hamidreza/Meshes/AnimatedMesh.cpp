/// A simple wrapper for the provided Line Draw

#include "stdafx.h"
#include <assert.h>

#include "AnimatedMesh.h"
#include "OBJLoader.h"
#include <string>

AnimatedMesh::AnimatedMesh()
{
}

AnimatedMesh::~AnimatedMesh()
{
}

void AnimatedMesh::SetHardResetAtEnd(bool b)
{
	m_HardResetAtEnd = b;
}

void AnimatedMesh::AddSingleFrameFromOBJ(const char* filepath)
{
	std::vector<Vec2> frame = OBJLoader::LoadLineOBJ(filepath);

	// Ensure the new frame has the same # of vertices. if it's the first frame, adopt the new frame's vert count.
	if (m_frames.size() > 0)
	{
		assert(frame.size() == m_verts.size());
	}

	if (m_frames.size() == 0)
	{
		m_verts = frame;
	}

	m_frames.push_back(frame);
}

void AnimatedMesh::LoadFramesFromOBJ(const char* filepath, unsigned int frameCount)
{
	for (size_t i = 0; i < frameCount; i++)
	{
		std::string newfilepath = filepath;

		// insert frame number after filename.
		newfilepath.insert(newfilepath.length() - 4, "_" + std::to_string(i+1)); 

		AddSingleFrameFromOBJ(newfilepath.c_str());
	}
}

void AnimatedMesh::Animate(float deltaTime)
{
	if (m_frames.size() < 2)
		return;

	m_framePercentage += deltaTime * 0.001f * m_framerate;
	
	if (m_framePercentage >= 1)
	{

		m_currentFrameIndex = m_nextFrameIndex;
		m_nextFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
		
		if (m_HardResetAtEnd && m_currentFrameIndex == m_frames.size() - 1)
		{
			for (size_t i = 0; i < m_verts.size(); i++)
			{
				m_verts[i] = m_frames[0][i];
			}

			m_currentFrameIndex = 0;
			m_nextFrameIndex = 1;
		}

		m_framePercentage = 0;
	}

	float interpolationFactor = 0;

	switch (m_interpolationStyle)
	{
		case InterpolationStyle::Linear:
			interpolationFactor = m_framePercentage;
			break;

		case InterpolationStyle::SineSmooth:
			interpolationFactor = (1 + (float)sin(M_PI * (m_framePercentage - 0.5f))) * 0.5f;
			break;

		case InterpolationStyle::Exponential:
			interpolationFactor = pow(m_framePercentage, 3.0f);
			break;

		case InterpolationStyle::ExponentialInv:
			interpolationFactor = pow(m_framePercentage, 0.333f);
			break;
	}

	for (size_t i = 0; i < m_verts.size(); i++)
	{
		m_verts[i] = Vec2::Interpolate(m_frames[m_currentFrameIndex][i], m_frames[m_nextFrameIndex][i], interpolationFactor);
	}
}

void AnimatedMesh::SetInterpolationStyle(InterpolationStyle interpolationStyle)
{
	m_interpolationStyle = interpolationStyle;
}

void AnimatedMesh::SetFrameRate(float framerate)
{
	m_framerate = framerate;
}
