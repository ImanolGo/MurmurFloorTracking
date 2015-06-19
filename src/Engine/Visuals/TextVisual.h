/*
 *  TextVisual.h
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#pragma once


#include "Font.h"


#include "BasicVisual.h"


//=========================== class TextVisual ==============================
//============================================================================
/** \class TextVisual Visual.h
 *	\brief Represents an image visual
 *	\details The class uses the OF class ofImage to draw the image in a 3D world
 */

class TextVisual: public BasicVisual
{
    public:
    
        //! Constructor
        TextVisual();

        //! Constructor
        TextVisual(ofVec3f pos, float width, float height, bool centred = false);

        //! Destructor
        virtual ~TextVisual();

        //! Draws the text visual
        virtual void draw();

        //! Sets the text to be drawn
        virtual void setText(const std::string& text, const std::string& fontName, float fontSize, ofColor color = ofColor(0,0,0));

        //! Sets the text to be drawn
        virtual void setText(const std::string& text);

        //! Sets the height between lines
        virtual void  setLineHeight(float lineHeight);

        //! Sets the the width of the visual
        virtual void setWidth(float width);

        //! Gets the width of the current bounding box
        virtual float getWidth() const {return m_box.getWidth();}

        //! Gets the height of the current bounding box
        virtual float getHeight() {return m_box.getHeight();}

    private:

        Font              m_font;		 ///< Font class
        std::string       m_text;        ///< text to be rendered
        float             m_fontSize;    ///< saves the font size
        bool              m_centred;     ///< determines whether the visual is centred or not
        ofRectangle       m_box;         ///< the box surrounding the text
        ofVec3f           m_translation; ///< the point to which shift the origin
};

