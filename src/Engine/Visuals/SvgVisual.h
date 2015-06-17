/*
 *  SvgVisual.h
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#pragma once


#include "ofxSvg.h"
#include "BasicVisual.h"


//=========================== class SvgVisual ==============================
//============================================================================
/** \class SvgVisual SvgVisual.h
 *	\brief Represents an SVG visual
 *	\details The class uses the OF addon class ofxSVG to draw a 2D svg images
 */

class SvgVisual: public BasicVisual
{

public:

    //! Constructor
    SvgVisual(const ofVec3f& pos, const string& resourceName, bool centred = false);

    //! Destructor
    virtual ~SvgVisual();

	//! Draws the text visual
	virtual void draw();

    //! Sets the texture to be binded to the quad
    virtual bool setResource(const string& resourceName);

    //! Set the width
    virtual void setWidth(float width, bool keepRatio=false);

    //! Set the height
    virtual void setHeight(float height, bool keepRatio=false);

    //! Get the original width
    float getOriginalWidth() const {return m_originalWidth;}

    //! Get the original height
    float getOriginalHeight() const {return m_originalHeight;}

    //! Returns the number of paths from the scalable vector graphic
    int getNumPath() const { return m_svg->getNumPath();}

    //!applies to whole shape
    void setFilled(bool t);
    void setFillColor(const ofColor& col);
    void setStrokeWidth(float f);
    void setStrokeColor(const ofColor &color);//use to set alpha too
    bool getFilled()const;
    const ofColor& getFillColor() const ;
    float getStrokeWidth()const;
    const ofColor& getStrokeColor()const;


    //!applies to specific path
    void setFilled(bool t,int path);
    void setFillColor(const ofColor& col,int path);//use to set alpha too
    void setStrokeWidth(float f,int path);
    void setStrokeColor(const ofColor &color,int path);//use to set alpha too
    bool getFilled(int path) const;
    const ofColor& getFillColor(int path)const;
    float getStrokeWidth(int path)const;
    const ofColor& getStrokeColor(int path)const;

protected:

    typedef vector <ofPath>     VectorPaths;

    ofPtr<ofxSVG>       m_svg;              ///< ofPtr to the SVG
    VectorPaths         m_paths;            ///< vector storing the paths
    ofVec3f             m_resizer;          ///< it deals with the resize of the picture
    bool                m_centred;          ///< defines if the visual should be centred or not
    float               m_originalWidth;    ///< stores the original width of the image in pixels
    float               m_originalHeight;   ///< stores the original height of the image in pixels

};

