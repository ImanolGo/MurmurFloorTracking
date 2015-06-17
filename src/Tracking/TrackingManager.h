/*
 *  TrackingManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#pragma once

#include "Manager.h"

#include "ofxMultiKinectV2.h"


//========================== class TrackingManager ==============================
//============================================================================
/** \class TrackingManager TrackingManager.cpp
 *	\brief Class managing Murmur«s floor tracking
 *	\details It reads the IR sensor of the Kinect camera and sends the blob tracking information
 */

class TrackingManager: public Manager
{
    
    static const int IR_CAMERA_WIDTH;
    static const int IR_CAMERA_HEIGHT;
    
public:
    
    //! Constructor
    TrackingManager();
    
    //! Destructor
    ~TrackingManager();
    
    //! Set-up the kinect camera tracking
    void setup();
    
    //! Update the kinect camera tracking
    void update();
    
    //! Draw kinect camera tracking
    void draw();
    
    //! Brightness change controlled by GUI
    void onBrightnessChange(float & value);
   
    
private:
    
   
    void setupKinectCamera();
    
    void updateKinectCamera();
    
    void drawKinectCamera();
    
    
private:
    
    
    ofShader             m_irShader;                 ///< Shader class handling the IR camera capture
    static const string  m_irFragmentShaderString;   ///< Actual fragement shader handling the IR camera capture
    
    ofxMultiKinectV2     m_kinect;                   ///< Mircrosoft Kinect v2 class
    ofTexture            m_irTexture;                ///< The texture holding every new IR captured frame
    
    float                m_irBrightness;             ///< brightness of the IR image
    
    
    
};

//==========================================================================


