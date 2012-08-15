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

#include "ofxSTLImporter.h"

ofxSTLImporter::ofxSTLImporter(){
	
}

ofxSTLImporter::~ofxSTLImporter(){
	facets.clear();
}

void ofxSTLImporter::loadSTL(string path){
	ifstream myFile;
	myFile.open(path.c_str(), ios::in);
	if(!myFile.is_open()){
		ofLog(OF_LOG_ERROR, "ofxSTLImporter::loadSTL - could not open file");
		return;
	}
	if(isASCII(myFile)){
		ofLog(OF_LOG_VERBOSE, "ofxSTLImporter::loadSTL - loading ASCII file");
		asciiReader.readFile(myFile, facets);
		modelName = asciiReader.getModelName();
	}else{
		ofLog(OF_LOG_VERBOSE, "ofxSTLImporter::loadSTL - loading Binary file");
		binaryReader.readFile(myFile, facets);
		modelName = "";
	}
}

string ofxSTLImporter::getModelName(){
	return modelName;	
}

bool ofxSTLImporter::isASCII(ifstream& myFile){
	myFile.seekg(ios::beg);
	char fileHeader[5];
	myFile.read(fileHeader, 5);
	string solidWord("solid");
	bool bWordsMatch = true;
	for(int i=0; i<5; i++){
		if(fileHeader[i] != solidWord[i]){
			bWordsMatch = false;
			break;
		}
	}
	return bWordsMatch;
}

