/*
 *  StateMachine.h
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#pragma once

#include "Manager.h"
#include "ofMain.h"
#include "StateMachine.h"

//========================== class StateManager ==============================
//============================================================================
/** \class StateManager StateManager.h
 *	\brief It creates and manages a certain state machine
 *	\details It would create a state machhine according to a certain logic
 */


class StateManager: public Manager
{
public:
    
    //! Constructor
    StateManager();
    
    //! Destructor
    ~StateManager();

    //! Setups the state machine
    void setup();
    
    //! Change to a state
    void changeState(string name);

private:
    
	//! Creates all states
	void createStates();

	//! Creates the state manager
	void createStateMachine();
    
private:

    ofPtr<StateMachine>	  m_stateMachine;	///< current state machine

};


