
#include <time.h>

#ifndef TIMER_H
#define TIMER_H
class Timer
{
public:
	Timer();
	
	/***********************
	* GetGameTime: Retrieve the Game Time in seconds
	* @author: Callan Moore
	* @return: float: The game time
	********************/
	float GetGameTime()const;
	
	/***********************
	* GetDeltaTime: Retrieve the Delta Time in seconds
	* @author: Callan Moore
	* @return: float: The Delta time
	********************/
	float GetDeltaTime()const; 

	
	/***********************
	* Reset: Reset the Timer
	* @author: Callan Moore
	* @return: void
	********************/
	void Reset();
	
	/***********************
	* Start: Start the Timer
	* @author: Callan Moore
	* @return: void
	********************/
	void Start();
	
	/***********************
	* Stop: Stop the Timer
	* @author: Callan Moore
	* @return: void
	********************/
	void Stop();  // Call when paused.
	
	/***********************
	* Tick: Calculate the Delta tick
	* @author: Callan Moore
	* @return: void
	********************/
	void Tick();  // Call every frame.

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPreviousTime;
	__int64 mCurrentTime;

	bool mStopped;
};

#endif