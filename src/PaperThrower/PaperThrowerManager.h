/*
 *  PaperThrowerManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 03/08/15.
 *
 */

#pragma once

#include "Manager.h"

#include "ofxMultiKinectV2.h"
#include "ofxCv.h"


//========================== class PaperThrowerManager ==============================
//============================================================================
/** \class PaperThrowerManager PaperThrowerManager.cpp
 *	\brief Class managing Murmur«s paper thrower
 *	\details It sends the necessary commands to the serial port connected to the Arduino
 */

class PaperThrowerManager: public Manager
{
    
    static const int BAUD_RATE;		///< defines communication's baud rate
    
public:
    
    //! Constructor
    PaperThrowerManager();
    
    //! Destructor
    ~PaperThrowerManager();
    
    //! Set-up the kinect camera tracking
    void setup();
    
    //! Draw kinect camera tracking
    void draw();
    
    //! Fire paper
    void onFire();
    
    //! Slide paper
    void onSliderScroll(int & value);
    
    //! Exit
    void onExit();
   
private:
    
    //! Set-up the serial
    void setupSerial();
    
private:
    
   ofSerial     m_serial;
   int          m_slider;
    
};

//==========================================================================


