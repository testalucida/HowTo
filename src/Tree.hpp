/*
 * Tree.hpp
 *
 *  Created on: Jul 2, 2020
 *      Author: martin
 */

#ifndef TREE_HPP_
#define TREE_HPP_

#include "fltk_std.h"

class Tree : public Fl_Tree {
public:
	Tree( int x, int y, int w, int h ) : Fl_Tree( x, y, w, h ) {
		box( FL_FLAT_BOX );
	}
	~Tree() {}
};



#endif /* TREE_HPP_ */
