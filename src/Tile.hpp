/*
 * Tile.hpp
 *
 *  Created on: Jul 2, 2020
 *      Author: martin
 */

#ifndef TILE_HPP_
#define TILE_HPP_

#include "fltk_std.h"

class Tile : public Fl_Tile {
public:
	Tile( int x, int y, int w, int h ) : Fl_Tile( x, y, w, h ) {
	}
	~Tile() {}

};



#endif /* TILE_HPP_ */
