#pragma once

//#include "ofMain.h"
#include "svgtiny.h"
#include "ofPath.h"
#include "ofTypes.h"

class ofxSVG {
	public:

        ofxSVG();

	    ~ofxSVG();

		float getWidth() const {
			return width;
		}
		float getHeight() const {
			return height;
		}
		void load(string path);
		void draw();

		int getNumPath(){
			return paths.size();
		}
		ofPath & getPathAt(int n){
			return paths[n];
		}

        //!applies to whole shape
        void setFilled(bool t);
        void setFillColor(const ofColor& col);
        void setStrokeWidth(float f);
        void setStrokeColor(const ofColor &color);//use to set alpha too
        bool getFilled() const {return m_isFilled;}
        const ofColor& getFillColor() const {return m_fillColor;}
        float getStrokeWidth()const {return m_strokeWidth;}
        const ofColor& getStrokeColor()const {return m_strokeColor;}


        //!applies to specific path
        void setFilled(bool t,int path);
        void setFillColor(const ofColor& col,int path);//use to set alpha too
        void setStrokeWidth(float f,int path);
        void setStrokeColor(const ofColor &color,int path);//use to set alpha too
        bool getFilled(int path) const;
        const ofColor& getFillColor(int path)const;
        float getStrokeWidth(int path)const;
        const ofColor& getStrokeColor(int path)const;

	private:

		float width, height;

		vector <ofPath> paths;

		void setupDiagram(struct svgtiny_diagram * diagram);
		void setupShape(struct svgtiny_shape * shape, ofPath & path);

        bool     m_isFilled;
        ofColor  m_fillColor;
        ofColor  m_strokeColor;
        float    m_strokeWidth;

};
