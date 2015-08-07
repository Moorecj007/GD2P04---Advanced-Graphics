/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Utilities.h
* Description : Extra functionality
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

//Inclusion Guards
#pragma once
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// Defines
#define VALIDATE(a) if (!a) return (false)
#define ReleaseCOM(x) { if (x){ x->Release(); x = 0; } }

#pragma message("Included Utilities.h")

#endif // __UTILITIES_H__

