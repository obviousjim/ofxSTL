#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST);
	light.pointLight(0, 0, 255, 0, 0, 500);
	reflections.directionalLight(100, 100, 100, 0, -1, 0);
	reflections.specular(200, 200, 200);
	ofxMaterialSpecular(250, 250, 250);
	ofxMaterialShininess(30);
	ofxSetSmoothLight(true);
	
	ofSetLogLevel(OF_LOG_VERBOSE);
	bSaveModel = false;
	
	//some random model created with ofxMarchingCubes... :)
	stlImporter.loadSTL(ofToDataPath("testASCII.stl"));
	//stlImporter.loadSTL("testBin.stl");
}

//--------------------------------------------------------------
void testApp::update(){
	if(bSaveModel){
		bSaveModel = false;
		vector<ofxSTLFacet>& facets = stlImporter.getFacets();
		int numFacets = facets.size();
		stlExporter.beginModel("some model");
		for(int i=0; i<numFacets; i++){
			stlExporter.addTriangle(facets[i].vert1, facets[i].vert2, facets[i].vert3, facets[i].normal);
		}
		stlExporter.useASCIIFormat(true); //export as ASCII (default is binary)
		stlExporter.saveModel(ofToDataPath("testASCII.stl"));
		stlExporter.useASCIIFormat(false); //export as binary
		stlExporter.saveModel(ofToDataPath("testBin.stl"));
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofxLightsOn();
	ofPoint center(ofGetWidth()*0.5f, ofGetHeight()*0.5f, -1000);
	float counter = (float)ofGetFrameNum();
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glRotatef(counter*0.05f, 1.0f, 0.0f, 0.0f);
	glRotatef(counter*0.1f, 0.0f, 1.0f, 0.0f);
	stlImporter.draw();
	glPopMatrix();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == ' ')bSaveModel = true;
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

