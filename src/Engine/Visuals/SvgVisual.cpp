/*
 *  SvgVisual.cpp
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#include "AppManager.h"
#include "ResourceManager.h"

#include "SvgVisual.h"

SvgVisual::SvgVisual(const ofVec3f& pos, const string& resourceName,bool centred):
    BasicVisual(pos, 0, 0), m_centred(centred), m_resizer(1,1,1)
{
    this->setResource(resourceName);
}

SvgVisual::~SvgVisual()
{
    //Intentionally left empty
}

bool SvgVisual::setResource(const string& resourceName)
{
    m_svg = AppManager::getInstance().getResourceManager().getSVG(resourceName);

    m_width = m_originalWidth = m_svg->getWidth();
    m_height = m_originalHeight = m_svg->getHeight();
    m_resizer.x = m_width/m_originalWidth;
    m_resizer.y = m_height/m_originalHeight;

    return true;
}


void SvgVisual::draw()
{
    ofPushMatrix();

        ofTranslate(m_position);

        ofScale(m_scale.x, m_scale.y);

        if(m_centred){
            ofTranslate(-m_width*0.5,-m_height*0.5);
        }


        ofRotateX(m_rotation.x);
        ofRotateY(m_rotation.y);

        //ofRect(0,0,m_width,m_height);

        ofScale(m_resizer.x,m_resizer.y);

        ofSetColor(m_color);

        m_svg->draw();


    ofPopMatrix();
}

void SvgVisual::setWidth(float width, bool keepRatio)
{
    m_width = width;
    if(keepRatio){
        float ratio = m_originalWidth/m_originalHeight;
        m_height = m_width/ratio;
    }

    m_resizer.x = m_width/m_originalWidth;
    m_resizer.y = m_height/m_originalHeight;
}

void SvgVisual::setHeight(float height, bool keepRatio)
{
    m_height = height;
    if(keepRatio){
        float ratio = m_originalWidth/m_originalHeight;
        m_width = m_height*ratio;
    }

    m_resizer.x = m_width/m_originalWidth;
    m_resizer.y = m_height/m_originalHeight;
}


void SvgVisual::setFilled(bool t)
{
    m_svg->setFilled(t);
}

void SvgVisual::setFilled(bool t,int path)
{
    m_svg->setFilled(t,path);

}

bool SvgVisual::getFilled(int path) const
{
    return m_svg->getFilled(path);
}

bool SvgVisual::getFilled() const
{
    return m_svg->getFilled();
}


void SvgVisual::setFillColor(const ofColor &color)
{
    m_svg->setFillColor(color);
}


void SvgVisual::setFillColor(const ofColor& col,int path)
{
    m_svg->setFillColor(col,path);
}

const ofColor& SvgVisual::getFillColor(int path) const
{
    return m_svg->getFillColor(path);
}

const ofColor& SvgVisual::getFillColor() const
{
    return m_svg->getFillColor();
}



void SvgVisual::setStrokeWidth(float f)
{
    m_svg->setStrokeWidth(f);
}

void SvgVisual::setStrokeWidth(float f,int path)
{
    m_svg->setStrokeWidth(f,path);

}

float SvgVisual::getStrokeWidth(int path) const
{
    return m_svg->getStrokeWidth(path);
}

float SvgVisual::getStrokeWidth() const
{
     return m_svg->getStrokeWidth();
}


void SvgVisual::setStrokeColor(const ofColor& col)
{
    m_svg->setStrokeColor(col);
}

void SvgVisual::setStrokeColor(const ofColor& col,int path)
{
     m_svg->setStrokeColor(col,path);
}

const ofColor& SvgVisual::getStrokeColor(int path) const
{
    return m_svg->getStrokeColor(path);
}

const ofColor& SvgVisual::getStrokeColor() const
{
    return m_svg->getStrokeColor();
}

