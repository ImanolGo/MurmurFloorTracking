/*
 *  TextVisual.cpp
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */


#include "TextVisual.h"

TextVisual::TextVisual(ofVec3f pos, float width, float height, bool centred): BasicVisual(pos, width, height),m_fontSize(0), m_centred(centred)
{
    //Intentionally left empty
}

TextVisual::~TextVisual()
{
    //Intentionally left empty
}

void TextVisual::setText(const std::string& text, const std::string& fontName, float fontSize, ofColor color)
{
//    m_text = text;
//    m_fontSize = fontSize;
//
//    m_font.setup(fontName);
//
//    if(m_centred){
//        m_font.setTextBlockAlignment(ofxFontStash::OF_TEXT_ALIGN_CENTER);
//    }
//
//    //m_box =  m_font.getBBox(m_text,m_fontSize,m_position.x,m_position.y);
//    m_box = m_font.drawMultiLineColumn(m_text,m_fontSize,m_position.x,m_position.y,m_width, false);
//    m_color = color;
//    m_translation = m_position - m_box.getPosition();
//
//    if(m_centred){
//       m_translation.y -= m_box.getHeight()*0.5;
//    }
//

    m_text = text;
    m_fontSize = fontSize;

    m_font.setup(fontName,m_fontSize);

    if(m_centred){
        m_font.setTextBlockAlignment(Font::OF_TEXT_ALIGN_CENTER);
    }

    m_box =  m_font.drawMultiLineColumn(m_text,m_position.x,m_position.y,m_width);

    m_color = color;
    m_translation = m_position - m_box.getPosition();

    if(m_centred){
       m_translation.y -= m_box.getHeight()*0.5;
    }

}

void TextVisual::setText(const std::string& text)
{
//    m_text = text;
//
//    m_box = m_font.drawMultiLineColumn(m_text,m_fontSize,m_position.x,m_position.y,m_width, false);
//    //m_box =  m_font.getBBox(m_text,m_fontSize,m_position.x,m_position.y);
//
//    m_translation = m_position - m_box.getPosition();
//    if(m_centred){
//        m_translation.y -= m_box.getHeight()*0.5;
//    }

    m_text = text;

    m_box =  m_font.drawMultiLineColumn(m_text,m_position.x,m_position.y,m_width);

    m_translation = m_position - m_box.getPosition();
    if(m_centred){
        m_translation.y -= m_box.getHeight()*0.5;
    }

}

void  TextVisual::setWidth(float width)
{
    m_width = width;
    this->setText(m_text);
}

void  TextVisual::setLineHeight(float lineHeight)
{
     m_font.setLineHeight(lineHeight);
}

void TextVisual::draw()
{
    ofPushMatrix();
    //ofEnableAlphaBlending();

        ofScale(m_scale.x, m_scale.y);
        //ofSetColor(ofColor(255,255,10,200));
        //ofCircle(m_position, 3);
        //ofSetColor(ofColor(255,10,10,100));
        //if(m_centred){
            //ofRect(m_position.x - m_box.width*0.5, m_position.y - m_box.height*0.5, m_box.width, m_box.height);
        //}
        //else{
            //ofRect(m_position.x, m_position.y, m_box.width, m_box.height);
        //}

        ofSetColor(m_color);
        ofTranslate(m_translation.x, m_translation.y);
        //m_font.drawMultiLineColumn(m_text,m_fontSize, m_position.x,m_position.y,m_width);
        m_font.drawMultiLineColumn(m_text,m_position.x,m_position.y,m_width);

    //ofDisableAlphaBlending();
    ofPopMatrix();   // recall the pushed style
}
