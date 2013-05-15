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

class ofxSTLBinaryWriter: public ofxSTLWriterBase{
public:
	void writeFile(string fileName, const vector<ofxSTLFacet>& facets){
		std::fstream myFile(fileName.c_str(), std::ios::out | std::ios::binary);
		writeHeader(myFile);
		unsigned int numFacets = (unsigned int)facets.size();
		writeObject(myFile, numFacets);
		for(int i=0; i<numFacets; i++){
			writeFacet(myFile, facets[i]);
		}
		myFile.close();		
	}
	
protected:
	template<class T> void writeObject(std::fstream& myFile, T& object){
		int numBytes = sizeof(T);
		myFile.write((char*)&object, numBytes);
	}
	void writeVector(std::fstream& myFile, const ofPoint& vec){
		writeObject(myFile, vec.x);
		writeObject(myFile, vec.y);
		writeObject(myFile, vec.z);
	}
	void writeFacet(std::fstream& myFile, const ofxSTLFacet& facet){
		writeVector(myFile, facet.normal);
		writeVector(myFile, facet.vert1);
		writeVector(myFile, facet.vert2);
		writeVector(myFile, facet.vert3);
		short zero = 0;
		writeObject(myFile, zero);
	}
	void writeHeader(std::fstream& myFile){
		char header[80];
		memset(header, ' ', 80);
		myFile.write(header, 80);
	}
};