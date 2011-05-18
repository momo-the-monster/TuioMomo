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

#include "MMMFiddlyBits.h"
#include "MSAViewController.h"
#include "box.h"

//--------------------------------------------------------------
void MMMFiddlyBits::setup(){	
	ofEnableAlphaBlending();
	
	int cols = ceil(ofGetScreenWidth() / BOX_SIZE);
	int rows = ceil(ofGetScreenHeight() / BOX_SIZE);
	
	num_boxes = rows * cols;
	
	int index = 0;
	for (int col = 0; col < cols; col++) {
		for (int row=0; row < rows; row++) {
			int newX = (col % cols) * BOX_SIZE;	
			int newY = (row % rows) * BOX_SIZE;
			boxes[index].setup(index, ofPoint(newX, newY, 0),BOX_SIZE);
			ofAddListener(boxes[index].onBoxTouched, this, &MMMFiddlyBits::onBoxTouched);
			index++;
		}
	}
}


//--------------------------------------------------------------
void MMMFiddlyBits::update(){
	for(int i = 0; i < num_boxes; i++) {
		boxes[i].update();
	}
	outlinePool.update();
	miniboxPool.update();
}

//--------------------------------------------------------------
void MMMFiddlyBits::draw(){
	ofFill();
	ofSetColor(0, 0, 0);
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	
	for(int i = 0; i < num_boxes; i++) {
		boxes[i].draw();
	}
	outlinePool.draw();
	miniboxPool.draw();
}

//--------------------------------------------------------------
void MMMFiddlyBits::touchDown(ofTouchEventArgs &touch){
	for(int i = 0; i < num_boxes; i++) {
		// test for finger-box collision
		if(boxes[i].hitTest(touch.x, touch.y)) {
			// notify box
			boxes[i].onTouchDown(touch.id);
			// create animated outline
			int colors[3] = {boxes[i].color.r, boxes[i].color.g, boxes[i].color.b};
			outlinePool.create(ofPoint(boxes[i].pos.x, boxes[i].pos.y), colors);
			miniboxPool.create(ofPoint(boxes[i].pos.x, boxes[i].pos.y), colors);
		}
	}
}

//--------------------------------------------------------------
void MMMFiddlyBits::touchMoved(ofTouchEventArgs &touch){
	for(int i = 0; i < num_boxes; i++) {
		boxes[i].onTouchMoved(touch);
	}
}

//--------------------------------------------------------------
void MMMFiddlyBits::touchUp(ofTouchEventArgs &touch){
	for(int i = 0; i < num_boxes; i++) {
		if(boxes[i].hitTest(touch.x, touch.y)) {
			boxes[i].onTouchUp();
		}
	}
}
//--------------------------------------------------------------
void MMMFiddlyBits::touchDoubleTap(ofTouchEventArgs &touch){
	
}

void MMMFiddlyBits::onBoxTouched(int &index){
	int colors[3] = {boxes[index].color.r, boxes[index].color.g, boxes[index].color.b};
	outlinePool.create(ofPoint(boxes[index].pos.x, boxes[index].pos.y), colors);
	miniboxPool.create(ofPoint(boxes[index].pos.x, boxes[index].pos.y), colors);
}