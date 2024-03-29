/////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	IGameState.h
//
// Authors: James Gonzalez (JG), 
// 
// Purpose: The interface for all states
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

class IGameState
{
private:
	bool render;

public:
	IGameState(void)
	{
		render = true;
	}
	virtual ~IGameState(void) = 0 {}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:	Enter
	// 
	// Purpose: Enter the state
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Enter(void) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:	Exit
	// 
	// Purpose: Exit the state
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Exit(void) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:	Input
	// 
	// Purpose: Get input from user
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Input(float fElapsedTime ) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:	Update
	// 
	// Purpose: Run update code
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Update(float fElapsedTime ) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:	Render
	// 
	// Purpose: draw to screen
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Render(void) = 0;

	
	bool GetWillRender() const { return render; }
	void SetWillRender(bool val) { render = val; }
};