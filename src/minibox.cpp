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

#include "minibox.h"

Minibox::~Minibox() {

}

void Minibox::init(const ofPoint &newPos, int colors[]) {
	//kludgy, will fix once I understand c++ better
	rgbColor color2 = {colors[0],colors[1],colors[2]};
	color = color2;
	
	speed = 12;
	width = 12;
	height = 12;
	pos.x = newPos.x + 32;
	pos.y = newPos.y + 32;
	active = true;
	
	if(rand()%2 == 0) {
		// move X
		if(rand()%2 == 0) {
			// move right
			moveX = speed;
			moveY = 0;
		} else {
			// move left
			moveX = -1*speed;
			moveY = 0;
		}
	} else {
		// move Y
		if(rand()%2 == 0) {
			// move up
			moveX = 0;
			moveY = -1*speed;
		} else {
			// move down
			moveX = 0;
			moveY = speed;
		}
	}
	
}

void Minibox::update() {
	if(active) {
		pos.x += moveX;
		pos.y += moveY;
		// recycle minibox if it leaves the screen area
		if(pos.x > 1024 || pos.x < 0 || pos.y > 768 || pos.y < 0) {
			active = false;
		}
	}
}

void Minibox::draw() {
	if(active) {
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetColor(color.r,color.g,color.b);
		ofNoFill();
		ofRect(pos.x, pos.y, width, height);
	}
}