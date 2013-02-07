/*
 *  ofxAnimateText.h
 *  fontsExample
 *
 *  Created by Seth Hunter on 12/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _ANIMATE_TEXT
#define _ANIMATE_TEXT

#include "ofMain.h"
#include "ofxAnimateTextPolyline.h"

//stores a library of Takes
class ofxAnimateText{
public:
    ofxAnimateText(string _textStr, ofxAnimateTextPolyline _path, int _glyphSpacing, string _fontPath, int _fontSize);
    ~ofxAnimateText();
	
	void smoothPath(float _resampleSpacing, int _smoothSize, float _smoothShape);
	void startAnimation() { isRunning = true; }
	void stopAnimation()  { isRunning = false; }
	void fadeAnimation(int _numFrames);
	void setStartPos(ofPoint _start) { startPosition = _start; }
	void setTextColor(ofColor _textColor) { textColor = _textColor; }
	void setIncrement(int _inc) { inc = _inc; }
	void setMaxAlpha(float _alpha) { maxAlpha = _alpha; }
	void update();
	void draw();
	void setDirection(bool _direction);	
	
	string textStr; 
	ofxAnimateTextPolyline path;
	vector <ofPoint> pathVerticies;
	ofTrueTypeFont	fontRenderer;
	int inc; //increment amount is equal to the speed of the animation
	bool animateDirection; //true is forward false is backwards
	float offsetAngle;
	ofPoint startPosition;
	ofColor textColor;
	bool isRunning; 
	int stopAtVert; 
	
	
protected:
	
	int showCount; 
	float offsetX;
	float offsetY;
	float fadeRatio;
	float maxAlpha;
	int verticiesCount;
	
	
};

#endif
