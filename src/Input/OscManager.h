/*
 *  OscManager.h
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxOsc.h"

//========================== class OscManager =======================================
//==============================================================================
/** \class OscManager OscManager.h
 *	\brief class for managing the OSC events
 *	\details It reads all the OSC events and create the proper application events
 */


class OscManager: public Manager
{

public:
    //! Constructor
    OscManager();

    //! Destructor
    virtual ~OscManager();

    //! setups the manager
    void setup();

    //! updates the manager
    void update();
    
    //! send position
    void sendPosition(const ofPoint& pos);
    
private:
    
    //! sets upt the osc receiver
    void setupOscReceiver();
    
    //! sets upt the osc sender
    void setupOscSender();
    

 private:
    
     ofxOscReceiver m_oscReceiver;  ///< OSC receiver class
     ofxOscSender   m_oscSender;    ///< OSC sender class

};

