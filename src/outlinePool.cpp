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

#include "outlinePool.h"

void OutlinePool::create(const ofPoint &pos, int colors[3]) {
	// find an available outline
	for (int i = 0; i < POOL_SIZE; i++) {
		if (!outlines[i].active) {
			outlines[i].init(pos, colors);
			return;
		}
	}
}