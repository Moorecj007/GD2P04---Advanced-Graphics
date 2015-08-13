/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Camera_Debug.h
* Description : Debug camera for free roam around a scene
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Camera_Debug.h"

CCamera_Debug::CCamera_Debug()
{
}

CCamera_Debug::~CCamera_Debug()
{
}

bool CCamera_Debug::Initialise(CDX10Renderer* _pRenderer, float _speed, float _rotSpeed)
{
	m_pRenderer = _pRenderer;

	m_position = v3float(0.0f, 0.0f, 0.0f);
	m_look = v3float(0.0f, 0.0f, 5.0f);
	m_up = v3float(0.0f, 1.0f, 0.0f);
	m_right = v3float(1.0f, 0.0f, 0.0f);

	m_speed = _speed;
	m_rotationSpeed = _rotSpeed;

	return true;
}

void CCamera_Debug::SetViewMatrix()
{
	m_pRenderer->SetViewMatrix(m_position, m_look, m_up);
}

void CCamera_Debug::MoveInLookDir(float _dir, float _dt)
{
	m_look = m_look.Normalise();
	if (_dir > 0)
	{		
		m_position += m_look * m_speed * _dt;
	}
	else
	{
		m_position -= m_look * m_speed * _dt;
	}
}

void CCamera_Debug::Yaw(float _dir, float _dt)
{
	m_look = m_look.Normalise();
	float yawRot = DegreesToRadians(100) * _dt;
	if (_dir > 0)
	{
		m_look.x = m_look.x * cos(yawRot) - m_look.y * sin(yawRot);
		m_look.y = m_look.y;
		m_look.z = m_look.z * sin(yawRot) + m_look.z * cos(yawRot);
		m_look = m_look.Normalise();
	}
	else
	{
		m_look.x = m_look.x * cos(-yawRot) - m_look.y * sin(-yawRot);
		m_look.y = m_look.y;
		m_look.z = m_look.z * sin(-yawRot) + m_look.z * cos(-yawRot);
		m_look = m_look.Normalise();
	}
}

