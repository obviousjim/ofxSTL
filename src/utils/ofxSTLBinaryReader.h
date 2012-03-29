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


class ofxSTLBinaryReader: public ofxSTLReaderBase{
public:
	
	void readFile(ifstream& myFile, vector<ofxSTLFacet>& facets){
		unsigned int getPosition = 80;
		myFile.seekg(getPosition);
		unsigned int numFacets = 0;
		readObject(myFile, numFacets);
		getPosition+=4;
		facets.clear();
		for(; numFacets > 0; numFacets--){
			ofxSTLFacet facet;
			readFacet(myFile, facet);
			facets.push_back(facet);
		}
	}
	
	template<class T> void readObject(ifstream& myFile, T& object){
		int numBytes = sizeof(T);
		myFile.read((char*)&object, numBytes);
	}
	void readVector(ifstream& myFile, ofPoint& vec){
		readObject(myFile, vec.x);
		readObject(myFile, vec.y);
		readObject(myFile, vec.z);
	}
	void readFacet(ifstream& myFile, ofxSTLFacet& facet){
		readVector(myFile, facet.normal);
		readVector(myFile, facet.vert1);
		readVector(myFile, facet.vert2);
		readVector(myFile, facet.vert3);
		//in between each facet there's a 2 byte gap, so we advance the get position.
		unsigned int getPos = myFile.tellg();
		myFile.seekg(getPos+2);
	}
};