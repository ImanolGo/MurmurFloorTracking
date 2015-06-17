/*
 *  State.cpp
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#include "State.h"


State::State(const std::string& name):m_name(name), m_active(false), m_initialized(false)
{
    //Intentionally left empty
}


State::~State()
{
    //Intentionally left empty
}


void State::initialize()
{
   if(m_initialized)
       return;
    
    m_initialized = true;
    
}

void State::onEnter()
{
    m_active = true;   
}

void State::onExit()
{
    m_active = false; 
}
