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

#include <vector>
#include <memory>

//forward declarations
class Fl_Box;
class Fl_Button;
class Fl_Pixmap;

struct Rectangle {
    int X, Y, W, H;
};

namespace flx {
    
    class Flx_MdiChild;
    typedef std::shared_ptr< std::vector<Flx_MdiChild*> > MdiChildListPtr; 
    
    static int getWidgetIndex( const Fl_Widget &w )  {
        Fl_Group &p = *(w.parent());
        for( int i = 0, imax = p.children(); i < imax; i++ ) {
            Fl_Widget *pW = p.child( i );
            if( pW == &w ) {
                return i;
            }
        }
        return -1;
    }
    
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
    
    struct VetoableCloseAction {
        VetoableCloseAction() : canClose( true ) {}
        bool canClose;
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
     * Flx_MdiChild repräsentiert ein Dokument im Flx_MdiContainer.
     * Es besteht aus der Client-Area, in der beliebige Widgets angeordnet
     * sein können und der Flx_TitleBar.
     */
    class Flx_MdiChild : public Fl_Group {
    public:
        my::Signal<Flx_MdiChild, SystemBoxAction> signalSystemButtonClick;
    public:
        Flx_MdiChild( int x, int y, int w, int h, const char *pLbl = 0 );
        const Rectangle getClientAreaSize() const;
        void add( Fl_Widget & );
        void add( Fl_Widget * );
        int handle( int evt );
        void setTitleBarColors( Fl_Color focused, Fl_Color unfocused );
        void restoreSize();
        void resize( int x, int y, int w, int h );
    protected:
        void draw();
        
    private:
        void onSystemButtonClick( Flx_SystemButton &btn, SystemBoxAction & action );
        void drag();
        MousePosition checkResizeCursor();
        
        void resize();
        void resizeHorz( int dx );
        void resizeVert( int dy );
        bool canResizeVert( int dy ) const;
        bool canResizeHorz( int dx ) const;
        void rememberSize();
        void createTitleBar( int x, int y, int w, const char *pLbl = 0 );
        void createSystemButtons( int x, int y, int sideLen );
        void setTitleBarColorFocused( bool focused );
        
    private:
        MousePosition _mousePos;
        bool _dragging;
        int _x, _y;
        Fl_Group *_pTitleBar;
        Fl_Color _titleBarColorFocused;
        Fl_Color _titleBarColorUnfocused;
        Rectangle _recentSize; //Größe vor Maxi- oder Minimize
        Fl_Box *_pImageBox;
        Fl_Box *_pTitleBox;
        Fl_Group *_pSystemBox;
        Flx_SystemButton *_pMinBtn, *_pMaxBtn, *_pCloseBtn;
        Fl_Group *_pClientArea;
        Fl_Pixmap *_pIcon;
    };
    
    
    /**
     * Flx_MdiContainer verwaltet die Flx_MdiChild-Objekte.
     */
    class Flx_MdiContainer : public Fl_Group {
    public:
        my::Signal<Flx_MdiContainer, VetoableCloseAction> signalBeforeChildClose;
    public:
        Flx_MdiContainer( int x, int y, int w, int h );
        void draw();
        int handle( int evt );
        void add( Fl_Widget & );
        void add( Fl_Widget * );
        void remove( Fl_Widget & );
        void remove( int i );
        void remove( Fl_Widget * );
        void end();
        /**
         * Liefert die geöffneten MdiChildren in der Reihenfolge
         * absteigender Indices. D.h., das Child, das gerade den
         * Focus hat, ist das erste im Vector.
         * @return MdiChildListPtr ( vector<Flx_MdiChild*> )
         */
        const MdiChildListPtr getMdiChildren() const;
        /**
         * Ordnet die geöffneten MdiChildren von links nach rechts und
         * von oben nach unten an.
         * Die Größe der Children wird dabei so geändert, dass sie in in diesen
         * Container - bei gegebener Größe -  hineinpassen.
         */
        void arrangeChildren();
        /**
         * Setzt den Focus auf child
         * @param child
         */
        void setFocusTo( Flx_MdiChild &child );
    private:
        void onChildSystemButtonClick( Flx_MdiChild &child, SystemBoxAction &action );
        void connectToChildSignals( Flx_MdiChild &child );
        void disconnectFromChildSignals( Flx_MdiChild &child );
    };
}

#endif	/* FLX_MDI_INTERNAL_H */

