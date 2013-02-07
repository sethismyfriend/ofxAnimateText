/*
 *  ofxAnimateTextManager.cpp
 *  fontsExample
 *
 *  Created by Seth Hunter on 12/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxAnimateTextManager.h"


ofxAnimateTextManager::ofxAnimateTextManager() {
	frameCount = 0;
	//ofSetDataPathRoot("../../../data");
	
}

ofxAnimateTextManager::~ofxAnimateTextManager() {
	
}
 


// Default values are included for all of them in case you don't specifiy them
void ofxAnimateTextManager::addTextAnimation(string _textStr, ofColor _color, float _maxAlpha, int _glyphSpacing, int _fontSize, 
					  string _fontPath, float _resampleAmount, float _smoothSize, float _smoothShape, bool _direction, float _x, float _y) {
	
	ofxAnimateTextPolyline * _path = getFreePath();
	
	if(_path != NULL) {
		ofxAnimateText * addme = new ofxAnimateText(_textStr, *_path, _glyphSpacing, _fontPath, _fontSize);
		addme->smoothPath(_resampleAmount, _smoothSize, _smoothShape);
		addme->setTextColor(_color);
		addme->setMaxAlpha(_maxAlpha);
		addme->setIncrement(_glyphSpacing);
		addme->setDirection(_direction);
		addme->startAnimation();
		if((_x != 0.0f) && (_y != 0.0f)) addme->setStartPos(ofPoint(_x,_y));
		animations.push_back(*addme);
	}
}




//returns a path which is not currently reserved

ofxAnimateTextPolyline * ofxAnimateTextManager::getFreePath() {
	
	vector < ofxAnimateTextPolyline * >  freePaths;
	for(int i=0; i<paths.size(); i++) {
		if(paths[i].getReserved() == false) freePaths.push_back(&paths[i]);
	}
	
	int freeSize = freePaths.size()-1;
	if(freeSize > 0) {
		int randPath = ofRandom(freeSize);
		return freePaths[randPath];
	}
	return NULL; 
}

void ofxAnimateTextManager::removeTextAnimation(int num) {
	
}


void ofxAnimateTextManager::draw() {
	for(int i=0; i<animations.size(); i++) {
		animations[i].draw();
	}
}

void ofxAnimateTextManager::update() {
	for(int i=0; i<animations.size(); i++) {
		animations[i].update();
	}
	frameCount++;
}


// loads normalized float position data of a polyline formatted as follows from text files:
/*
 0.5234375,0.23567708
 0.55078125,0.23958333
 0.5761719,0.24609375
*/

void ofxAnimateTextManager::loadPaths(string _directory) {
	
	int numFiles = dir.listDir(_directory);
	
	for(int i = 0; i < numFiles; i++){
		ifstream fin; //declare a file stream  
		fin.open( ofToDataPath(dir.getPath(i).c_str()).c_str() ); //issues with formatting to cstring.  		
		ofxAnimateTextPolyline tempLine;
		while(fin!=NULL) //as long as theres still text to be read  
		{  
			string str; //declare a str
			getline(fin, str); //get a line from the file, put it in the string  
			vector<string> tempSplit;
			tempSplit = ofSplitString(str, ",", true, true);
			if(tempSplit.size() == 2) {
				tempLine.addVertex(ofPoint( atof(tempSplit[0].c_str())*ofGetWindowWidth() , atof(tempSplit[1].c_str())*ofGetWindowHeight() ));
			}
		}
		paths.push_back(tempLine);
		//printf("adding a line from file %s \n",dir.getPath(i).c_str());
	}
}
