/*
 *  StateMachine.cpp
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */

#include "StateMachine.h"

// the static event, or any static variable, must be initialized outside of the class definition.
ofEvent<string> StateMachine::changeStateEvent = ofEvent<string>();

StateMachine::StateMachine()
{
    //Intentionally left empty
}

StateMachine::~StateMachine()
{
	//Intentionally left empty
}

void StateMachine::addListeners()
{
    ofAddListener(changeStateEvent, this, &StateMachine::onChangeState);
}

void  StateMachine::removeListeners()
{
    ofRemoveListener(changeStateEvent, this, &StateMachine::onChangeState);
}

void StateMachine::addState(ofPtr<State> state)
{
	m_states[state->getName()] = state;
}


void StateMachine::onChangeState(string& name)
{
    
    StateMap::const_iterator it = m_states.find(name);
    if(it == m_states.end()) {
        ofLogError()<< "StateMachine::changeState-> no state with name: " + name;
    }
    else{
        if (m_currentState) m_currentState->onExit();
        m_currentState = it->second;
        m_currentState->onEnter();
    }
}



