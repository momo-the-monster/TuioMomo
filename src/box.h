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

#define		IDLE_COLOR		0x000000
#define		OVER_COLOR		0xFFFFFF
#define		MODE_SHRINK		0
#define		MODE_GROW		1
#define		MODE_STATIC		2

class Box {
	
public:
	struct rgbColor { int r; int g; int b;};
	
	ofPoint pos;					// position of box
	int boxSize;
	int innerWidth;					// inner box width, can be combined with height
	int innerHeight;				// inner box height
	rgbColor color;					// a random choice from the LSD palette
	int mode;						// the box is either growing, shrinking, or static
	int outlineAlpha;				// fades after a touch
	bool hasPoint;					// whether the box currently has a touch point
	int pointID;					// tracked touchID
	int index;						// which number in the grid this is
	ofEvent<int>onBoxTouched;		// dispatched to main app
	int waitBeforeFade;				// delay before fading out outline
	int fadeWaitTime;				// waitBeforeFade resets to this
	
	rgbColor colors[5];
	
	int growRate;
	int shrinkRate;
	int outlineFadeRate;
	
	// initialize all parameters
	void setup(int idx, ofPoint newPos, int newSize) {
		ofEnableAlphaBlending();
		index = idx;
		boxSize = newSize;
		innerWidth = 0;
		innerHeight = 0;
		pos = newPos;
		color = getRandomColor();
		hasPoint = false;
		pointID = NULL;
		mode = MODE_STATIC;
		outlineAlpha = 0;		// start invisible OR
	//	outlineAlpha = 255;		// start visible
		
		// parameters to play with
		growRate = 10;
		shrinkRate = 1;
		outlineFadeRate = 10;
		fadeWaitTime = 50;
		
		// there's got to be a better way to do this
		rgbColor color0 = {65,255,245};
		rgbColor color1 = {62,192,197};
		rgbColor color2 = {59,129,150};
		rgbColor color3 = {56,65,102};
		rgbColor color4 = {248,5,96};

		colors[0] = color0;
		colors[1] = color1;
		colors[2] = color2;
		colors[3] = color3;
		colors[4] = color4;
	}
	 
	rgbColor getRandomColor(){
		rgbColor newColor = colors[rand()%5];
		return newColor;
	}
	
	
	// grow, shrink, fade outline
	void update() {
		if(mode == MODE_GROW) {
			innerWidth += growRate;
			innerHeight += growRate;
			if(innerWidth >= boxSize) mode = MODE_STATIC;
		} else if(mode == MODE_SHRINK) {
			innerWidth -= shrinkRate;
			innerHeight -= shrinkRate;
			if(innerWidth <= 0) mode = MODE_STATIC;
		}
		if(waitBeforeFade > 0) {
			waitBeforeFade--;
		} else {
			if(outlineAlpha > 0) {
				outlineAlpha -= outlineFadeRate;
			}
		}
	}
	
	// draw outline and/or fill
	void draw() {
		// draw two outlines with alpha fade over time
		if(outlineAlpha > 0) {
			ofSetColor(color.r,color.g,color.b,outlineAlpha);
			ofNoFill();
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(pos.x + boxSize * 0.5, pos.y + boxSize * 0.5, boxSize, boxSize);
			
			// second outline, offset and not as opaque
			ofSetColor(color.r,color.g,color.b,outlineAlpha - 100);
			ofRect(pos.x + boxSize * 0.7, pos.y + boxSize * 0.7, boxSize, boxSize);
			
		}
		
		if(hasPoint || mode == MODE_SHRINK) {
			ofFill();
			ofSetColor(color.r,color.g,color.b,outlineAlpha);
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(pos.x + boxSize * 0.5, pos.y + boxSize * 0.5, innerWidth, innerHeight);
		}
	}
	
	// called from main after hitTest
	void onTouchDown(int touchId){
		activate(touchId);
	}
	
	// called from main after hitTest
	void onTouchUp() {
		hasPoint = false;
		pointID = NULL;
		mode = MODE_SHRINK;
	}
	
	// called from main, always
	void onTouchMoved(ofTouchEventArgs &touch){
		bool isOver = hitTest(touch.x, touch.y);
		
		// first check if a previous point has left
		if(hasPoint) {
			if(touch.id == pointID) {
				if(isOver) {
					// touch point is still here
				} else {
					// touch point has left
					hasPoint = false;
					mode = MODE_SHRINK;
				}
			}
		} else {
			// now check if a new point has entered
			if(isOver) {
				activate(touch.id);
				ofNotifyEvent(onBoxTouched, index);
			}
		}
	}
	
	// what to do when activated (touched, or new touch point entered)
	void activate(int touchId) {
		color = getRandomColor();
		mode = MODE_GROW;
		hasPoint = true;
		pointID = touchId;
		outlineAlpha = 255;
		waitBeforeFade = fadeWaitTime;
	}
	
	// am I touching you?
	bool hitTest(int tx, int ty) {
		return ((tx > pos.x) && (tx < pos.x + boxSize) && (ty > pos.y) && (ty < pos.y + boxSize));
	}
};