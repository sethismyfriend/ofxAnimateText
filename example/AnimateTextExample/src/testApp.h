#pragma once

#include "ofMain.h"
#include <fstream>
#include "takeManager.h"
#include "ofxAnimateTextManager.h"

class testApp : public ofBaseApp{
	
	public:
		
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		
	
	void loadPaths(bool circleA, ofDirectory dir);
		
	bool bFirst;
	string typeStr;
	ofTrueTypeFont	verdana30;
	int testNum;

	TakeManager * m_takeManager;
	ofxAnimateTextManager * animationsA;
	ofxAnimateTextManager * animationsB;

};

