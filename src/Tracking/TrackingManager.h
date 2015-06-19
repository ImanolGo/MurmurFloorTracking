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
#include "ofxCv.h"


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
    static const int TRACKING_PERSISTANCY;
    static const int LEARNING_TIME;
    
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
    void onBrightnessChange(int & value);
    
    //! Threshold change controlled by GUI
    void onThresholdChange(int & value);
    
    //! Background Threshold change controlled by GUI
    void onBackgroundThresholdChange(int & value);
    
    //! Minimum area change controlled by GUI
    void onMinAreaChange(int & value);
    
    //! Maximum area change controlled by GUI
    void onMaxAreaChange(int & value);
    
    //! Background Subtraction togle change controlled by GUI
    void onBackgroundSubstractionChange(bool & value);
    
    //! Reset Backround for background substraction
    void onResetBackground();
   
private:
    
    void setupKinectCamera();
    
    void setupContourTracking();
    
    void updateKinectCamera();
    
    void updateContourTracking();
    
    void updateTrackingPoint();
    
    void drawCamera();
    
    void drawIrCamera();
    
    void drawContourTracking();
    
    void drawTracking();
    
    void drawTrackingPosition();
    
    void drawTrackingPosText();
    
private:
    
    
    ofShader                m_irShader;                 ///< Shader class handling the IR camera capture
    static const string     m_irFragmentShaderString;   ///< Actual fragement shader handling the IR camera capture
    
    ofxMultiKinectV2        m_kinect;                   ///< Mircrosoft Kinect v2 class
    ofTexture               m_irTexture;                ///< The texture holding every new IR captured frame
    ofFbo                   m_irFbo;                    ///< The fbo holding the IR frame after applying shader
    int                     m_irBrightness;             ///< brightness of the IR image
    
    ofxCv::ContourFinder        m_contourFinder;            ///< threshold used for the contour tracking
    ofxCv::RunningBackground    m_background;               ///< used for background substraction
    ofPoint                     m_trackingPosition;         ///< position representing the tracking object
    int                         m_threshold;                ///< threshold used for the contour tracking
    int                         m_thresholdBackground;      ///< threshold used for the backround substraction
    int                         m_contourMinArea;           ///< contour minimum area
    int                         m_contourMaxArea;           ///< blcontourob's maxmimum area
    bool                        m_substractBackground;      ///< defines whether to extract or not the background
    
};

//==========================================================================


