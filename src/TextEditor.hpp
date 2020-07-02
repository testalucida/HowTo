/*
 * TextEditor.hpp
 *
 *  Created on: Jul 2, 2020
 *      Author: martin
 */

#ifndef TEXTEDITOR_HPP_
#define TEXTEDITOR_HPP_

#include "fltk_std.h"

class TextEditor : public Fl_Text_Editor {
public:
    TextEditor(int X,int Y,int W,int H) : Fl_Text_Editor(X,Y,W,H) {
        // Style table for the respective styles
        static const Fl_Text_Editor::Style_Table_Entry stable[] = {
           // FONT COLOR      FONT FACE   FONT SIZE
           // --------------- ----------- --------------
           {  FL_BLACK,       FL_HELVETICA, 14 }, // A - Black
		   {  FL_BLACK,       FL_HELVETICA_BOLD, 14 }, // B - Black bold
		   {  FL_BLACK,       FL_HELVETICA_ITALIC, 14 }, // C - Black italic
           {  FL_DARK_GREEN,  FL_HELVETICA, 14 }, // D - Green
		   {  FL_DARK_GREEN,  FL_HELVETICA_BOLD, 14 }, // E - Green bold
		   {  FL_DARK_GREEN,  FL_HELVETICA_ITALIC, 14 }, // F - Green italic
           {  FL_RED,         FL_HELVETICA, 14 }, // G - Red
		   {  FL_RED,         FL_HELVETICA_BOLD, 14 }, // H - Red bold
		   {  FL_RED,         FL_HELVETICA_ITALIC, 14 }, // I - Red italic
        };
        _tbuff = new Fl_Text_Buffer();    // text buffer
        _sbuff = new Fl_Text_Buffer();    // style buffer
        buffer(_tbuff);
        int stable_size = sizeof( stable)/sizeof(stable[0] );
        highlight_data( _sbuff, stable, stable_size, 'A', 0, 0 );
        _tbuff->add_modify_callback( modifyCallback_static, (void*)this );
    }

    // Modify callback handler
    void modifyCallback(int pos,        // position of update
                        int nInserted,  // number of inserted chars
                        int nDeleted,   // number of deleted chars
                        int,            // number of restyled chars (unused here)
                        const char* text)    // text deleted (unused here)
    {
    	fprintf( stderr, "modifyCallback: pos=%d, nInserted=%d, nDeleted=%d\n", pos, nInserted, nDeleted );
        // Nothing inserted or deleted? ==> select or unselect text
        if (nInserted == 0 && nDeleted == 0) {
        	fprintf( stderr, "insert_position: %d, selected: %d\n", insert_position(), _tbuff->selected() );
        	return;
        }

        // Characters inserted into tbuff?
        //     Insert same number of chars into style buffer..
		//
		if ( nInserted > 0 ) {
			char *style = new char[nInserted+1];  // temp buffer
			memset( style, _currentstyle, nInserted );          // init style to "A"s
			style[ nInserted ] = '\0';                // terminate string
			_sbuff->insert( pos, style );        // insert "A"s into style buffer
			delete[] style;                         // done with temp buffer..
		}

        // Characters deleted from tbuff?
        //    Delete same number of chars from style buffer..
        //
        if ( nDeleted > 0 ) {
            _sbuff->remove( pos, pos + nDeleted );
            return;     // nothing more to do; deleting won't affect our single char coloring
        }

        // Focus on characters inserted
        int start  = pos;
        int end    = pos + nInserted;
        fprintf( stderr, "\t\tinserted: start/end=%d/%d, text='%.*s'\n", start, end, (end-start), _tbuff->address(start) );

        // SIMPLE EXAMPLE:
        //     Color the digits 0-4 in green, 5-9 in red.
        //
        for ( int i=start; i<end; i++ ) {
            unsigned int c = _tbuff->char_at(i);
            if      ( strchr("01234", c) ) _sbuff->replace(i, i+1, "F");   // style 'F' (green)
            else if ( strchr("56789", c) ) _sbuff->replace(i, i+1, "H");   // style 'H' (red)
            else                           _sbuff->replace(i, i+1, "A");   // style 'A' (black)
        }
    }

    static void modifyCallback_static(int pos,                 // position of update
                                      int nInserted,           // number of inserted chars
                                      int nDeleted,            // number of deleted chars
                                      int nRestyled,           // number of restyled chars
                                      const char *deletedText, // text deleted
                                      void *cbarg) {           // callback data
        TextEditor *ted = (TextEditor*)cbarg;
        ted->modifyCallback(pos, nInserted, nDeleted, nRestyled, deletedText);
    }

    void onBold( bool on ) {
    	int start, end;
    	_tbuff->selection_position( &start, &end );
    	fprintf( stderr, "bold: %s, selection from %d to %d\n", on == true ? "on" : "off", start, end );
    }

    void onItalic( bool on ) {
    	fprintf( stderr, "italic: %s\n", on == true ? "on" : "off" );
	}

    static void onBold_static( Fl_Widget* w, void* userdata ) {
    	TextEditor* pThis = (TextEditor*) userdata;
    	Fl_Toggle_Button* btn = (Fl_Toggle_Button*)w;
    	pThis->onBold( (btn->value() == 1) );
    }

    static void onItalic_static( Fl_Widget* w, void* userdata ) {
    	TextEditor* pThis = (TextEditor*) userdata;
		Fl_Toggle_Button* btn = (Fl_Toggle_Button*)w;
		pThis->onItalic( (btn->value() == 1) );
	}

    void text( const char* val ) {
        _tbuff->text( val );
    }

private:
    Fl_Text_Buffer *_tbuff;      // text buffer
    Fl_Text_Buffer *_sbuff;      // style buffer
    char _currentstyle = 'A';
};



#endif /* TEXTEDITOR_HPP_ */
