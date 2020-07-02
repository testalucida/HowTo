
#include "fltk_std.h"
//#include "global.h"
#include "ToolBar.hpp"
#include "xpm.h"
#include "Tile.hpp"
#include "Tree.hpp"
#include "TextEditor.hpp"
#include "Controller.hpp"
#include <fltk_ext/FlxStatusBox.h>

using namespace std;


int main() {
	int w = 1000;
	int h = 780;
	int statusH = 25;
	int treeW = 200;

	Fl_Double_Window *win =
			new Fl_Double_Window( 150, 0, w, h, "How To" );

	ToolBar* tb = new ToolBar( 0, 0, w );

	int tileY = tb->y() + tb->h();
	int tileH = h - tileY - statusH;
	Tile* tile = new Tile( 0, tileY, w, tileH );
	tile->begin();
		Tree* tree = new Tree( tile->x(), tileY, treeW, tile->h() );
		int ted1X = tree->x() + tree->w();
		int ted1W = (w - treeW)/2;
		int tedH = tile->h();
		TextEditor* ted1 = new TextEditor( ted1X, tileY, ted1W, tedH );
		int ted2X = ted1->x() + ted1->w();
		int ted2W = w - ted2X;
		TextEditor* ted2 = new TextEditor( ted2X, tileY, ted2W, tedH );
	tile->end();

	FlxStatusBox* status = new FlxStatusBox( 0, h-statusH, w, statusH );
	status->setStatusText( "Ready." );

	Controller ctrl( tree, status );

	tb->addButton( new_xpm, false, "New note", ctrl.onNewNote_static, &ctrl );
	tb->addButton( save_xpm, false, "Save note locally", ctrl.onSave_static, &ctrl );
	tb->addButton( ftp_xpm, false, "Save to server", ctrl.onFtp_static, &ctrl );
	tb->addSpacing( 10 );
	tb->addButton( "B", FL_HELVETICA_BOLD, true, "Bold Font", ctrl.onBold_static, &ctrl );
	tb->addButton( "I", FL_HELVETICA_ITALIC, true, "Italic Font", ctrl.onItalic_static, &ctrl );

	win->resizable( win );
	win->end();
	win->show();

	int rc = Fl::run();

	return rc;
}

/**
 * todo
 *
 */
