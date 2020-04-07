/* 
 * Copyright (c) 2009, Rui Madeira
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * http://creativecommons.org/licenses/LGPL/2.1/
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include "ofxSTLFacet.h"

class ofxSTLBase{
public:
	
	virtual void draw(){
		debugDraw();
	}
	
	void debugDraw(){
		glColor3f(1.0f, 1.0f, 1.0f);
		//drawWireFrame();
		//drawNormals();
		glColor3f(1.0f, 1.0f, 1.0f);
		drawFacets();
	}
	
	void drawFacets(){
		int numFacets = facets.size();
		glBegin(GL_TRIANGLES);
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			glNormal3f(f.normal.x, f.normal.y, f.normal.z);
			glVertex3f(f.vert1.x, f.vert1.y, f.vert1.z);
			glVertex3f(f.vert2.x, f.vert2.y, f.vert2.z);
			glVertex3f(f.vert3.x, f.vert3.y, f.vert3.z);
		}
		glEnd();
	}
	
	void drawNormals(){
		ofPoint centerPt;
		ofPoint targetPt;
		int numFacets = facets.size();
		float inv3 = 1.0f / 3.0f;
		glBegin(GL_LINES);
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			centerPt.x = (f.vert1.x + f.vert2.x + f.vert3.x) * inv3;
			centerPt.y = (f.vert1.y + f.vert2.y + f.vert3.y) * inv3;
			centerPt.z = (f.vert1.z + f.vert2.z + f.vert3.z) * inv3;
			targetPt = centerPt + (f.normal * 10);
			glVertex3f(centerPt.x, centerPt.y, centerPt.z);
			glVertex3f(targetPt.x, targetPt.y, targetPt.z);
		}
		glEnd();
	}
	
	void drawWireFrame(){
		int numFacets = facets.size();
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			glBegin(GL_LINE_STRIP);
			glNormal3f(f.normal.x, f.normal.y, f.normal.z);
			glVertex3f(f.vert1.x, f.vert1.y, f.vert1.z);
			glVertex3f(f.vert2.x, f.vert2.y, f.vert2.z);
			glVertex3f(f.vert3.x, f.vert3.y, f.vert3.z);
			glVertex3f(f.vert1.x, f.vert1.y, f.vert1.z);
			glEnd();
		}
	}
	
	vector<ofxSTLFacet>& getFacets(){
		return facets;
	}
	
	void normalizeModel(){
		ofPoint minPt, maxPt;
		int numFacets = facets.size();
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			if(minPt.x > f.vert1.x) minPt.x = f.vert1.x;
			if(minPt.x > f.vert2.x) minPt.x = f.vert2.x;
			if(minPt.x > f.vert3.x) minPt.x = f.vert3.x;
			if(maxPt.x < f.vert1.x) maxPt.x = f.vert1.x;
			if(maxPt.x < f.vert2.x) maxPt.x = f.vert2.x;
			if(maxPt.x < f.vert3.x) maxPt.x = f.vert3.x;
			if(minPt.y > f.vert1.y) minPt.y = f.vert1.y;
			if(minPt.y > f.vert2.y) minPt.y = f.vert2.y;
			if(minPt.y > f.vert3.y) minPt.y = f.vert3.y;
			if(maxPt.y < f.vert1.y) maxPt.y = f.vert1.y;
			if(maxPt.y < f.vert2.y) maxPt.y = f.vert2.y;
			if(maxPt.y < f.vert3.y) maxPt.y = f.vert3.y;
		}
		float distX = maxPt.x - minPt.x;
		float distY = maxPt.y - minPt.y;
		float invDist = 1.0f/MAX(distX, distY);
		scaleModel(invDist);
	}
	
	void scaleModel(float amount){
		int numFacets = facets.size();
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			f.vert1 *= amount;
			f.vert2 *= amount;
			f.vert3 *= amount;
		}
	}
	
	void rescaleModel(float size){
		normalizeModel();
		scaleModel(size);
	}
	
	void shiftModelPosition(const ofPoint& amount){
		int numFacets = facets.size();
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			f.vert1 += amount;
			f.vert2 += amount;
			f.vert3 += amount;
		}
	}
	
	void centerModel(ofPoint centerPos = ofPoint(0,0,0)){
		ofPoint modelCenter = getModelCenter();
		ofPoint shift =  centerPos - modelCenter;
		shiftModelPosition(shift);
	}
	
	ofPoint getModelCenter(){
		ofPoint pos;
		int numFacets = facets.size();
		for(int i=0; i<numFacets; i++){
			ofxSTLFacet& f = facets[i];
			pos += f.vert1;
			pos += f.vert2;
			pos += f.vert3;
		}
		pos /= (numFacets*3);
		return pos;
	}
	
protected:
	vector<ofxSTLFacet> facets;
	string modelName;
};
