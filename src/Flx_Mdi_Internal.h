/* 
 * File:   Flx_Mdi_Internal.h
 * Author: max
 *
 * Created on 15. Februar 2015, 10:56
 */

#ifndef FLX_MDI_INTERNAL_H
#define	FLX_MDI_INTERNAL_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>

#include <my/Signal.hpp>
#include <my/CharBuffer.h>

//forward declarations
class Fl_Box;
class Fl_Button;

namespace flx {
    
    /** MousePosition where cursor changes */
    enum MousePosition {
        POS_ANY = 0,
        POS_N = 1,
        POS_E = 2,
        POS_S = 4,
        POS_W = 8,
        POS_NE = 3,
        POS_SE = 6,
        POS_SW = 12,
        POS_NW = 9
    };

    /** cursor at position */
    static Fl_Cursor cursors[] = {
        FL_CURSOR_DEFAULT, //0
        FL_CURSOR_NS, //1
        FL_CURSOR_WE, //2
        FL_CURSOR_NE, //3
        FL_CURSOR_NS, //4
        FL_CURSOR_DEFAULT, //5 -- Dummy1
        FL_CURSOR_NW, //6
        FL_CURSOR_DEFAULT, //7 -- Dummy1
        FL_CURSOR_WE, //8
        FL_CURSOR_NW, //9
        FL_CURSOR_DEFAULT, //10 -- Dummy1
        FL_CURSOR_DEFAULT, //11 -- Dummy2
        FL_CURSOR_NE //12
    };
    
    enum SystemBoxButtonType {
        SYSTEMBUTTON_CLOSE,
        SYSTEMBUTTON_MINI,
        SYSTEMBUTTON_MAXI
    };
    
    struct SystemBoxAction {
    public:
        SystemBoxButtonType actionButton;
    };
    
    
    /**
     * SystemButton 
     */
    class Flx_SystemButton : public Fl_Button {
    public:
        my::Signal< Flx_SystemButton, SystemBoxAction > signalSystemButtonClick;
    public:
        Flx_SystemButton( int x, int y, int w, int h, SystemBoxButtonType type, Fl_Color color );
        static void staticOnClick( Fl_Widget *pW, void *pUserdata );
        void onClick();
    private:
        SystemBoxButtonType _type;
    };
    
    
    /**
     * Systembox auf der rechten Seite der Flx_TitleBar.
     * Enthält 3 Flx_SystemButtons.
     */
    class Flx_SystemBox : public Fl_Group {
        my::Signal< Flx_SystemBox, SystemBoxAction > signalSystemButtonClicked;
    public:
        Flx_SystemBox( int x, int y, int w, int h );
        void draw();
        int handle( int evt );
    private:
        /**
         * Callback-Methode, die nach dem Drücken eines Systembox-
         * Button gerufen wird
         * @param btn: der gedrückte Button
         * @param 
         */
        //void onControlButton( Flx_Button &btn, ActionParm & );
    private:
        Flx_SystemButton *_pMinBtn, *_pMaxBtn, *_pCloseBtn;
    };
    
    
    /**
     * Jedes Flx_MdiChild hat eine Flx_TitleBar, bestehend aus einem
     * Icon, dem Titel und einer Flx_SystemBox.
     */
    class Flx_TitleBar : public Fl_Group {
    public:
        my::Signal< Flx_TitleBar, SystemBoxAction > signalSystemButtonClicked;
    public:
        Flx_TitleBar( int x, int y, int w, int h, const char *pLbl = 0 );
        bool isMouseOverSystemBox() const;
        bool isMouseOverTitle() const;
        void draw();
        int handle( int evt );
    private:
        /**
         * Callback-Methode, die gerufen wird, wenn ein System-Button
         * gedrückt wird
         * @param systemBox
         * @param action
         */
        void onSystemBoxAction( Flx_SystemBox &systemBox, SystemBoxAction &action );
    private:
        my::CharBuffer _title;
        Fl_Box *_pImageBox;
        Fl_Box *_pTitleBox;
        Flx_SystemBox *_pSystemBox;
    };
    
    
    /**
     * Flx_MdiChild repräsentiert ein Dokument im Flx_MdiContainer.
     * Es besteht aus der Client-Area, in der beliebige Widgets angeordnet
     * sein können und der Flx_TitleBar.
     */
    class Flx_MdiChild : public Fl_Group {
    public:
        Flx_MdiChild( int x, int y, int w, int h, const char *pLbl = 0 );
        void draw();
        int handle( int evt );
    private:
        void onSystemButtonClick( Flx_SystemButton &btn, SystemBoxAction & action );
        void drag();
        MousePosition checkResizeCursor();
        void resize();
        void resizeHorz( int dx );
        void resizeVert( int dy );
        bool canResizeVert( int dy ) const;
        bool canResizeHorz( int dx ) const;
        void createTitleBar( int x, int y, int w, const char *pLbl = 0 );
        void createSystemButtons( int x, int y, int sideLen );
    private:
        MousePosition _mousePos;
        bool _dragging;
        int _x, _y;
        Fl_Group *_pTitleBar;
        Fl_Color _titleBarColor;
        Fl_Box *_pImageBox;
        Fl_Box *_pTitleBox;
        Fl_Group *_pSystemBox;
        Flx_SystemButton *_pMinBtn, *_pMaxBtn, *_pCloseBtn;
        Fl_Group *_pClientArea;
    };
    
    
    /**
     * Flx_MdiContainer verwaltet die Flx_MdiChild-Objekte.
     */
    class Flx_MdiContainer : public Fl_Group {
    public:
        Flx_MdiContainer( int x, int y, int w, int h );
        void draw();
        int handle( int evt );
    private:
    };
}

#endif	/* FLX_MDI_INTERNAL_H */

