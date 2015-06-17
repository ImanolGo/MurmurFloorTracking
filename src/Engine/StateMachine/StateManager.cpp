/*
 *  StateMachine.cpp
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#include "StateManager.h"


StateManager::StateManager(): Manager()
{
    setup();
}

StateManager::~StateManager()
{
    ofLogNotice() <<"StateManager::destructor";
}


void StateManager::setup()
{
     ofLogNotice() <<"StateManager::initialized";
    
    this->createStateMachine();
    this->createStates();

    //Set the starting state
    //m_stateMachine->onChangeState("SimpleVoronoiState");

}

void StateManager::createStateMachine()
{
    m_stateMachine = ofPtr<StateMachine>(new StateMachine());
}

void StateManager::createStates()
{
    //Create all the states

    /*LoopState* loopState = new LoopState("LoopState");
    loopState->initialize();
    m_stateMachine->addState(loopState);*/
}


void StateManager::changeState(string name)
{
    //Create all the states
    
    m_stateMachine->onChangeState(name);
}













