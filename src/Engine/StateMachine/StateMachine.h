/*
 *  StateMachine.h
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#pragma once


#include "ofMain.h"
#include "State.h"


//======================== class StateMachine ==================================
//==============================================================================
/** \class StateMachine StateMachine.h
 *	\brief Finite state machine for managing states and their transitions.
 */
class StateMachine
{
public:
    //! Constructor
    StateMachine();
    //! Destructor
    ~StateMachine();

    //! Adds a new state if there is no state with the same name
    void addState(ofPtr<State> state);
    //! Sets the current state to the specified state (calls onEnter() for the new state).
    void onChangeState(std::string& name);

private:

    //! Adds all the listeners
    void addListeners();
    
    //! Removes all the listeners
    void removeListeners();

    //! Switches the current state to the specified state (onExit() resp. onEnter() are called for the current and the new state).
    void switchStateTo(const ofPtr<State> newState);

	//==========================================================================
    
public:
    
    static ofEvent<string> changeStateEvent;

private:

    typedef map<std::string, ofPtr<State> >		StateMap;		  ///< map for storing states sorted by
    StateMap		  m_states;			///< a map of all added states sorted by there name
    ofPtr<State>	  m_currentState;	///< the currently active state

};

