/*
 *  AppManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(true)
{
    //Intentioanlly left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    
    setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
   ofSetVerticalSync(true);
   ofSetFrameRate(60);
   ofShowCursor();
}


void AppManager::setupManagers()
{
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_settingsManager.setup();
    m_layoutManager.setup();
    m_oscManager.setup();
    m_trackingManager.setup();
    m_keyboardManager.setup();
    m_paperThrowerManager.setup();
    m_guiManager.setup();
}

void AppManager::update()
{
    m_trackingManager.update();
    m_visualEffectsManager.update();
    m_oscManager.update();
}


void AppManager::draw()
{
    m_viewManager.draw();
    
    if (!m_debugMode) {
        return;
    }
    
    m_oscManager.draw();
    m_trackingManager.draw();
    m_guiManager.draw();
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    
    m_guiManager.showGui(m_debugMode);

}



