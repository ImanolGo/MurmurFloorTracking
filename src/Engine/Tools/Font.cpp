/*
 *  Font.h
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#include <iostream>
#include "Font.h"

/* *********************************************************************** */

Font::Font():m_lineHeight(1.0),m_batchDrawing(false),m_textBlockAlignment(OF_TEXT_ALIGN_LEFT)
{
	//Intentionally left empty
}

Font::~Font()
{
	//Intentionally left empty
}

bool Font::setup( string fontFile, float fontSize, float lineHeightPercent)
{

    m_trueTypeFont.setEncoding(OF_ENCODING_UTF8);

	m_lineHeight = lineHeightPercent;

	bool bAntiAliased=true;
    bool bFullCharacterSet=true;
    bool makeContours=false;
    float simplifyAmt=0.3;
    int dpi=0.0;

	if(m_trueTypeFont.loadFont(fontFile,fontSize,bAntiAliased,bFullCharacterSet,makeContours,simplifyAmt,dpi)){
	    //ofLogNotice() << "Font::setup-> font loaded " << fontFile << " with size " << fontSize;
        return true;
	}
	else{
         ofLogNotice() << "Font::setup-> Can't load font " << fontFile << "!!";
        return false;
	}

    return false;
}


void Font::draw( string text, float x, float y)
{
    if(!m_trueTypeFont.isLoaded()){
        return;
    }

    m_trueTypeFont.drawString(text,x,y);
}

void Font::drawMultiLine( string text, float x, float y)
{
    if(!m_trueTypeFont.isLoaded()){
        return;
    }

    stringstream ss(text);
    string s;
    int line = 0;
    float yy = y;
    int fontSize = m_trueTypeFont.getSize();

    while ( getline(ss, s, '\n') ) {
        //cout << s << endl;
        yy = y + fontSize * m_lineHeight* FONT_HEIGHT_MULT * line;
        m_trueTypeFont.drawString(s.c_str(),x,yy);
        line ++;
    }
}

ofRectangle Font::drawMultiLineColumn( string text, float x, float y, float columnWidth)
{

    ofRectangle totalArea = ofRectangle(x,y,0,0);

    if(!m_trueTypeFont.isLoaded()){
        return totalArea;
    }

    int fontSize = m_trueTypeFont.getSize();

	vector<string>splitLines;
    ofRectangle r;

    ofUTF8Ptr start = ofUTF8::beginPtr(text);
    ofUTF8Ptr iter = ofUTF8::beginPtr(text);
    ofUTF8Ptr lineStart = iter;
    ofUTF8Ptr lastSpace;
    ofUTF8Ptr stop = ofUTF8::endPtr(text);

    string thisLine = "";
    bool foundSpace = false;
    bool foundNewLine = false;
    while(iter < stop) {

        ofUniChar c = ofUTF8::getNext(iter); // get the next unichar and iterate
        if ( ofUnicode::isSpace(c) ){
            foundSpace = true;
            lastSpace = iter;
        }
        if ( ofTextConverter::toUTF8(c) == "\n" ){
            foundNewLine = true;
        }
        thisLine += ofTextConverter::toUTF8(c);
        r = m_trueTypeFont.getStringBoundingBox(thisLine.c_str(), 0,0);

        if ( r.width > columnWidth || foundNewLine ) { //we went too far, lets jump back to our closest space
            if(foundNewLine){
                if (thisLine == "\n"){ //if the whole line is only \n, replace for space to avoid weird things
                    thisLine = " ";
                }else{	//otherwise remove the "\n"
                    thisLine = thisLine.substr(0, thisLine.length()-1);
                }
                splitLines.push_back(thisLine);

            }else{
                if (foundSpace){
                    //cout << "## foundSpace! (" << thisLine << ")" << endl;
                    string finalLine = walkAndFill(lineStart, iter, lastSpace);
                    splitLines.push_back(finalLine);
                    iter = lastSpace;
                }else{
                    //cout << "## no Space! (" << thisLine << ")" << endl;
                    splitLines.push_back(thisLine);
                }
            }
            //reset counter vars
            lineStart = iter;
            r.width = 0;
            thisLine = "";
            foundSpace = foundNewLine = false;
        }else{
            if(iter == stop){ //last line!
                string finalLine = walkAndFill(lineStart, iter, stop);
                splitLines.push_back(finalLine);
                break;
            }
        }
    }

    for(int i = 0; i < splitLines.size(); i++)
    {
        float yy = m_lineHeight * FONT_HEIGHT_MULT * fontSize * i;

        ofPushMatrix();

            if(m_textBlockAlignment == OF_TEXT_ALIGN_LEFT)
            {
                ofTranslate(0, yy);
            }

            else if(m_textBlockAlignment == OF_TEXT_ALIGN_CENTER)
            {
                ofRectangle r = m_trueTypeFont.getStringBoundingBox(splitLines[i], 0,0);
                ofTranslate(-r.getWidth()*0.5, yy);
            }
            else if(m_textBlockAlignment == OF_TEXT_ALIGN_RIGHT)
            {
                ofRectangle r = m_trueTypeFont.getStringBoundingBox(splitLines[i], 0,0);
                ofTranslate(-r.getWidth(), yy);
            }
            else
            {
                ofTranslate(0, yy);
            }

            m_trueTypeFont.drawString(splitLines[i],x,y);

        ofPopMatrix();

        totalArea = totalArea.getUnion( m_trueTypeFont.getStringBoundingBox(splitLines[i], x, y + yy));
    }

	return totalArea;
}

string Font::walkAndFill(ofUTF8Ptr begin, ofUTF8Ptr & iter, ofUTF8Ptr end){

	string finalLine = "";
	ofUTF8Ptr i = begin;
	while (i < iter) { // re-fill the finalLine from the begining to the last Space
		finalLine += ofTextConverter::toUTF8(ofUTF8::getNext(i)); // get the next unichar and iterate
		if(i == end){
			break;
		}
	}
	return finalLine;
}


void Font::setLineHeight(float percent){
	m_lineHeight = percent;
}
