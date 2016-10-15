/*
 *  GuiManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxGui.h"
//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application«s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    
public:
    
    //! Constructor
    GuiManager();
    
    //! Destructor
    ~GuiManager();
    
    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    int getWidth()  {return m_gui.getWidth();}
    
    int getHeight()  {return m_gui.getHeight();}
    
    void setGuiTrackingPos(const ofVec2f& pos) { m_trackingPos = pos; }
    
    void setGuiBrightness(int value) {m_brightness = value;}
    
    void setGuiThreshold(int value) {m_threshold = value;}
    
    void setGuiBackgroundThreshold(int value) {m_backgroundThreshold = value;}
    
    void setGuiMinArea(int value) {m_minArea = value;}
    
    void setGuiMaxArea(int value) {m_maxArea = value;}
    
    void setBackgroundSubstraction(bool value) {m_backgroundSubstraction = value;}
    
    void setPaperThrowerSlider(int value) {m_paperThrowerSlider = value;}
    
private:
    
    void setupCameraGui();
    
    void setupTrackingGui();
    
    void setupPaperThrowerGui();
    
public:
    
    static const int GUI_WIDTH;
    
private:
    
    // Fluid GUI
    ofxPanel	m_gui;
    bool        m_showGui;  //It defines the whether the gui should be shown or not
    
    ofParameterGroup	 m_cameraParameters;
    ofParameterGroup	 m_trackingParameters;
    ofParameterGroup	 m_paperThrowerParameters;
    
    ofParameter<float>	 m_guiFPS;
    ofParameter<ofVec2f> m_trackingPos;
    ofParameter<int>	 m_brightness;
    ofParameter<int>	 m_threshold;
    ofParameter<float>	 m_learningTime;
    ofParameter<int>	 m_backgroundThreshold;
    ofParameter<int>	 m_minArea;
    ofParameter<int>	 m_maxArea;
    ofParameter<bool>	 m_reverseCoordinates;
    ofParameter<bool>	 m_backgroundSubstraction;
    
    ofParameter<int>     m_cropLeft, m_cropRight, m_cropTop, m_cropBottom;
    
    ofParameter<int>	 m_paperThrowerSlider;
    
};

//==========================================================================


