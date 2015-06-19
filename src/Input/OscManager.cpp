/*
 *  OscManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */


#include "OscManager.h"
#include "SettingsManager.h"
#include "AppManager.h"


OscManager::OscManager(): Manager()
{
    //Intentionally left empty
}

OscManager::~OscManager()
{
   ofLogNotice() << "OscManager::destructor";
}


//--------------------------------------------------------------

void OscManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"OscManager::initialized" ;
    this->setupOscReceiver();
    this->setupOscSender();
}

void OscManager::setupOscReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getPortReceive();
    
    m_oscReceiver.setup(portReceive);
   
    ofLogNotice() <<"OscManager::setupOscReceiver -> listening for osc messages on port  " << portReceive;
}

void OscManager::setupOscSender()
{
    int portSend = AppManager::getInstance().getSettingsManager().getPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    
    m_oscSender.setup(host, portSend);
    
    ofLogNotice() <<"OscManager::setupOscSender -> open osc connection " << host << ":" << portSend;
}


void OscManager::sendPosition(const ofPoint& pos)
{
    ofxOscMessage m;
    m.setAddress("/MurmurFloorTracking/position");
    m.addIntArg(pos.x);
    m.addIntArg(pos.y);
    m_oscSender.sendMessage(m);
}

void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(&m);
        
        // check for mouse moved message
        if(m.getAddress() == "/MurmurFloorTracking/position"){
            ofPoint pos;
            pos.x = m.getArgAsFloat(0);
            pos.y = m.getArgAsFloat(1);
            AppManager::getInstance().getTrackingManager().setTrackingPos(pos);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/position/X"){
            float x = m.getArgAsFloat(0);
            AppManager::getInstance().getTrackingManager().onTrackingPosXChange(x);

        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/position/Y"){
            float y = m.getArgAsFloat(0);
            AppManager::getInstance().getTrackingManager().onTrackingPosYChange(y);
            
        }
        
    }
}








