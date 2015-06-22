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
    m_gui.setPosition(LayoutManager::MARGIN, LayoutManager::MARGIN);
    
    this->setupCameraGui();
    this->setupTrackingGui();
    
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}


void GuiManager::setupCameraGui()
{
    TrackingManager* trackingManager = &AppManager::getInstance().getTrackingManager();
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
   
    ofxIntSlider * brightness = new ofxIntSlider();
    brightness->setup("Brightness", 40, 0, 255);
    //brightness->setup("Brightness", 6535.0, 100.0, 80000);
    brightness->addListener(trackingManager, &TrackingManager::onBrightnessChange);
    m_gui.add(brightness);
    
}

void GuiManager::setupTrackingGui()
{
    TrackingManager* trackingManager = &AppManager::getInstance().getTrackingManager();
    
    ofxIntSlider * threshold = new ofxIntSlider();
    threshold->setup("Threshold", 40, 0, 255);
    threshold->addListener(trackingManager, &TrackingManager::onThresholdChange);
    m_gui.add(threshold);
    
    ofxIntSlider * backgroundThreshold = new ofxIntSlider();
    backgroundThreshold->setup("BackgroundThreshold", 10, 0, 30);
    backgroundThreshold->addListener(trackingManager, &TrackingManager::onBackgroundThresholdChange);
    m_gui.add(backgroundThreshold);
    
    ofxIntSlider * minArea = new ofxIntSlider();
    minArea->setup("MinArea", 20, 0, 100);
    minArea->addListener(trackingManager, &TrackingManager::onMinAreaChange);
    m_gui.add(minArea);
    
    ofxIntSlider * maxArea = new ofxIntSlider();
    maxArea->setup("MaxArea", 100, 100, 500);
    maxArea->addListener(trackingManager, &TrackingManager::onMaxAreaChange);
    m_gui.add(maxArea);
    
    m_trackingPos.set("TrackingPos", ofVec2f(0,0),  ofVec2f(0,0),  ofVec2f(1.0,1.0));
    m_trackingPos.addListener(trackingManager, &TrackingManager::onTrackingPosChange);
    m_gui.add(m_trackingPos);
    
    ofxToggle * backgroundSubstraction = new ofxToggle();
    backgroundSubstraction->setup("BackgroundSubstraction", true);
    backgroundSubstraction->addListener(trackingManager, &TrackingManager::onBackgroundSubstractionChange);
    m_gui.add(backgroundSubstraction);
    
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

void GuiManager::setGuiTrackingPos(const ofVec2f& pos)
{
    m_trackingPos = pos;
}
