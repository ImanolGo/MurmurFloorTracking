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

const string TrackingManager::m_irFragmentShader =
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
const float TrackingManager::SCALE = 1.35;
const int TrackingManager::TRACKING_PERSISTANCY = 5*30;
const int TrackingManager::LEARNING_TIME = 10*30;


TrackingManager::TrackingManager(): Manager(), m_irBrightness(6535.0), m_threshold(80), m_contourMinArea(50), m_contourMaxArea(1000), m_thresholdBackground(10), m_substractBackground(true),m_cropLeft(0), m_cropRight(0), m_cropTop(0), m_cropBottom(0)
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
    this->setupFbos();
}

void TrackingManager::setupContourTracking()
{
    
    m_contourFinder.setMinAreaRadius(m_contourMinArea);
    m_contourFinder.setMaxAreaRadius(m_contourMaxArea);
    m_contourFinder.setTargetColor(ofColor::white, TRACK_COLOR_RGB);
    m_contourFinder.setThreshold(m_threshold);
    //m_contourFinder.getTracker().setPersistence(TRACKING_PERSISTANCY);
    //m_contourFinder.setSimplify(true);
    //m_contourFinder.getTracker().setSmoothingRate(0.6);
    //m_contourFinder.setSortBySize(true);
    //m_contourFinder.setFindHoles(false);
    
    //m_contourFinder.getTracker().setMaximumDistance(32);
    
    //m_background.setLearningTime(LEARNING_TIME);
    m_background.setThresholdValue(m_threshold);
    
    m_background.reset();
}

void TrackingManager::setupKinectCamera()
{
    m_irShader.setupShaderFromSource(GL_FRAGMENT_SHADER, m_irFragmentShader);
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

void TrackingManager::setupFbos()
{
    m_findBlobsFbo.allocate(IR_CAMERA_WIDTH, IR_CAMERA_HEIGHT, GL_RGB);
    m_findBlobsFbo.begin();
        ofClear(0,0,0,0);
    m_findBlobsFbo.end();
    
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
            
            ofPushStyle();
            ofSetColor(150);
            ofFill();
            ofRect(0,0,m_cropLeft,IR_CAMERA_HEIGHT);
            ofRect(0,0,IR_CAMERA_WIDTH,m_cropTop);
            ofRect(IR_CAMERA_WIDTH-m_cropRight,0, m_cropRight, IR_CAMERA_HEIGHT);
            ofRect(0,IR_CAMERA_HEIGHT-m_cropBottom,IR_CAMERA_WIDTH,m_cropBottom);
            ofPopStyle();
            
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
            //m_background.reset();
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
    
    AppManager::getInstance().getGuiManager().setGuiTrackingPos(m_trackingPosition);
    //AppManager::getInstance().getOscManager().sendPosition(m_trackingPosition);
}



void TrackingManager::draw()
{
    this->drawTracking();
}


void TrackingManager::drawTracking()
{
    ofVec2f pos = this->getPosition();
    ofPushMatrix();
        ofTranslate( pos.x , pos.y );
        ofScale(SCALE,SCALE);
        this->drawIrCamera();
        this->drawContourTracking();
        this->drawTrackingPosition();
    
    //m_findBlobsFbo.draw(0,0);
    ofPopMatrix();
}


void TrackingManager::drawIrCamera()
{
    ofPushStyle();
        ofSetColor(255);
        ofRect(0, 0, IR_CAMERA_WIDTH + LayoutManager::PADDING*2, IR_CAMERA_HEIGHT + LayoutManager::PADDING*2);
        m_irFbo.draw(LayoutManager::PADDING,LayoutManager::PADDING);
    
    ofPopStyle();
    
    //m_findBlobsFbo.draw(0,0);

}


void TrackingManager::drawContourTracking()
{
    ofPushMatrix();
        ofNoFill();
        ofTranslate( LayoutManager::PADDING , LayoutManager::PADDING);
        for(int i = 0; i < m_contourFinder.size(); i++)
        {
            auto p = m_contourFinder.getPolyline(i).getSmoothed(4, 1);
            p.simplify(2);
            p.draw();
            
            ofRect(toOf(m_contourFinder.getBoundingRect(i)));
        }

    ofPopMatrix();
}


void TrackingManager::drawTrackingPosition()
{
    float x = m_trackingPosition.x*IR_CAMERA_WIDTH + LayoutManager::PADDING;
    float y = m_trackingPosition.y*IR_CAMERA_HEIGHT + LayoutManager::PADDING;
    float radius = 8;
    
    ofPushMatrix();
    ofPushStyle();
        ofSetColor(255,255,0);
        ofNoFill();
        ofCircle(x, y, radius);
        ofFill();
        ofCircle(x, y, radius/8);
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------

void TrackingManager::onResetBackground(){
    m_background.reset();
}


void TrackingManager::onBrightnessChange(int & value){
    m_irBrightness = ofMap(value, 0, 255, 50000, 1000, true);
    //ofLogNotice() <<"TrackingManager::brightness << " << m_irBrightness ;
}

void TrackingManager::onThresholdChange(int & value){
    m_threshold = ofClamp(value,0,255);
    m_contourFinder.setThreshold(m_threshold);
}

void TrackingManager::onBackgroundThresholdChange(int & value){
    m_thresholdBackground = ofClamp(value,0,30);
    m_background.setThresholdValue(m_thresholdBackground);
}


void TrackingManager::onMinAreaChange(int & value){
    m_contourMinArea = ofClamp(value,0,100);
    m_contourFinder.setMinAreaRadius(m_contourMinArea);
}

void TrackingManager::onMaxAreaChange(int & value){
    m_contourMaxArea = ofClamp(value,0,500);
    m_contourFinder.setMaxAreaRadius(m_contourMaxArea);
}

void TrackingManager::onBackgroundSubstractionChange(bool & value)
{
    m_substractBackground = value;
}

void TrackingManager::onTrackingPosChange(ofVec2f & value)
{
    m_trackingPosition = value;
    AppManager::getInstance().getOscManager().sendPosition(m_trackingPosition);
}


int TrackingManager::getHeight() const
{
    return (IR_CAMERA_HEIGHT + LayoutManager::PADDING*2)*SCALE;
}

int TrackingManager::getWidth() const
{
    return (IR_CAMERA_HEIGHT + LayoutManager::PADDING*2)*SCALE;
}

ofVec2f TrackingManager::getPosition() const
{
    ofVec2f pos;
    pos.y = LayoutManager::MARGIN;
    pos.x = GuiManager::GUI_WIDTH + 2*LayoutManager::MARGIN;
    return pos;
}



