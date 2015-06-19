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
        //brightness = (brightness/255.0)*(6500 - 80000) + 80000;
        float value = col.r / brightness;
        //float value = col.r / 6535.0;
        gl_FragColor = vec4(vec3(value), 1.0);
    }
);

const int TrackingManager::IR_CAMERA_WIDTH = 512;
const int TrackingManager::IR_CAMERA_HEIGHT = 424;
const int TrackingManager::TRACKING_PERSISTANCY = 5*30;
const int TrackingManager::LEARNING_TIME = 10*30;


TrackingManager::TrackingManager(): Manager(), m_threshold(80), m_contourMinArea(50), m_contourMaxArea(1000), m_thresholdBackground(10), m_substractBackground(true)
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
    m_contourFinder.getTracker().setPersistence(TRACKING_PERSISTANCY);
    //m_contourFinder.getTracker().setMaximumDistance(32);
    
    m_background.setLearningTime(LEARNING_TIME);
    m_background.setThresholdValue(m_threshold);
    m_background.reset();
}

void TrackingManager::setupKinectCamera()
{
    m_irShader.setupShaderFromSource(GL_FRAGMENT_SHADER, m_irFragmentShaderString);
    m_irShader.linkProgram();
    
    m_irFbo.allocate(IR_CAMERA_WIDTH, IR_CAMERA_HEIGHT, GL_RGB);
    m_irFbo.begin();
        ofClear(0,0,0,0);
    m_irFbo.end();
    
    m_kinect.open(true, true, 0, 2);
    m_kinect.start();

    // Note :
    // Default OpenCL device might not be optimal.
    // e.g. Intel HD Graphics will be chosen instead of GeForce.
    // To avoid it, specify OpenCL device index manually like following.
    // m_kinect.open(true, true, 0, 1); // GeForce on MacBookPro Retina
    
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
    
        if (m_irTexture.isAllocated()) {
            m_irFbo.begin();
            m_irShader.begin();
            m_irShader.setUniform1f("brightness", m_irBrightness);
            m_irTexture.draw(0, 0, IR_CAMERA_WIDTH, IR_CAMERA_HEIGHT);
            m_irShader.end();
            m_irFbo.end();
        }
    }
}

void TrackingManager::updateContourTracking()
{
    if (m_kinect.isFrameNew()) {
        ofImage image;
        ofPixels pixels;
        m_irFbo.readToPixels(pixels);
        image.setFromPixels(pixels);
        
        if(m_substractBackground){
            ofImage thresholded;
            m_background.update(image, thresholded);
            thresholded.update();
            m_contourFinder.findContours(thresholded);
        }
        else{
            m_contourFinder.findContours(image);
        }
        
        this->updateTrackingPoint();
    }
}

void TrackingManager::updateTrackingPoint()
{
    double contourArea = 0;
    for(int i = 0; i < m_contourFinder.size(); i++) {
        
        if(contourArea < m_contourFinder.getContourArea(i)){
            contourArea =  m_contourFinder.getContourArea(i);
            m_trackingPosition = toOf(m_contourFinder.getCenter(i));
            m_trackingPosition.x/=IR_CAMERA_WIDTH;
            m_trackingPosition.y/=IR_CAMERA_HEIGHT;
        }
    }
}



void TrackingManager::draw()
{
    this->drawCamera();
    this->drawTracking();
}


void TrackingManager::drawCamera()
{
    int guiWidth = AppManager::getInstance().getGuiManager().getWidth();
    float y = LayoutManager::MARGIN;
    float x = guiWidth + 2*LayoutManager::MARGIN;
    
    ofPushMatrix();
        ofTranslate( x , y );
        this->drawIrCamera();
        this->drawContourTracking();
    ofPopMatrix();
}


void TrackingManager::drawIrCamera()
{
    ofPushStyle();
        ofSetColor(255);
        ofRect(0, 0, IR_CAMERA_WIDTH + LayoutManager::PADDING*2, IR_CAMERA_HEIGHT + LayoutManager::PADDING*2);
        m_irFbo.draw(LayoutManager::PADDING,LayoutManager::PADDING);
    ofPopStyle();
}


void TrackingManager::drawContourTracking()
{
    ofPushMatrix();
        ofTranslate( LayoutManager::PADDING , LayoutManager::PADDING);
        m_contourFinder.draw();
    ofPopMatrix();
}

void TrackingManager::drawTracking()
{
    int guiWidth = AppManager::getInstance().getGuiManager().getWidth();
    float y = 2*LayoutManager::MARGIN + IR_CAMERA_HEIGHT + LayoutManager::PADDING*2;
    float x = guiWidth + 2*LayoutManager::MARGIN;
    
    ofPushMatrix();
    ofPushStyle();
        ofTranslate( x , y );
        ofSetColor(255);
        ofRect(0, 0, IR_CAMERA_WIDTH + LayoutManager::PADDING*2, IR_CAMERA_HEIGHT + LayoutManager::PADDING*2);
        ofTranslate( LayoutManager::PADDING , LayoutManager::PADDING);
        ofSetColor(0);
        ofRect(0, 0, IR_CAMERA_WIDTH, IR_CAMERA_HEIGHT);
        this->drawTrackingPosition();
        ofTranslate( LayoutManager::PADDING , 2*LayoutManager::PADDING);
        this->drawTrackingPosText();
    ofPopStyle();
    ofPopMatrix();
}

void TrackingManager::drawTrackingPosition()
{
    float x = m_trackingPosition.x*IR_CAMERA_WIDTH;
    float y = m_trackingPosition.y*IR_CAMERA_HEIGHT;
    float radius = 10;
    
    ofPushStyle();
        ofSetColor(255);
        ofNoFill();
        ofCircle(x, y, radius);
        ofFill();
        ofCircle(x, y, radius/10);
    ofPopStyle();
}

void TrackingManager::drawTrackingPosText()
{
    
    ofPushStyle();
        ofSetColor(255);
        // display instructions
        string text = "X = " + ofToString(m_trackingPosition.x) + "\nY = " + ofToString(m_trackingPosition.y);
        ofDrawBitmapString(text, 0, 0);

    ofPopStyle();
    
   }
//--------------------------------------------------------------

void TrackingManager::onResetBackground(){
    m_background.reset();
}


void TrackingManager::onBrightnessChange(int & value){
    m_irBrightness = value;
    m_irBrightness = ofMap(value, 0, 255, 50000, 1000, true);
    //ofLogNotice() <<"TrackingManager::brightness << " << m_irBrightness ;
}

void TrackingManager::onThresholdChange(int & value){
    m_threshold = value;
    m_contourFinder.setThreshold(m_threshold);
}

void TrackingManager::onBackgroundThresholdChange(int & value){
    m_thresholdBackground= value;
    m_background.setThresholdValue(m_thresholdBackground);
}

void TrackingManager::onMinAreaChange(int & value){
    m_contourMinArea = value;
    m_contourFinder.setMinAreaRadius(m_contourMinArea);
}

void TrackingManager::onMaxAreaChange(int & value){
    m_contourMaxArea = value;
    m_contourFinder.setMaxAreaRadius(m_contourMaxArea);
}

void TrackingManager::onBackgroundSubstractionChange(bool & value)
{
    m_substractBackground = value;
}



