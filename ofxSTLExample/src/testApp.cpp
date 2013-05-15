#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	ofBackgroundHex(0x222222);
	ofSetVerticalSync(true);

    glEnable(GL_DEPTH_TEST);
   
    light.enable();
    
    // Move off default colors
    light.setDiffuseColor(ofColor::fromHsb(180, 70, 75));
    light.setAmbientColor(ofColor::fromHsb(180, 150, 200));
    
	ofSetLogLevel(OF_LOG_VERBOSE);
	bSaveModel = false;	

	stlImporter.loadSTL(ofToDataPath("OF_logo.stl"));
	//stlImporter.loadSTL("testBin.stl");
    
    drawMode = facets;

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
 
    camera.begin();
    
        // Enlarge our model
        stlImporter.rescaleModel(600);

        ofRotateY(-35); // beauty angle
    
        if(drawMode == normals) {
            stlImporter.drawNormals();
        }
        else if(drawMode == wire) {
             stlImporter.drawWireFrame();
        }
        else if(drawMode == facets) {
             stlImporter.drawFacets();
        }
   
    camera.end();
    
    //
    
    ofSetHexColor(0xe0d6ff);

    stringstream showKey;
    
    showKey << "Draw Options \n\n"
    << "1: Draw Normals \n"
    << "2: Draw WireFrame \n"
    << "3: Draw Facets";
    
    ofDrawBitmapString(showKey.str(), 20,20);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch (key) {
            
        case ' ':
            bSaveModel = true;
            break;
            
        case '1':
            drawMode = normals;
            break;
            
        case '2':
            drawMode = wire;
            break;
            
        case '3':
            drawMode = facets;
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }
    
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

