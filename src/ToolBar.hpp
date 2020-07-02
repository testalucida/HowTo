/*
 * ToolBar.hpp
 *
 *  Created on: Jul 2, 2020
 *      Author: martin
 */

#ifndef TOOLBAR_HPP_
#define TOOLBAR_HPP_

#include "fltk_std.h"

struct Position {
	int x = 0;
	int y = 0;
};

class ToolBar: public Fl_Group {
public:
	// CTOR
	ToolBar( int X, int Y, int W ) : Fl_Group( X, Y, W, 34 ) {
		box( FL_FLAT_BOX );
		color( FL_DARK2 );
		end();
	}

	/**
	 * Adds a button to the right side of the most right button on the left side of the toolbar.
	 */
	void addButton( const char** xpm, bool toggle = false, const char *tooltip = 0,
			        Fl_Callback *cb=0, void *data=0 )
	{
		Position xy = getXYfromLeft();
		Fl_Button* b = createButton( xy.x, xy.y, toggle, tooltip, cb, data );

		Fl_Pixmap* img = new Fl_Pixmap( xpm );
		b->image( img );
		_mostRightLeftButton = b;
	}

	void addButton( const char* label, int labelfont, bool toggle = false, const char* tooltip = 0,
			        Fl_Callback* cb = 0, void* data = 0 )
	{
		Position xy = getXYfromLeft();
		Fl_Button* b = createButton( xy.x, xy.y, toggle, tooltip, cb, data );
		b->label( label );
		b->labelfont( labelfont );
		b->labelsize( _buttonsize - 8 );
		_mostRightLeftButton = b;
	}

	void addSpacing( int w ) {
		Position xy = getXYfromLeft();
		//Fl_Button* btn = createButton( xy.x, xy.y, false );
		Fl_Box* box = new Fl_Box( xy.x, xy.y, w, _buttonsize );
		box->box( FL_FLAT_BOX );
		box->color( FL_DARK2 );
		_mostRightLeftButton = box;
	}

private:
	Fl_Button* createButton( int x, int y, bool toggle, const char *tooltip = 0,
				Fl_Callback *cb = 0, void *data = 0 )
		{
			begin();
			Fl_Button* b = NULL;
			if( toggle ) {
				b = new Fl_Toggle_Button( x, y, _buttonsize, _buttonsize );
			} else {
				b = new Fl_Button( x, y, _buttonsize, _buttonsize );
			}
			b->box( FL_FLAT_BOX );    // buttons won't have 'edges'
			b->color( FL_DARK2 );
			b->clear_visible_focus();

			if ( tooltip )
				b->tooltip( tooltip );

			if ( cb )
				b->callback( cb, data );

			end();

			return b;
		}

	Position getXYfromLeft() const {
		Position pos;
		pos.x = _mostRightLeftButton ? _mostRightLeftButton->x() + _mostRightLeftButton->w() + _spacing_x
				                     : _spacing_x;
		pos.y = 1;
		return pos;
	}

private:
	Fl_Widget* _mostRightLeftButton = NULL;
	int _buttonsize = 32;
	int _spacing_x = 4;
};


#endif /* TOOLBAR_HPP_ */
