#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(54, 54, 54, 255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	//ofSetVerticalSync(true);
	ofSetFrameRate(30);
	
	m_takeManager = new TakeManager();
    m_takeManager->loadXMLFile("takes.xml", true);
	
	//old OF default is 96 - but this results in fonts looking larger than in other programs. 
	ofTrueTypeFont::setGlobalDpi(72);
	
	animationsA = new ofxAnimateTextManager();
	animationsA->loadPaths("circleA/");
	
	animationsB = new ofxAnimateTextManager();
	animationsB->loadPaths("circleB/");
	
	Take * take = m_takeManager->getTake(0);
	typeStr = take->transcript();
	
	//create multiple constructors (for offset or not etc)
	animationsA->addTextAnimation(typeStr, ofColor(255,100,100), 255, 8, 32, "verdana.ttf", 6.0f, 20.0f, 10.0f, true, 0.0f, 0.0f);
	animationsB->addTextAnimation(typeStr, ofColor(200,100,100), 255, 4, 20, "verdana.ttf", 6.0f, 20.0f, 10.0f, true, 0.0f, 0.0f);
	
	animationsA->addTextAnimation(typeStr, ofColor(200,100,200), 255, 4, 20, "verdana.ttf", 6.0f, 20.0f, 10.0f, false, 0.0f, 0.0f);
	animationsB->addTextAnimation(typeStr, ofColor(200,200,0), 255, 4, 20, "verdana.ttf", 6.0f, 20.0f, 10.0f, true, 0.0f, 0.0f);
	
	animationsA->addTextAnimation(typeStr, ofColor(150,250,100), 255, 4, 20, "verdana.ttf", 6.0f, 20.0f, 10.0f, false, 0.0f, 0.0f);
	animationsB->addTextAnimation(typeStr, ofColor(200,200,200), 255, 4, 20, "verdana.ttf", 6.0f, 20.0f, 10.0f, true, 0.0f, 0.0f);
	
}




//--------------------------------------------------------------
void testApp::update(){
	animationsA->update();
	animationsB->update();

}

//--------------------------------------------------------------
void testApp::draw(){
	animationsA->draw();
	animationsB->draw();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){ 

}


//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
