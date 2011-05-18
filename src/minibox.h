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

class Minibox {
public:
	struct rgbColor { int r; int g; int b;};
	ofPoint pos;
	int width;
	int height;
	int moveX;
	int moveY;
	int speed;
	rgbColor color;
	bool active;
	
	Minibox(){
	    active = false;
	}
	virtual ~Minibox();
	
	void init(const ofPoint &newPos, int * colors);
	void update();
	void draw();
	
};