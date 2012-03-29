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

#include "ofMain.h"
#include <iostream>
#include <fstream>
#include "ofxSTLBase.h"
#include "ofxSTLFacet.h"

#include "utils/ofxSTLBinaryWriter.h"
#include "utils/ofxSTLASCIIWriter.h"

class ofxSTLExporter: public ofxSTLBase{
public:
	ofxSTLExporter();
	virtual ~ofxSTLExporter();
	void beginModel(string _solidName = "");
	void addTriangle(const ofPoint& vert1, const ofPoint& vert2, const ofPoint& vert3, const ofPoint& normal);
	void saveModel(string fileName);
	void useASCIIFormat(bool _bUseASCIIFormat = false); //default is binary format, use this if you want to save in ASCI format
protected:
	ofxSTLBinaryWriter binaryWriter;
	ofxSTLASCIIWriter asciiWriter;
	bool bUseASCIIFormat;
};
