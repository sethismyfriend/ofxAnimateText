/*
 *  ofxAnimateText.cpp
 *  fontsExample
 *
 *  Created by Seth Hunter on 12/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxAnimateText.h"


ofxAnimateText::ofxAnimateText(string _textStr, ofxAnimateTextPolyline _path, int _glyphSpacing, string _fontPath, int _fontSize ) {
	
	textStr = _textStr;
	path = _path;
	pathVerticies = path.getVertices();
	stopAtVert = pathVerticies.size();
	fontRenderer.loadFont(_fontPath, _fontSize, true, true);
	fontRenderer.setLineHeight(_fontSize * 1.5);
	inc = _glyphSpacing;	
	setTextColor(ofColor(255,255,255,255));  //default to white
	showCount = 0;
	offsetX = 0.0f;
	offsetY = 0.0f;
	fadeRatio = .5f;
	maxAlpha = 255;
	offsetAngle = 0;
	isRunning = false;
	animateDirection = false; //by default I like to go from right to left along the given path so it's more readable. 
	verticiesCount = pathVerticies.size();
	startPosition = pathVerticies[0];
}
ofxAnimateText::~ofxAnimateText() {
	
}

void ofxAnimateText::setDirection(bool _direction) { 
	animateDirection = _direction;
	if(animateDirection) {
		verticiesCount = 0;
	} else {
		verticiesCount = stopAtVert;
	}
}


void ofxAnimateText::smoothPath(float _resampleSpacing, int _smoothSize, float _smoothShape) {
	
	path.close();
	ofPolyline resampled = path.getResampledBySpacing(_resampleSpacing);
	ofPolyline smoothed = resampled.getSmoothed(_smoothSize, _smoothShape);	
	path = path.convertPolyline(smoothed);
	
	pathVerticies = path.getVertices();
	verticiesCount = pathVerticies.size();
	stopAtVert = pathVerticies.size();
	startPosition = pathVerticies[0];
}

void ofxAnimateText::fadeAnimation(int _numFrames) {
	//TODO
	//if(verticiesCount - _numFrames > 0) stopAtVert =
}

void ofxAnimateText::update() {
	if(animateDirection) {
		verticiesCount++;
	} else {
		verticiesCount--;
	}
}

void ofxAnimateText::draw() {
	//path.draw();
	for(int i=0; i<showCount; i++) {
		
		ofRectangle	bounds = fontRenderer.getStringBoundingBox(textStr.substr(i,1), 0, 0);
		bool drawIt = true;
		ofPushMatrix();
		
		ofPoint target;
		ofPoint prevTarget;
		
		int vertIndex = verticiesCount + inc*(i);
		
		//if we haven't reached the last spot
		if(vertIndex > 0) {
			//pick a target and a previous point
			if(vertIndex < stopAtVert) {
				target = pathVerticies[vertIndex];
				if(verticiesCount + inc*(i)  != 0) {
					prevTarget = pathVerticies[vertIndex-1];
				} else {
					prevTarget = target;
				}
			} else { 
				target = pathVerticies[stopAtVert-1];
				prevTarget = pathVerticies[stopAtVert-2];
				drawIt = false;
			}
			
			//this is to allow you to move the whole thing around or reposition it at the start
			ofPoint offsetPos = pathVerticies[0] - startPosition;
			
			if(i==1) printf("offsetPos  x= %f  y = %f \n",offsetPos.x,offsetPos.y);
			
			ofTranslate(target.x-offsetPos.x, target.y-offsetPos.y, 0);
						
			//calculate the angle
			float angle = atan2(target.y-prevTarget.y,target.x-prevTarget.x);
			float deg = ofRadToDeg(angle);

			ofRotateZ(deg);
			
			if(drawIt) {
				float alphaCalc;
				if(animateDirection) {
					alphaCalc = 1 - ((float)(verticiesCount) + (float)inc*(i))/(float)stopAtVert;
				} else { 
					alphaCalc = ((float)verticiesCount + (float)inc*(i))/(float)stopAtVert;
				}
				alphaCalc = (pow(alphaCalc,fadeRatio)) * maxAlpha;
				ofEnableAlphaBlending();
				ofSetColor(textColor.r, textColor.g, textColor.b ,alphaCalc);
				fontRenderer.drawString(textStr.substr(i,1), -bounds.width/2, bounds.height/2 );
				ofDisableAlphaBlending();
			}
		}
		ofPopMatrix();
	}
	
	if(showCount < textStr.length())  showCount++;
}


