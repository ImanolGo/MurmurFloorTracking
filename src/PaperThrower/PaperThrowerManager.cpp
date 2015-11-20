/*
 *  PaperThrowerManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 08/03/15.
 *
 */

#include "AppManager.h"

#include "PaperThrowerManager.h"

const int PaperThrowerManager::BAUD_RATE = 115200; ///< the baud rate


PaperThrowerManager::PaperThrowerManager(): Manager()
{
    //Intentionally left empty
}


PaperThrowerManager::~PaperThrowerManager()
{
    ofLogNotice() <<"PaperThrowerManager::Destructor";
    this->onExit();
}


void PaperThrowerManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupSerial();
    
    ofLogNotice() <<"PaperThrowerManager::initialized";
}

void PaperThrowerManager::setupSerial()
{
    
    m_serial.enumerateDevices();
    vector <ofSerialDeviceInfo> deviceList = m_serial.getDeviceList();
    
    int portNum = 0;
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    
    //m_serial.setup(portNum, BAUD_RATE); //open the first device
    //serial.setup("COM4"); // windows example
    
    for(int i= 0; i< deviceList.size();i++)
    {
        std::cout << deviceList[i].getDeviceName()<< std::endl;
        if(ofIsStringInString(deviceList[i].getDeviceName(), "tty.usbmodem")) //Arduino
        {
            m_serial.setup(deviceList[i].getDevicePath(),BAUD_RATE); // mac osx example
            //m_serial.setup("/dev/tty.usbmodem1421",BAUD_RATE); // mac osx example
            //serial.setup("/dev/ttyUSB0", 9600); //linux example
            
            ofLogNotice() << "PaperThrowerManager::setupSerial-> serial connected to " << deviceList[i].getDevicePath() ;
            return;
        }
    }
    
    ofLogNotice() << "PaperThrowerManager::setupSerial-> unable to connect to Arduino";
}

void PaperThrowerManager::onFire()
{
    char fire = 203;
    m_serial.writeByte(fire);
}

void PaperThrowerManager::onSliderScroll(int & value)
{
    m_slider = ofClamp(value, 0, 100);
    m_serial.writeByte((char) m_slider);
}

void PaperThrowerManager::onExit()
{
    m_slider = 0;
    onSliderScroll(m_slider);
    m_serial.writeByte(0);
}





