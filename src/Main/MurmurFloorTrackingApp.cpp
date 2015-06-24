/*
 *  MurmurFloorTrackingApp.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#include "AppManager.h"

#include "MurmurFloorTrackingApp.h"

//--------------------------------------------------------------
void MurmurFloorTrackingApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void MurmurFloorTrackingApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void MurmurFloorTrackingApp::draw(){
    AppManager::getInstance().draw();
}

void MurmurFloorTrackingApp::exit()
{
    ofLogNotice() <<"MurmurFloorTrackingApp::exit";

}


