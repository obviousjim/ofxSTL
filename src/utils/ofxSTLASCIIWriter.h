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

#include "ofxSTLWriterBase.h"

class ofxSTLASCIIWriter: public ofxSTLWriterBase{
public:
	ofxSTLASCIIWriter(){
		modelName = "";
	}
	
	void writeFile(string fileName, const vector<ofxSTLFacet>& facets){
		string modelInfo = "solid " + modelName + "\n";
		int numFacets = facets.size();
		for(int i=0; i<numFacets; i++){
			modelInfo += "facet normal " + ofToString(facets[i].normal.x) + " " + ofToString(facets[i].normal.y) + " " + ofToString(facets[i].normal.z) + "\n";
			modelInfo += "  outer loop\n";
			modelInfo += "    vertex " + ofToString(facets[i].vert1.x) + " " + ofToString(facets[i].vert1.y) + " " + ofToString(facets[i].vert1.z) + "\n";
			modelInfo += "    vertex " + ofToString(facets[i].vert2.x) + " " + ofToString(facets[i].vert2.y) + " " + ofToString(facets[i].vert2.z) + "\n";
			modelInfo += "    vertex " + ofToString(facets[i].vert3.x) + " " + ofToString(facets[i].vert3.y) + " " + ofToString(facets[i].vert3.z) + "\n";
			modelInfo += "  endloop\n";
			modelInfo += "endfacet\n";
		}
		modelInfo += "end solid " + modelName;
		std::ofstream myFile;
		myFile.open(fileName.c_str());
		myFile << modelInfo.c_str();
		myFile.close();		
	}
	
	void setModelName(string _modelName = ""){
		modelName = _modelName;
	}

protected:
	string modelName;
};