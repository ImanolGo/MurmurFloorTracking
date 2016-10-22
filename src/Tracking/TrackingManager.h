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

#define KINECT_CAMERA //Comment if you are using the laptop camera


//========================== class TrackingManager ==============================
//============================================================================
/** \class TrackingManager TrackingManager.cpp
 *	\brief Class managing Murmur«s floor tracking
 *	\details It reads the IR sensor of the Kinect camera and sends the blob tracking information
 */

class TrackingManager: public Manager
{
    
    static const float SCALE;
    static const int TRACKING_PERSISTANCY;
    static const int LEARNING_TIME;
    
public:
    
    static const int IR_CAMERA_WIDTH;
    static const int IR_CAMERA_HEIGHT;
    
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
    
    //! Return the tracking visual height
    int getHeight() const;
    
    //! Return the tracking visual hewidthight
    int getWidth() const;
    
    //! Return the tracking visual position
    ofVec2f getPosition() const;
    
    //! Tracking position coordinates change controlled by GUI
    void onTrackingPosChange(ofVec2f & value);
    
    //! Brightness change controlled by GUI
    void onBrightnessChange(int & value);
    
    //! Threshold change controlled by GUI
    void onThresholdChange(int & value);
    
    //! Learning Time change controlled by GUI
    void onLearningTimeChange(float & value);
    
    //! Background Threshold change controlled by GUI
    void onBackgroundThresholdChange(int & value);
    
    //! Minimum area change controlled by GUI
    void onMinAreaChange(int & value);
    
    //! Maximum area change controlled by GUI
    void onMaxAreaChange(int & value);
    
    //! Background Subtraction togle change controlled by GUI
    void onBackgroundSubstractionChange(bool & value);
    
    //! Reverse coordinates togle change controlled by GUI
    void onReverseCoordinatesChange(bool & value);
    
    //! Reset Backround for background substraction
    void onResetBackground();
    
    void onCropLeft( int & pixels) {m_cropLeft = pixels;}
    
    void onCropRight( int & pixels) {m_cropRight = pixels;}
    
    void onCropTop( int & pixels) {m_cropTop = pixels;}
    
    void onCropBottom( int & pixels){m_cropBottom = pixels;}
   
private:
    
    void setupFbos();
    
    void setupCamera();
    
    void setupKinectCamera();
    
    void setupWebCamera();
    
    void setupContourTracking();
    
    void updateCamera();
    
    void updateWebCamera();
    
    void updateKinectCamera();
    
    void updateContourTracking();
    
    void updateTrackingPoint();
    
    void drawTracking();
    
    void drawCamera();
    
    void drawContourTracking();
    
    void drawTrackingPosition();
    
private:
    
        
    ofShader                m_irShader;                 ///< Shader class handling the IR camera capture
    static const string     m_irFragmentShader;         ///< Fragment shader handling the IR camera capture
    
    ofxMultiKinectV2        m_kinect;                   ///< Mircrosoft Kinect v2 class
    ofVideoGrabber          m_vidGrabber;                  ///< Video Grabber
    ofTexture               m_irTexture;                ///< The texture holding every new IR captured frame
    ofFbo                   m_irFbo;                    ///< The fbo holding the IR frame after applying shader
    ofFbo                   m_findBlobsFbo;             ///< The fbo holding the image for blob detection

    int                     m_irBrightness;             ///< brightness of the IR image
    
    ofxCv::ContourFinder        m_contourFinder;            ///< threshold used for the contour tracking
    ofxCv::RunningBackground    m_background;               ///< used for background substraction
    ofVec2f                     m_trackingPosition;         ///< position representing the tracking object
    int                         m_threshold;                ///< threshold used for the contour tracking
    int                         m_thresholdBackground;      ///< threshold used for the backround substraction
    int                         m_contourMinArea;           ///< contour minimum area
    int                         m_contourMaxArea;           ///< blcontourob's maxmimum area
    bool                        m_substractBackground;      ///< defines whether to extract or not the background
    bool                        m_revserseCoordinates;      ///< defines whether to reverse or not the coordinates
    
    int                         m_cropLeft, m_cropRight, m_cropTop, m_cropBottom;
    
    
};

//==========================================================================


