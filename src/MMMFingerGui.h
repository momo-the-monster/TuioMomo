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

class MMMFingerGui {
public:
		virtual void setup() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		
		virtual void touchDown(ofTouchEventArgs &touch) = 0;
		virtual void touchMoved(ofTouchEventArgs &touch) = 0;
		virtual void touchUp(ofTouchEventArgs &touch) = 0;
		virtual void touchDoubleTap(ofTouchEventArgs &touch) = 0;
 
};