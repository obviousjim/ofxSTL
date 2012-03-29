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

#include "ofxSTLExporter.h"

ofxSTLExporter::ofxSTLExporter(){
	useASCIIFormat(false);
}

ofxSTLExporter::~ofxSTLExporter(){
	facets.clear();
}

void ofxSTLExporter::beginModel(string _modelName){
	modelName = _modelName;
	facets.clear();
}

void ofxSTLExporter::addTriangle(const ofPoint& vert1, const ofPoint& vert2, const ofPoint& vert3, const ofPoint& normal){	
	ofxSTLFacet facet;
	facet.vert1 = vert1;
	facet.vert2 = vert2;
	facet.vert3 = vert3;
	facet.normal = normal;
	facets.push_back(facet);
}

void ofxSTLExporter::saveModel(string fileName){
	if(bUseASCIIFormat){
		ofLog(OF_LOG_VERBOSE, "ofxSTLExporter::saveModel - saving ASCII format");
		asciiWriter.setModelName(modelName);
		asciiWriter.writeFile(fileName, facets);
	}else {
		ofLog(OF_LOG_VERBOSE, "ofxSTLExporter::saveModel - saving Binary format");
		binaryWriter.writeFile(fileName, facets);
	}
}

void ofxSTLExporter::useASCIIFormat(bool _bUseASCIIFormat){
	bUseASCIIFormat = _bUseASCIIFormat;
}





