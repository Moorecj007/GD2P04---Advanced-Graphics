/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DirectInput.h
* Description : Handles mouse input
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "DirectInput.h"

CDirectInput::CDirectInput()
{
	
}

CDirectInput::~CDirectInput()
{
	m_DIMouse->Unacquire();
	m_pDirectInput->Release();
}

bool CDirectInput::Initialise(HINSTANCE hInstance, HWND _hWnd)
{
	DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDirectInput,
		NULL);

	m_pDirectInput->CreateDevice(GUID_SysMouse,
		&m_DIMouse,
		NULL);

	m_DIMouse->SetDataFormat(&c_dfDIMouse);
	m_DIMouse->SetCooperativeLevel(_hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return true;
}

void CDirectInput::DetectMouseInput(float* _yawChange, float* _pitchChange)
{
	DIMOUSESTATE mouseCurrState;
	m_DIMouse->Acquire();
	m_DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

	// Detect the change in mouse state (if any)
	if ((mouseCurrState.lX != m_mousePrevState.lX) || (mouseCurrState.lY != m_mousePrevState.lY))
	{
		*_yawChange += m_mousePrevState.lX;
		*_pitchChange += mouseCurrState.lY;

		m_mousePrevState = mouseCurrState;
	}
}