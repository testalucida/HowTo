/*
 * Notepad.hpp
 *
 *  Created on: Jul 2, 2020
 *      Author: martin
 */

#ifndef NOTEPAD_HPP_
#define NOTEPAD_HPP_

#include "fltk_std.h"

class Notepad : public Fl_Group {
public:
	Notepad( int x, int y, int w, int h ) : Fl_Group( x, y, w, h ) {
		begin();
		end();
	}

private:

};


#endif /* NOTEPAD_HPP_ */
