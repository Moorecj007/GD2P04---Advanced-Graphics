/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Utilities.h
* Description : Extra functionality for Directx 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

//Inclusion Guards
#pragma once
#ifndef __DX10_UTILITIES_H__
#define __DX10_UTILITIES_H__
#pragma message("Included DX10_Utilities.h")

// Library Includes
#include <d3d10.h>
#include <d3dx10.h>
#include <dxerr.h>

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// Useful Macro for Validating a HRESULT returning 'OK'
#if defined(DEBUG) | defined(_DEBUG)
#ifndef VALIDATEHR
#define VALIDATEHR(x)		                                   \
	{														   \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
			return false;									   \
		}                                                      \
	}
#endif
#else
	#ifndef VALIDATEHR
	#define VALIDATEHR(x) (x)
	#endif
#endif 



#endif // __DX10_UTILITIES_H__