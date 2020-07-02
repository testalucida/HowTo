/*
 * Controller.hpp
 *
 *  Created on: Jul 2, 2020
 *      Author: martin
 */

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "Tree.hpp"
#include <fltk_ext/FlxStatusBox.h>

class Controller {
public:
	Controller( Tree* tree, FlxStatusBox* status ) :
		_tree( tree ),
		_status( status )
	{

	}

	static void onNewNote_static( Fl_Widget*, void* data ) {

	}
	static void onSave_static( Fl_Widget*, void *data ) {

	}
	static void onFtp_static( Fl_Widget*, void *data ) {

	}
	static void onBold_static( Fl_Widget*, void *data ) {

	}
	static void onItalic_static( Fl_Widget*, void *data ) {

	}


private:
	Tree* _tree;
	FlxStatusBox* _status;
};


#endif /* CONTROLLER_HPP_ */
