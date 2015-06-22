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
    this->setupText();
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

void OscManager::setupText()
{
    ofVec3f position;
    ofVec2f positionTrackingVisual = AppManager::getInstance().getTrackingManager().getPosition();
    int width = AppManager::getInstance().getTrackingManager().getWidth();
    int fontSize = 12;
    position.x = positionTrackingVisual.x;
    position.y = positionTrackingVisual.y +  AppManager::getInstance().getTrackingManager().getWidth() + LayoutManager::MARGIN;
    int height = fontSize*3;
    
    int portSend = AppManager::getInstance().getSettingsManager().getPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    string text = ">> OSC sending -> Host: " + host + ", Port: " + ofToString(portSend);
    
    m_sendingInformation =  ofPtr<TextVisual> (new TextVisual(position, width, height));
    m_sendingInformation->setLineHeight(1.5);
    m_sendingInformation->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    m_sendingInformation->setColor(ofColor::white);
    
    AppManager::getInstance().getViewManager().addOverlay(m_sendingInformation);
    
    
    int porReceive = AppManager::getInstance().getSettingsManager().getPortReceive();
    text = ">> OSC receiving -> Port: " + ofToString(porReceive);
    
    position.y += (height + 3*fontSize);
    m_receivingInformation =  ofPtr<TextVisual> (new TextVisual(position, width, height));
    m_receivingInformation->setLineHeight(1.5);
    m_receivingInformation->setText(text, "fonts/open-sans/OpenSans-Semibold.ttf", fontSize);
    m_receivingInformation->setColor(ofColor::white);
    
    AppManager::getInstance().getViewManager().addOverlay(m_receivingInformation);
    
}


void OscManager::sendPosition(const ofPoint& pos)
{
    ofxOscMessage m;
    m.setAddress("/MurmurFloorTracking/position");
    m.addFloatArg(pos.x);
    m.addFloatArg(pos.y);
    m_oscSender.sendMessage(m);
}

void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(&m);
        
        if(m.getAddress() == "/MurmurFloorTracking/TrackingPos"){
            ofVec2f pos;
            pos.x = m.getArgAsFloat(0);
            pos.y = m.getArgAsFloat(1);
            AppManager::getInstance().getTrackingManager().onTrackingPosChange(pos);

        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/Brightness"){
            int brightness = m.getArgAsInt32(0);
            AppManager::getInstance().getTrackingManager().onBrightnessChange(brightness);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/Threslhold"){
            int threshold = m.getArgAsInt32(0);
            AppManager::getInstance().getTrackingManager().onThresholdChange(threshold);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/BackgroundThreslhold"){
            int backgroundThreslhold = m.getArgAsInt32(0);
            AppManager::getInstance().getTrackingManager().onThresholdChange(backgroundThreslhold);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/MinArea"){
            int minArea = m.getArgAsInt32(0);
            AppManager::getInstance().getTrackingManager().onMinAreaChange(minArea);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/MaxArea"){
            int maxArea = m.getArgAsInt32(0);
            AppManager::getInstance().getTrackingManager().onMinAreaChange(maxArea);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/BackgroundSubstraction"){
            bool backgroundSubstraction = ( m.getArgAsInt32(0) != 0);
            AppManager::getInstance().getTrackingManager().onBackgroundSubstractionChange(backgroundSubstraction);
        }
        
        else if(m.getAddress() == "/MurmurFloorTracking/ResetBackground"){
            AppManager::getInstance().getTrackingManager().onResetBackground();
        }
        
    }
}








