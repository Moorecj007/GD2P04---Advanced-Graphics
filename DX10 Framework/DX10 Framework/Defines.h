/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Defines.h
* Description : Extra functionality
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Defines
#define VALIDATE(a) if (!a) return (false)
#define ReleaseCOM(x) { if (x){ x->Release(); x = 0; } }

