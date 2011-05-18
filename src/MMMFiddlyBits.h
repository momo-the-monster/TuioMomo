/*
 FiddlyBits
 Visualizer for Multitouch Interfaces
 (c) 2010 by Surya Buchwald <momodmonster@gmail.com>
 
 FiddlyBits is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 FiddlyBits is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with FiddlyBits.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "box.h"
#include "outline.h"
#include "outlinePool.h"
#include "miniboxPool.h"
#include "MMMFingerGui.h"

#define BOX_SIZE				64

typedef struct {

	float 	x;
	float 	y;
	bool 	bBeingDragged;
	bool 	bOver;
	float 	radius;
	
}	draggableVertex;


class MMMFiddlyBits :virtual public MMMFingerGui {
	
public:
	virtual void setup();
	virtual void update();
	virtual void draw();
	
	virtual void touchDown(ofTouchEventArgs &touch);
	virtual void touchMoved(ofTouchEventArgs &touch);
	virtual void touchUp(ofTouchEventArgs &touch);
	virtual void touchDoubleTap(ofTouchEventArgs &touch);
	void onBoxTouched(int &index);
	
	int num_boxes;
	Box boxes[192];
	OutlinePool outlinePool;
	MiniboxPool miniboxPool;
	float appIphoneScale;
	string		nextMessage;
	struct rgbColor { int r; int g; int b;};

};