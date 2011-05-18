/*
 TuioPad http://www.tuio.org/
 An Open Source TUIO App for iOS based on OpenFrameworks
 (c) 2010 by Mehmet Akten <memo@memo.tv> and Martin Kaltenbrunner <modin@yuri.at>
 This file (c) 2011 Surya Buchwald <momodmonster@gmail.com>
 
 TuioPad is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TuioPad is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TuioPad.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "ofMain.h"

#include "MSAViewController.h"
#include "MSAFingerDrawerCPP.h"
#include "ofxMultiTouch.h"


class MMMFingerDrawerManager: virtual public MMMFingerGui {
	
	public:

	MSAFingerDrawerCPP	fingerDrawer[11];
	
	MMMFingerDrawerManager() {
	}
	
	virtual void setup() {
	}
	
	virtual void update() {
	}
	
	virtual void draw() {
		for(int i=0; i<11; i++) {
			fingerDrawer[i].draw();
		}
	}
	
	virtual void touchDown(ofTouchEventArgs &touch) {
		fingerDrawer[touch.id].touchDown(touch.x, touch.y);
	}
	
	virtual void touchMoved(ofTouchEventArgs &touch) {
		fingerDrawer[touch.id].touchMoved(touch.x, touch.y);
	}
	
	virtual void touchUp(ofTouchEventArgs &touch) {
		fingerDrawer[touch.id].touchUp();
	}
	
	virtual void touchDoubleTap(ofTouchEventArgs &touch) {
	}
	
};