/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2015 Media Design School 
 
* File Name : GDI_Backbuffer.cpp
* Description : Backbuffer for GDI operations
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz
*/

// This include
#include "GDI_Backbuffer.h"

CBackBuffer::CBackBuffer()						
{
	// Set Initial variables and pointer to 0
	m_hWnd = 0;
	m_hDC = 0;
	m_hSurface = 0;
	m_hOldObject = 0;
	m_iWidth = 0;
	m_iHeight = 0;
}

CBackBuffer::~CBackBuffer()
{
	SelectObject(m_hDC, m_hOldObject);
	DeleteObject(m_hSurface);
	DeleteObject(m_hDC);
}

bool CBackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hWnd = _hWnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	HDC hWindowDC = ::GetDC(m_hWnd);
	m_hDC = CreateCompatibleDC(hWindowDC);
	m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);
	ReleaseDC(m_hWnd, hWindowDC);

	m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));
	HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

	Rectangle(m_hDC, 0, 0, m_iWidth, m_iHeight);
	SelectObject(m_hDC, oldBrush);

	return (true);
}

void CBackBuffer::Clear()
{
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(WHITE_BRUSH)));
	Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());
	SelectObject(GetBFDC(), hOldBrush);
}

HDC CBackBuffer::GetBFDC() const
{
	return (m_hDC);
}

int CBackBuffer::GetWidth() const
{
	return (m_iWidth);
}

int CBackBuffer::GetHeight() const
{
	return (m_iHeight);
}

void CBackBuffer::Present()
{
	HDC hWndDC = ::GetDC(m_hWnd);
	BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hWndDC);
}