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

// Inclusion Guards
#pragma once
#ifndef __CAMERA_DEBUG_H__
#define __CAMERA_DEBUG_H__

// Local Includes
#include "DX10Renderer.h"

class CCamera_Debug
{
public:

	/***********************
	* CCamera_Debug: Default Constructor for Debug Camera class
	* @author: Callan Moore
	********************/
	CCamera_Debug();

	/***********************
	* ~CCamera_Debug: Default Destructor for Debug Camera class
	* @author: Callan Moore
	********************/
	~CCamera_Debug();

	/***********************
	* Initialise: Initialise the Debug Camera
	* @author: Callan Moore
	* @Parameter: _pRenderer: Renderer for the Application
	* @Parameter: _speed: Initial speed of the Camera
	* @Parameter: _rotSpeed: Initial rotation speed of the camera
	* @return: bool: Successful or not
	********************/
	bool Initialise(CDX10Renderer* _pRenderer, float _speed, float _rotSpeed);

	/***********************
	* SetViewMatrix: Create and set the view matrix on the renderer
	* @author: Callan Moore
	* @Parameter: _pRenderer: Renderer for the Application
	* @return: bool: Successful or not
	********************/
	void SetViewMatrix();

	/***********************
	* MoveInLookDir: Move along the look axis
	* @author: Callan Moore
	* @Parameter: _dir: Positive or negative direction to move in
	* @Parameter: _dt: The current Delta Tick
	* @return: void
	********************/
	void MoveInLookDir(float _dir, float _dt);

	/***********************
	* Yaw: Rotate on the Y axis
	* @author: Callan Moore
	* @Parameter: _dir: Positive or negative direction to rotate in
	* @Parameter: _dt: The current Delta Tick
	* @return: void
	********************/
	void Yaw(float _dir, float _dt);

	/***********************
	* Pitch: Rotate on the X axis
	* @author: Callan Moore
	* @Parameter: _dir: Positive or negative direction to rotate in
	* @Parameter: _dt: The current Delta Tick
	* @return: void
	********************/
	void Pitch(float _dir, float _dt);

	// Strafe?
	// Roll?

	/***********************
	* GetPosition: Retrieve the position vector
	* @author: Callan Moore
	* @return: v3float: The Position vector
	********************/
	v3float GetPosition() const { return m_position; }

	/***********************
	* SetPosition: Set the Look vector
	* @author: Callan Moore
	* @parameter: _pos: The new position vector
	* @return: void
	********************/
	void SetPosition(v3float _pos) { m_position = _pos; }

	/***********************
	* GetLook: Retrieve the Look vector
	* @author: Callan Moore
	* @return: v3float: The Look vector
	********************/
	v3float GetLook() const { return m_look; }

	/***********************
	* SetLook: Set the Look vector
	* @author: Callan Moore
	* @parameter: _look: The new look vector
	* @return: void
	********************/
	void SetLook(v3float _look) { m_look = _look; }

	/***********************
	* GetUp: Retrieve the Up vector
	* @author: Callan Moore
	* @return: v3float: The Up vector
	********************/
	v3float GetUp() const { return m_up; }

	/***********************
	* SetUp: Set the Up vector
	* @author: Callan Moore
	* @parameter: _up: The new up vector
	* @return: void
	********************/
	void SetUp(v3float _up) { m_up = _up; }

	/***********************
	* GetRight: Retrieve the Right vector
	* @author: Callan Moore
	* @return: v3float: The Right vector
	********************/
	v3float GetRight() const { return m_right; }

	/***********************
	* SetRight: Set the Right vector
	* @author: Callan Moore
	* @parameter: _right: The new right vector
	* @return: void
	********************/
	void SetRight(v3float _right) { m_right = _right; }

	/***********************
	* GetSpeed: Retrieve the movement speed
	* @author: Callan Moore
	* @return: float: Movement speed of the Camera
	********************/
	float GetSpeed() const { return m_speed; }

	/***********************
	* SetSpeed: Set the movement speed
	* @author: Callan Moore
	* @parameter: _speed: The new movement speed
	* @return: void
	********************/
	void SetSpeed(float _speed) { m_speed = _speed; }

	/***********************
	* GetRotationSpeed: Retrieve the rotation speed
	* @author: Callan Moore
	* @return: float: Rotation speed of the Camera
	********************/
	float GetRotationSpeed() const { return m_rotationSpeed; }

	/***********************
	* SetRotationSpeed: Set the rotation speed
	* @author: Callan Moore
	* @parameter: _rot: The new rotation speed
	* @return: void
	********************/
	void SetRotationSpeed(float _rot) { m_rotationSpeed = _rot; }


private:
	CDX10Renderer* m_pRenderer;

	v3float m_position;
	v3float m_look;
	v3float m_up;
	v3float m_right;
	
	float m_speed;
	float m_rotationSpeed;
	
};

#endif	// __CAMERA_DEBUG_H__

