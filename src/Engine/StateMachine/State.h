/*
 *  State.h
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#pragma once

#include "ofMain.h"

class StateManager;

//========================== class State =======================================
//==============================================================================
/** \class State State.h
 *	\brief Represents a state of a finite state machine.
 *	\details Each state state has a unique identifier (its name).
 */


class State
{
public:

    //! Constructor
    State(const std::string& name);
    //! Destructor
    virtual ~State();

    //! Do the state initialization stuff here
    virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();

    //! returns if the state is active or not
    bool isActive() const {return m_active;}
    //! Returns the unique identifier of this state
    const std::string& getName() const { return m_name; }


protected:

    std::string      m_name;         ///< unique identifier of this state
    bool             m_active;       ///< determines whether the text is active or not
    bool             m_initialized;  ///< determines whether the State has been initialized or not

};



