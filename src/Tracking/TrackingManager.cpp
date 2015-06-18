/*
 *  TrackingManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 17/06/15.
 *
 */

#include "AppManager.h"

#include "TrackingManager.h"

using namespace ofxCv;
using namespace cv;

#define STRINGIFY(x) #x

const string TrackingManager::m_irFragmentShaderString =
STRINGIFY(
    uniform sampler2DRect tex;
    uniform float brightness;
    void main()
    {
        vec4 col = texture2DRect(tex, gl_TexCoord[0].xy);
        float value = col.r / brightness;
        //float value = col.r / 6535.0;
        gl_FragColor = vec4(vec3(value), 1.0);
    }
);

const int TrackingManager::IR_CAMERA_WIDTH = 512;
const int TrackingManager::IR_CAMERA_HEIGHT = 424;



TrackingManager::TrackingManager(): Manager(), m_threshold(80), m_contourMinArea(50), m_contourMaxArea(1000)
{
    //Intentionally left empty
}


TrackingManager::~TrackingManager()
{
    ofLogNotice() <<"TrackingManager::Destructor";
}


void TrackingManager::setup()
{
    if(m_initialized)
        return;
    
    ofLogNotice() <<"TrackingManager::initialized";
    
    Manager::setup();
    
    this->setupKinectCamera();
    this->setupContourTracking();
}

void TrackingManager::setupContourTracking()
{
    
    m_contourFinder.setMinAreaRadius(m_contourMinArea);
    m_contourFinder.setMaxAreaRadius(m_contourMaxArea);
    m_contourFinder.setTargetColor(ofColor::white, TRACK_COLOR_RGB);
    m_contourFinder.setThreshold(m_threshold);
}

void TrackingManager::setupKinectCamera()
{
    m_irShader.setupShaderFromSource(GL_FRAGMENT_SHADER, m_irFragmentShaderString);
    m_irShader.linkProgram();
    m_irFbo.allocate(IR_CAMERA_WIDTH, IR_CAMERA_HEIGHT, GL_RGB);
    
    m_kinect.open(true, true, 0);

    // Note :
    // Default OpenCL device might not be optimal.
    // e.g. Intel HD Graphics will be chosen instead of GeForce.
    // To avoid it, specify OpenCL device index manually like following.
    // m_kinect.open(true, true, 0, 1); // GeForce on MacBookPro Retina
    
    m_kinect.start();
    
}


void TrackingManager::update()
{
    this->updateKinectCamera();
    this->updateContourTracking();
}

void TrackingManager::updateKinectCamera()
{
    m_kinect.update();
    if (m_kinect.isFrameNew()) {
        m_irTexture.loadData(m_kinect.getIrPixelsRef());
        m_irFbo.begin();
        m_irShader.begin();
        m_irTexture.draw(0, 0, 512, 424);
        m_irShader.end();
    }
}

void TrackingManager::updateContourTracking()
{
    if (m_kinect.isFrameNew()) {
        ofImage image;
        ofPixels pixels;
        m_irFbo.readToPixels(pixels);
        image.setFromPixels(pixels);
        m_contourFinder.findContours(image);
    }
}




void TrackingManager::draw()
{
    this->drawKinectCamera();
}

void TrackingManager::drawKinectCamera()
{
    if (m_irTexture.isAllocated()) {
        m_irShader.begin();
        m_irShader.setUniform1f("brightness", m_irBrightness);
        m_irTexture.draw(0, 0, IR_CAMERA_WIDTH, IR_CAMERA_HEIGHT);
        m_irShader.end();
    }
}



//--------------------------------------------------------------

void TrackingManager::onBrightnessChange(float & value){
    m_irBrightness = value;
}

void TrackingManager::onThresholdChange(int & value){
    m_threshold = value;
    m_contourFinder.setThreshold(m_threshold);
}

void TrackingManager::onMinAreaChange(int & value){
    m_contourMinArea = value;
    m_contourFinder.setMinAreaRadius(m_contourMinArea);
}

void TrackingManager::onMaxAreaChange(int & value){
    m_contourMaxArea = value;
    m_contourFinder.setMaxAreaRadius(m_contourMaxArea);
}



