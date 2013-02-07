/*
 *  ofxAnimateTextPolyline.h
 *  fontsExample
 *
 *  Created by Seth Hunter on 12/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _ANIMATE_TEXT_POLYLINE
#define _ANIMATE_TEXT_POLYLINE

#include "ofMain.h"

//stores a library of Takes
class ofxAnimateTextPolyline : public ofPolyline {
public:
    ofxAnimateTextPolyline() : ofPolyline() { 
		isReserved = false; 
	}
    ~ofxAnimateTextPolyline() {    } ;
	
	ofxAnimateTextPolyline convertPolyline(ofPolyline _poly) {
		ofxAnimateTextPolyline temp;
		temp.addVertexes(_poly.getVertices());
		return temp;
	}
	
	bool getReserved() { return isReserved; }
	void setReserved() { isReserved = true; }
	void setUnReserved() { isReserved = false; }
	
	bool isReserved;
	
};

#endif
