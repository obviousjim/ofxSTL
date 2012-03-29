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

#include "ofxSTLReaderBase.h"

class ofxSTLASCIIReader: public ofxSTLReaderBase{
public:
	ofxSTLASCIIReader(){
		lineIndex = 0;
		modelName = "";
	}
	
	void readFile(ifstream& myFile, vector<ofxSTLFacet>& facets){
		lineIndex = 0;
		unsigned int fileSize;
		string line;
		vector<string>lines;
		while(!myFile.eof()){
			getline(myFile, line);
			lines.push_back(line);
		}
		lineIndex = 0;
		int numLines = lines.size();
		facets.clear();
		readModelName(lines);
		while(lineIndex < numLines){
			vector<string> elements = ofSplitString(lines[lineIndex], " ");
			if(elements[0].compare("endsolid") == 0)break;
			else if(elements[0].compare("facet") == 0){
				ofxSTLFacet facet;
				readFacet(lines, facet);
				facets.push_back(facet);
			}
			lineIndex++;
		}
		/*
		for(int i=0; i<facets.size(); i++){
			printf("normal x:%f, y:%f, z:%f\n", facets[i].normal.x, facets[i].normal.y, facets[i].normal.z);
			printf("vert1 x:%f, y:%f, z:%f\n", facets[i].vert1.x, facets[i].vert1.y, facets[i].vert1.z);
			printf("vert2 x:%f, y:%f, z:%f\n", facets[i].vert2.x, facets[i].vert2.y, facets[i].vert2.z);
			printf("vert3 x:%f, y:%f, z:%f\n", facets[i].vert3.x, facets[i].vert3.y, facets[i].vert3.z);
		}*/
	}
	
	void readModelName(const vector<string>& lines){
		lineIndex = 0;
		unsigned int nameBegin = lines[0].find_first_of(" ") + 1;
		modelName = lines[0].substr(nameBegin);
		lineIndex += 1;
	}
	
	void readFacet(const vector<string>& lines, ofxSTLFacet& facet){
		readNormal(lines, facet.normal);
		lineIndex += 1;
		readVertex(lines, facet.vert1);
		readVertex(lines, facet.vert2);
		readVertex(lines, facet.vert3);
	}
	
	void readVertex(const vector<string>& lines, ofPoint& vec){
		vector<string> elements = ofSplitString(lines[lineIndex], " ");
		int numElements = elements.size();
		if(numElements != 4){
			ofLog(OF_LOG_ERROR, "ofxSTLImport - problem reading vertex line");
			assert(0);
		}
		vec.x = ofToFloat(elements[1]);
		vec.y = ofToFloat(elements[2]);
		vec.z = ofToFloat(elements[3]);
		lineIndex+=1;
	}
	
	void readNormal(const vector<string>& lines, ofPoint& vec){
		vector<string> elements = ofSplitString(lines[lineIndex], " ");
		int numElements = elements.size();
		if(numElements != 5){
			ofLog(OF_LOG_ERROR, "ofxSTLImporter - problem reading normal line");
			assert(0);
		}
		vec.x = ofToFloat(elements[2]);
		vec.y = ofToFloat(elements[3]);
		vec.z = ofToFloat(elements[4]);
		lineIndex+=1;
	}
	
	string getModelName(){
		return modelName;
	}
protected:
	unsigned int lineIndex;
	string modelName;
};