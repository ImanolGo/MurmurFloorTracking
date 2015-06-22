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
#include "LayoutManager.h"

#include "GuiManager.h"

const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "MurmurFloorTracking";
const int GuiManager::GUI_WIDTH = 250;


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
    
    m_gui.setDefaultWidth(GUI_WIDTH);
    m_gui.setup(GUI_SETTINGS_NAME, GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(LayoutManager::MARGIN, LayoutManager::MARGIN);
    
    this->setupCameraGui();
    this->setupTrackingGui();
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
 
   
}


void GuiManager::setupCameraGui()
{
    TrackingManager* trackingManager = &AppManager::getInstance().getTrackingManager();
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
   
    m_brightness.set("Brightness", 40, 0, 255);
    m_brightness.addListener(trackingManager, &TrackingManager::onBrightnessChange);
    m_gui.add(m_brightness);
    
}

void GuiManager::setupTrackingGui()
{
    TrackingManager* trackingManager = &AppManager::getInstance().getTrackingManager();
    
    m_threshold.set("Threshold", 40, 0, 255);
    m_threshold.addListener(trackingManager, &TrackingManager::onThresholdChange);
    m_gui.add(m_threshold);
    
    m_backgroundThreshold.set("BackgroundThreshold", 10, 0, 30);
    m_backgroundThreshold.addListener(trackingManager, &TrackingManager::onBackgroundThresholdChange);
    m_gui.add(m_backgroundThreshold);
    
    m_minArea.set("MinArea", 20, 0, 100);
    m_minArea.addListener(trackingManager, &TrackingManager::onMinAreaChange);
    m_gui.add(m_minArea);
    
    m_maxArea.set("MaxArea", 100, 100, 500);
    m_maxArea.addListener(trackingManager, &TrackingManager::onMaxAreaChange);
    m_gui.add(m_maxArea);
    
    m_trackingPos.set("TrackingPos", ofVec2f(0,0),  ofVec2f(0,0),  ofVec2f(1.0,1.0));
    m_trackingPos.addListener(trackingManager, &TrackingManager::onTrackingPosChange);
    m_gui.add(m_trackingPos);
    
    m_backgroundSubstraction.set("BackgroundSubstraction", true);
    m_backgroundSubstraction.addListener(trackingManager, &TrackingManager::onBackgroundSubstractionChange);
    m_gui.add(m_backgroundSubstraction);
    
    ofxButton * resetBackground = new ofxButton();
    resetBackground->setup("ResetBackground");
    resetBackground->addListener(trackingManager, &TrackingManager::onResetBackground);
    m_gui.add(resetBackground);
    
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
    ofLogNotice() <<"GuiManager::toggleGui -> show GUI "<< m_showGui;
    m_showGui = !m_showGui;
}

