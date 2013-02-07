/*
 *  ofxAnimateTextManager.h
 *  fontsExample
 *
 *  Created by Seth Hunter on 12/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _ANIMATE_TEXT_MANAGER
#define _ANIMATE_TEXT_MANAGER

#include "ofxAnimateText.h"
#include "ofxAnimateTextPolyline.h"
#include "ofMain.h"

//stores a library of Takes
class ofxAnimateTextManager{
public:
    ofxAnimateTextManager();
    ~ofxAnimateTextManager();
	
	// Default values are included for all of them in case you don't specifiy them
	void addTextAnimation(string _textStr, ofColor _color=ofColor(255,255,255), float _maxAlpha=255, int _glyphSpacing=4, int _fontSize=24, 
						  string _fontPath="verdana.ttf", float _resampleAmount=6.0f, float _smoothSize=20.0f, float _smoothShape=10.0f, 
						  bool _direction=false, float _x=0.0f, float _y=0.0f);
	
	
	void removeTextAnimation(int num);
	void loadPaths(string _directory);
	void draw();
	void update();
		
	
protected:
   
	int frameCount;
	vector <ofxAnimateText> animations;
	vector <ofxAnimateTextPolyline> paths;
	ofxAnimateTextPolyline * getFreePath();
	ofDirectory dir;

	
};

#endif
