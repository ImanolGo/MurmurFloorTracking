/*
 *  GuiManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "TrackingManager.h"

#include "GuiManager.h"

const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
    //Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
    if(m_initialized)
        return;
    
    ofLogNotice() <<"GuiManager::initialized";
    
    Manager::setup();
    
    m_gui.setup("GuiSettings", GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(20, 20);
    
    this->setupCameraGui();
    this->setupTrackingGui();
    
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}


void GuiManager::setupCameraGui()
{
    TrackingManager* trackingManager = &AppManager::getInstance().getTrackingManager();
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
    
    ofxFloatSlider * brightness = new ofxFloatSlider();
    brightness->setup("Brightness", 6535.0, 100.0, 80000);
    brightness->addListener(trackingManager, &TrackingManager::onBrightnessChange);
    m_gui.add(brightness);
}

void GuiManager::setupTrackingGui()
{

}

void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    m_gui.draw();
    m_guiFPS = ofGetFrameRate();
}


void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}
