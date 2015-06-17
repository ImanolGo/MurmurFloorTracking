#include "ofxSvg.h"
#include "ofConstants.h"

ofxSVG::ofxSVG(): m_strokeWidth(0),m_isFilled(false)
{

}


ofxSVG::~ofxSVG(){
	paths.clear();
}

void ofxSVG::load(string path){
	path = ofToDataPath(path);

	if(path.compare("") == 0){
		ofLogError("ofxSVG") << "load(): path does not exist: \"" << path << "\"";
		return;
	}

	ofBuffer buffer = ofBufferFromFile(path);
	size_t size = buffer.size();

	struct svgtiny_diagram * diagram = svgtiny_create();
	svgtiny_code code = svgtiny_parse(diagram, buffer.getText().c_str(), size, path.c_str(), 0, 0);

	if(code != svgtiny_OK){
		string msg;
		switch(code){
		 case svgtiny_OUT_OF_MEMORY:
			 msg = "svgtiny_OUT_OF_MEMORY";
			 break;

		 case svgtiny_LIBXML_ERROR:
			 msg = "svgtiny_LIBXML_ERROR";
			 break;

		 case svgtiny_NOT_SVG:
			 msg = "svgtiny_NOT_SVG";
			 break;

		 case svgtiny_SVG_ERROR:
			 msg = "svgtiny_SVG_ERROR: line " + ofToString(diagram->error_line) + ": " + diagram->error_message;
			 break;

		 default:
			 msg = "unknown svgtiny_code " + ofToString(code);
			 break;
		}
		ofLogError("ofxSVG") << "load(): couldn't parse \"" << path << "\": " << msg;
	}

	setupDiagram(diagram);

	svgtiny_free(diagram);
}

void ofxSVG::draw(){
	for(int i = 0; i < (int)paths.size(); i++){
		paths[i].draw();
	}
}


void ofxSVG::setupDiagram(struct svgtiny_diagram * diagram){

	width = diagram->width;
	height = diagram->height;

	for(int i = 0; i < (int)diagram->shape_count; i++){
		if(diagram->shape[i].path){
			paths.push_back(ofPath());
			setupShape(&diagram->shape[i],paths.back());
		}else if(diagram->shape[i].text){
			ofLogWarning("ofxSVG") << "setupDiagram(): text: not implemented yet";
		}
	}
}

void ofxSVG::setupShape(struct svgtiny_shape * shape, ofPath & path){
	float * p = shape->path;

	path.setFilled(false);

	if(shape->fill != svgtiny_TRANSPARENT){
		path.setFilled(true);
		path.setFillHexColor(shape->fill);
		path.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    }

	if(shape->stroke != svgtiny_TRANSPARENT){
		path.setStrokeWidth(shape->stroke_width);
		path.setStrokeHexColor(shape->stroke);
	}

	for(int i = 0; i < (int)shape->path_length;){
		if(p[i] == svgtiny_PATH_MOVE){
			path.moveTo(p[i + 1], p[i + 2]);
			i += 3;
		}
		else if(p[i] == svgtiny_PATH_CLOSE){
			path.close();

			i += 1;
		}
		else if(p[i] == svgtiny_PATH_LINE){
			path.lineTo(p[i + 1], p[i + 2]);
			i += 3;
		}
		else if(p[i] == svgtiny_PATH_BEZIER){
			path.bezierTo(p[i + 1], p[i + 2],
						   p[i + 3], p[i + 4],
						   p[i + 5], p[i + 6]);
			i += 7;
		}
		else{
			ofLogError("ofxSVG") << "setupShape(): SVG parse error";
			i += 1;
		}
	}
}

/*
 These affect the whole document
 */
void ofxSVG::setFilled(bool t)
{
    for(int i = 0; i < (int)paths.size(); i++){
            paths[i].setFilled(t);
    }

    m_isFilled = t;
}

void ofxSVG::setFilled(bool t,int path)
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return;
    }

    paths[path].setFilled(t);

}

bool ofxSVG::getFilled(int path) const
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return false;
    }

    return paths[path].isFilled();

}



void ofxSVG::setFillColor(const ofColor &color)
{
    for(int i = 0; i < (int)paths.size(); i++){
        paths[i].setFillColor(color);
    }

    m_fillColor = color;
}


void ofxSVG::setFillColor(const ofColor& col,int path)
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return;
    }

    paths[path].setFillColor(col);
}

const ofColor& ofxSVG::getFillColor(int path) const
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return m_fillColor;
    }

    return paths[path].getFillColor();
}


void ofxSVG::setStrokeWidth(float f)
{
    for(int i = 0; i < (int)paths.size(); i++){
        paths[i].setStrokeWidth(f);
    }

    m_strokeWidth = f;
}

void ofxSVG::setStrokeWidth(float f,int path)
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return;
    }

    paths[path].setStrokeWidth(f);

}

float ofxSVG::getStrokeWidth(int path) const
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return 0;
    }

    return paths[path].getStrokeWidth();
}

void ofxSVG::setStrokeColor(const ofColor& col)
{
    for(int i = 0; i < (int)paths.size(); i++){
        paths[i].setStrokeColor(col);
    }

    m_strokeColor = col;
}

void ofxSVG::setStrokeColor(const ofColor& col,int path)
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return;
    }

    paths[path].setStrokeColor(col);
}

const ofColor& ofxSVG::getStrokeColor(int path) const
{
    if(path > paths.size()-1){
        ofLogWarning()<<"WARNING: Tried to modify ofxSVG path out of index - "<< path;
        return m_strokeColor;
    }

    return paths[path].getStrokeColor();
}

