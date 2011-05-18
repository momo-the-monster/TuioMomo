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

#include "outline.h"

Outline::~Outline() {
	//dtor
}

void Outline::init(const ofPoint &newPos, int colors[]) {
	//kludgy, will fix once I understand c++ better
	rgbColor color2 = {colors[0],colors[1],colors[2]};
	color = color2;
	
	ofEnableAlphaBlending();
	width = 0;
	height = 0;
	alpha = 255;
	pos.x = newPos.x + 32;
	pos.y = newPos.y + 32;
	active = true;
	growSpeed = 8;
	fadeSpeed = 4;
}

void Outline::update() {
	if(active) {
		width += growSpeed;
		height += growSpeed;
		alpha -= fadeSpeed;
		if(width > 2048) active = false;
	}
}

void Outline::draw() {
	if(active) {
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetColor(color.r,color.g,color.b,alpha);
		ofNoFill();
		ofRect(pos.x, pos.y, width, height);
	}
}