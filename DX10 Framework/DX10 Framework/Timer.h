/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Timer.h
* Description : Timer class to track time and delta ticks
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef TIMER_H
#define TIMER_H

class CTimer
{
public:
	CTimer();
	
	// TO DO - revamp timer class
	float GetGameTime()const;
	float GetDeltaTime()const;

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.

private:
	double m_secondsPerCount;
	double m_deltaTime;

	__int64 m_baseTime;
	__int64 m_pausedTime;
	__int64 m_stopTime;
	__int64 m_prevTime;
	__int64 m_currentTime;

	bool m_stopped;
};

#endif	// TIMER_H