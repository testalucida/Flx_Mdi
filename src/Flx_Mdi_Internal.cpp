/* 
 * File:   Flx_Mdi_Internal.cpp
 * Author: max
 * 
 * Created on 15. Februar 2015, 10:56
 */

#include "Flx_Mdi_Internal.h"
#include "../images/mdi.xpm"

#include <my/Util.h>
#include <my/CharBuffer.h>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>


#include <cmath>

using namespace std;
using namespace my;

void log( const char *pMsg, Fl_Widget *p ) {
    CharBuffer msg( pMsg );
    msg.add( "%s" ).add( typeid( p ).name() );    
    Util::log( msg.get() );
}

void printBounds( Fl_Widget *p ) {
    Util::log( "Widget %s: x=%d, y=%d, w=%d, h=%d",
              p->label(), p->x(), p->y(), p->w(), p->h() );
}

namespace flx {
    
    ///////////////////////////////////////////////////////////
    ////////////  MdiChildException  ///////////////////////////////
    ///////////////////////////////////////////////////////////
    MdiChildException::MdiChildException(const char* pMsg) {
        _msg.add( pMsg );
    }
    

    ///////////////////////////////////////////////////////////
    ////////////  Flx_SystemButton  ///////////////////////////////
    ///////////////////////////////////////////////////////////

    Flx_SystemButton::Flx_SystemButton( int x, int y, int w, int h, SystemBoxButtonType type, Fl_Color color )
    : Fl_Button( x, y, w, h )
    , _type( type ) {
        box( FL_FLAT_BOX );

        this->color( color );
        down_color( fl_darker( color ) );

        label( type == SYSTEMBUTTON_MINI ? "-" : type == SYSTEMBUTTON_MAXI ? "+" : "x" );
        labelfont( FL_HELVETICA_BOLD );
        labelsize( 16 );
        clear_visible_focus( );

        callback( staticOnClick, this );
    }

    void Flx_SystemButton::staticOnClick( Fl_Widget *pW, void *pUserdata ) {
        Flx_SystemButton *pBtn = (Flx_SystemButton*) pUserdata;
        pBtn->onClick( );
    }

    void Flx_SystemButton::onClick( ) {
        SystemBoxAction action;
        action.actionButton = _type;
        signalSystemButtonClick.send( *this, action );
    }

 
    ///////////////////////////////////////////////////////////
    ////////////  Flx_MdiChild  ///////////////////////////////
    ///////////////////////////////////////////////////////////

    Flx_MdiChild::Flx_MdiChild( int x, int y, int w, int h, const char *pLbl )
    : Fl_Group( x, y, w, h, pLbl )
    , _titleBarColorFocused ( fl_rgb_color( 26, 26, 26 ) )
    , _titleBarColorUnfocused( fl_rgb_color( 160, 160, 160 ) )
    , _currentCursor( FL_CURSOR_DEFAULT )
    {
        box( FL_FLAT_BOX );
        labelsize( 0 );
        int border = 3;

        createTitleBar( x + border, y + 2, w - 2*border, pLbl );
        
        _pClientArea = new Fl_Group( x+border, _pTitleBar->y() + _pTitleBar->h(), 
                                     w-2*border, h - _pTitleBar->h() - border - 2, 
                                    "ClientArea" );
        _pClientArea->labelsize( 0 );
        _pClientArea->box( FL_FLAT_BOX );
        _pClientArea->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
        _pClientArea->color( FL_WHITE );
        _pClientArea->end();
        
        end( );
        
        resizable( _pClientArea );
        
        rememberSize();
        
        printBounds( this );
        printBounds( _pTitleBar );
        printBounds( _pClientArea );
 
    }

    void Flx_MdiChild::createTitleBar( int x, int y, int w, const char *pLbl ) {
        int titleBarH = 30;
        int sysBtnSideLen = 25;
        int sysBoxW = 3 * sysBtnSideLen + 1;
        int imgBoxSideLen = 28;
        int titleBoxW = w - sysBoxW - imgBoxSideLen;

        _pTitleBar = new Fl_Group( x, y, w, titleBarH, "TitleBar" );
        _pTitleBar->box( FL_FLAT_BOX );
        _pTitleBar->labelsize( 0 );

        //////// ImageBox
        _pImageBox = new Fl_Box( x, y, imgBoxSideLen, imgBoxSideLen );
        //Default Icon:
        _pIcon = new Fl_Pixmap( mdi_xpm );
        _pImageBox->image( _pIcon );

        /////// TitleBox
        _pTitleBox = new Fl_Box( _pImageBox->x( ) + _pImageBox->w( ), y,
                titleBoxW, titleBarH, pLbl );
        _pTitleBox->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
        _pTitleBox->box( FL_FLAT_BOX );

        /////// SystemBox
        _pSystemBox = new Fl_Group( _pTitleBar->x( ) + _pTitleBar->w( ) - sysBoxW, y,
                                    sysBoxW, titleBarH, "SystemBox" );
        _pSystemBox->labelsize( 0 );

        /////// SystemButtons
        createSystemButtons( _pSystemBox->x( ), y + 2, sysBtnSideLen );

        _pSystemBox->end( );

        _pTitleBar->end( );
        _pTitleBar->resizable( _pTitleBox );
        
        setTitleBarColorFocused( false );
    }
    
    void Flx_MdiChild::setTitle( const char *pTitle ) {
        _pTitleBox->copy_label( pTitle );
    }
    
    void Flx_MdiChild::setTitleBarColors( Fl_Color focused, Fl_Color unfocused ) {
        bool isFocused = _pTitleBar->color() == _titleBarColorFocused ? true : false;
        _titleBarColorUnfocused = unfocused;
        _titleBarColorFocused = focused;
        setTitleBarColorFocused( isFocused );
        redraw();
    }

    void Flx_MdiChild::createSystemButtons( int x, int y, int sideLen ) {
        _pMinBtn = new Flx_SystemButton( x, y, sideLen, sideLen, SYSTEMBUTTON_MINI, 
                                        _titleBarColorUnfocused );
        _pMinBtn->signalSystemButtonClick
                .connect< Flx_MdiChild, &Flx_MdiChild::onSystemButtonClick >( this );

        _pMaxBtn = new Flx_SystemButton( _pMinBtn->x( ) + _pMinBtn->w( ), y,
                sideLen, sideLen, SYSTEMBUTTON_MAXI, _titleBarColorUnfocused );
        _pMaxBtn->signalSystemButtonClick
                .connect< Flx_MdiChild, &Flx_MdiChild::onSystemButtonClick >( this );


        _pCloseBtn = new Flx_SystemButton( _pMaxBtn->x( ) + _pMaxBtn->w( ), y,
                sideLen, sideLen, SYSTEMBUTTON_CLOSE, _titleBarColorUnfocused );
        _pCloseBtn->signalSystemButtonClick
                .connect< Flx_MdiChild, &Flx_MdiChild::onSystemButtonClick >( this );
    }

    
    void Flx_MdiChild::setTitleBarColorFocused( bool focused ) {
        Fl_Color colr = focused ? _titleBarColorFocused : _titleBarColorUnfocused;
        Fl_Color lblcolor = focused ? FL_WHITE : FL_GRAY;
        _pTitleBar->color( colr );
        
        _pTitleBox->color( colr );
        _pTitleBox->labelcolor( lblcolor );
        
        _pMinBtn->color( colr );
        _pMinBtn->labelcolor( lblcolor );
        
        _pMaxBtn->color( colr );
        _pMaxBtn->labelcolor( lblcolor );
        
        _pCloseBtn->color( colr );
        _pCloseBtn->labelcolor( lblcolor );
    }
    
    void Flx_MdiChild::draw( ) {
        bool clipped = false;
        Fl_Widget *p = parent();
        int overlapY = y() + h() - ( p->y() + p->h() );
        int overlapX = x() + w() - ( p->x() + p->w() );
        overlapX = overlapX < 0 ? 0 : overlapX;
        if( overlapY > 0 || overlapX > 0 ) {          
            fl_push_clip( x(), y(), w() - overlapX, h() - overlapY );
            clipped = true;
        }
        
        Fl_Group::draw( );
        
        if( clipped ) {
            fl_pop_clip();
        }
    }
    
    const Rectangle Flx_MdiChild::getClientAreaSize() const {
        Rectangle r;
        r.X = _pClientArea->x();
        r.Y = _pClientArea->y();
        r.W = _pClientArea->w();
        r.H = _pClientArea->h();
        return r;
    }

    void Flx_MdiChild::add( Fl_Widget &w ) {
        _pClientArea->add( w );
    }
    
    void Flx_MdiChild::add( Fl_Widget *pW ) {
        add( *pW );
    }
    
    int Flx_MdiChild::handle( int evt ) {
        int rc = Fl_Group::handle( evt );

        switch( evt ) {
            case FL_MOVE:
            {
                _mousePos = getMousePosition();
                if( _mousePos == POS_ANY ) {
                    if( _currentCursor != cursors[POS_ANY] )
                    {
                        setCursor( POS_ANY );
                    }
                } else {
                    setCursor( _mousePos );
                }
                break;
            }
            case FL_LEAVE:
                setCursor( POS_ANY );
                break;
            case FL_FOCUS:
                setTitleBarColorFocused( true );
                redraw();
                break;
            case FL_UNFOCUS:
                setTitleBarColorFocused( false );
                redraw();
                break;
            case FL_PUSH:
            {                                  
                //if /this/ == Fl_MdiChild (not one of its children)
                //then make it the last in the Fl_Group::array(). Thus,
                //it will be drawn /last/, i.e. "over" the other
                //Flx_MdiChild instances:                
                Fl_Widget *pW = parent()->child( parent()->children() - 1 );               
                if( pW != this ) {
                    Flx_MdiContainer *pParent = (Flx_MdiContainer*)parent();
                    if( pParent->children( ) > 1 ) {                    
                        pParent->removeMdiChild( *this, false );
                        pParent->addMdiChild( *this, false );                    
                        pParent->redraw( );
                    }
                }    
                Fl_Widget *pFocussed = Fl::focus();
                if( /*pFocussed &&*/ pFocussed != this ) {                    
                    this->take_focus();
                }

                _x = Fl::event_x( );
                _y = Fl::event_y( );
                
                if( _mousePos == POS_ANY ) {
                    Fl_Widget *pW = Fl::belowmouse();  
                    if( pW == _pTitleBox ) {
                        _dragging = true;
                        fl_cursor( FL_CURSOR_MOVE );
                        _currentCursor = FL_CURSOR_MOVE;
                        if( Fl::event_clicks() != 0 ) {
                            SystemBoxAction action;
                            action.actionButton = SYSTEMBUTTON_MAXI;
                            signalSystemButtonClick.send( *this, action );
                        }                         
                    }
                }                
                
                return 1;
                
            }
                break;
            case FL_RELEASE:
                _dragging = false;
                _mousePos = POS_ANY;
                break;
            case FL_DRAG:
                if( _dragging ) {
                    drag( );
                } else if( _mousePos != POS_ANY ) {
                    resize( );
                }
                break;
            default:
                break;
        }

        return rc;
    }

//    MousePosition Flx_MdiChild::checkResizeCursor( ) {
//        int x = Fl::event_x( ), y = Fl::event_y( );
//        int leftX = this->x( );
//        int rightX = leftX + this->w( );
//        int topY = this->y( );
//        int botY = topY + this->h( );
//
//        unsigned int pos = POS_ANY;
//
//        if( x > ( rightX - 6 ) ) {
//            pos = POS_E;
//        } else if( x < ( leftX + 6 ) ) {
//            pos = POS_W;
//        }
//        if( y > ( botY - 6 ) ) {
//            pos += POS_S;
//        } else if( y < ( topY + 6 ) ) {
//            pos += POS_N;
//        }
//
//        fl_cursor( cursors[pos] );
//
//        return (MousePosition) pos;
//    }
    
    MousePosition Flx_MdiChild::getMousePosition() const {
        int x = Fl::event_x( ), y = Fl::event_y( );
        int leftX = this->x( );
        int rightX = leftX + this->w( );
        int topY = this->y( );
        int botY = topY + this->h( );

        unsigned int pos = POS_ANY;

        if( x > ( rightX - 6 ) ) {
            pos = POS_E;
        } else if( x < ( leftX + 6 ) ) {
            pos = POS_W;
        }
        if( y > ( botY - 6 ) ) {
            pos += POS_S;
        } else if( y < ( topY + 6 ) ) {
            pos += POS_N;
        }

        return (MousePosition) pos;
    }

    void Flx_MdiChild::setCursor( MousePosition pos ) {
        Fl_Cursor cursor = cursors[pos];
        fl_cursor( cursor );
        _currentCursor = cursor;
    }
    
    void Flx_MdiChild::onSystemButtonClick( Flx_SystemButton &btn, SystemBoxAction & action ) {
        signalSystemButtonClick.send( *this, action );
    }

    void Flx_MdiChild::drag( ) {
        int x = Fl::event_x( ), y = Fl::event_y( );
        int thisX = this->x( ), thisY = this->y( );

        int dx = x - _x, dy = y - _y;
        int newX = thisX + dx;
        int newY = thisY + dy;

        //check if dragging is possible
        int remVis = 15; //min. remains visible
        int parentX = parent( )->x( ), parentY = parent( )->y( );
        if( newX < ( parentX - w( ) + remVis ) ) return;
        if( newX > ( parentX + parent( )->w( ) - remVis ) ) return;
        if( newY < parentY ) return;
        if( newY > ( parentY + parent( )->h( ) - remVis ) ) return;

        position( newX, newY );
        window( )->redraw( );
        _x = x;
        _y = y;
    }

    void Flx_MdiChild::resize( ) {
        int x = Fl::event_x( ), y = Fl::event_y( );
        int dx = x - _x, dy = y - _y;

        switch( _mousePos ) {
            case POS_E:
            case POS_W:
                resizeHorz( dx );
                break;
            case POS_N:
            case POS_S:
                resizeVert( dy );
                break;
            default:
                resizeHorz( dx );
                resizeVert( dy );
                break;
        }

        window( )->redraw( );

        _x = Fl::event_x( );
        _y = Fl::event_y( );
        
        rememberSize();
    }

    void Flx_MdiChild::resizeHorz( int dx ) {
        int thisX = this->x( );
        if( canResizeHorz( dx ) ) {
            if( ( _mousePos & POS_E ) == POS_E ) {
                Fl_Group::resize( thisX, this->y( ), this->w( ) + dx, this->h( ) );
            } else {
                Fl_Group::resize( this->x( ) + dx, this->y( ), this->w( ) - dx, this->h( ) );
            }
        }
    }

    void Flx_MdiChild::resizeVert( int dy ) {
        int thisY = this->y( );
        if( canResizeVert( dy ) ) {
            if( ( _mousePos & POS_N ) == POS_N ) {
                Fl_Group::resize( this->x( ), thisY + dy, this->w( ), this->h( ) - dy );
            } else {
                Fl_Group::resize( this->x( ), thisY, this->w( ), this->h( ) + dy );
            }
        }
    }

    bool Flx_MdiChild::canResizeVert( int dy ) const {
        if( dy > 0 ) {
            //resizing downwards
            if( ( _mousePos & POS_N ) == POS_N ) { //grip on title bar; child getting smaller
                if( this->y( ) > parent( )->y( )/*keep title bar visible*/ &&
                        this->h( ) > ( _pTitleBar->h( ) + 25 /*approx. scrollbar height*/ ) ) {
                    return true;
                }
            } else {
                //grip on lower border; child getting higher
                return true;
            }
        } else { //dy < 0; resizing upwards
            if( ( _mousePos & POS_N ) == POS_N ) { //grip on title bar; child getting higher
                if( this->y( ) > parent( )->y( ) ) {
                    return true;
                }
            } else {
                //grip on lower border; child getting smaller
                if( this->h( ) > ( _pTitleBar->h( ) + 25 /*approx. scrollbar height*/ ) ) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Flx_MdiChild::canResizeHorz( int dx ) const {
        if( dx > 0 ) { //resizing to the right
            if( ( _mousePos & POS_W ) == POS_W ) { //grip on left border; child getting smaller
                if( this->w( ) > 100  ) {
                    return true;
                }
            } else {
                //grip on right border; child growing
                return true;
            }
        } else { //resizing to the left
            if( ( _mousePos & POS_W ) == POS_W ) { //grip on left border; child getting smaller		
                return true;
            } else {
                //grip on right border; child growing
                if( this->w( ) > 100 /* scrollbar width */ ) {
                    return true;
                }
            }
        }
        return false;
    }

    void Flx_MdiChild::restoreSize() {
        resize( _recentSize.X, _recentSize.Y, _recentSize.W, _recentSize.H );
    }
    
    void Flx_MdiChild::resize( int x, int y, int w, int h ) {
        Fl_Group::resize( x, y, w, h );
        Fl_Group *pParent = parent()->as_group();
        if( pParent ) {
            if( x == pParent->x() && y == pParent->y() &&
                w == pParent->w() && h == pParent->h() )
            {
                ; //do nothing
            } else {
                rememberSize();
            }
           
        }
    }

    void Flx_MdiChild::rememberSize() {
        _recentSize.X = this->x();
        _recentSize.Y = this->y();
        _recentSize.W = this->w();
        _recentSize.H = this->h();
    }
    
    
    ///////////////////////////////////////////////////////////
    ////////////  Flx_MdiContainer  ///////////////////////////////
    ///////////////////////////////////////////////////////////

    Flx_MdiContainer::Flx_MdiContainer( int x, int y, int w, int h )
    : Fl_Group( x, y, w, h ) 
    {
        box( FL_FLAT_BOX );
        color( fl_rgb_color( 234, 234, 234 ) );
    }
    
    void Flx_MdiContainer::end() {
        Fl_Group::end();
        
        for( int i = 0, imax = children(); i < imax; i++ ) {
            Fl_Widget *pW = child( i ); 
            
            connectToChildSignals( (Flx_MdiChild&)*pW );           
        }

    }
    
    void Flx_MdiContainer::addMdiChild( Flx_MdiChild &mdiChild, bool connectToSignals ) 
    {
        Fl_Group::add( mdiChild );
        if( connectToSignals ) {
            connectToChildSignals( mdiChild );
        }
    }
    
    void Flx_MdiContainer::add( Fl_Widget &w ) {
        Flx_MdiChild *pMdiChild = dynamic_cast<Flx_MdiChild*>( &w );
        if( !pMdiChild ) {
            MdiChildException ex( "Widget to be added is not a Flx_MdiChild" );
            throw( ex );
        }
        addMdiChild( *pMdiChild, true );
    }
    
    void Flx_MdiContainer::add( Fl_Widget *pW ) {
        add( *pW );
    }
    
    void Flx_MdiContainer::removeMdiChild( Flx_MdiChild &mdiChild, 
                                           bool disconnectFromSignals ) 
    {
        disconnectFromChildSignals( mdiChild );
        Fl_Group::remove( mdiChild );
    }
    
    void Flx_MdiContainer::remove( Fl_Widget *pW ) {
        remove( *pW );
    }
    
    void Flx_MdiContainer::remove( Fl_Widget &w ) {
        Flx_MdiChild *pMdiChild = dynamic_cast<Flx_MdiChild*>( &w );
        if( !pMdiChild ) {
            MdiChildException ex( "Widget to be removed is not a Flx_MdiChild. How could you add() it?" );
            throw( ex );
        }
        
        removeMdiChild( *pMdiChild, true );
    }
    
    void Flx_MdiContainer::remove( int i ) {
        remove( *child( i ) );
    }

    const MdiChildListPtr Flx_MdiContainer::getMdiChildren() const {
        MdiChildListPtr ptr( new vector<Flx_MdiChild*>() );
        for( int i = children()-1; i > -1; i-- ) {
            Flx_MdiChild *pChild = (Flx_MdiChild*)child( i );
            if( typeid( *pChild ).name() == typeid( Flx_MdiChild ).name() ) {
                ptr->push_back( pChild );
            }
        }
        return ptr;
    }
    
    void Flx_MdiContainer::arrangeChildren() {
        if( w() < 200 || h() < 200 ) {return;} 
        
        float maxrows = 3;
        float rows = ceil( (float)children() / maxrows );
        
        float H = (float)h() / rows;
        
        float cols = (float)children() / rows;
        float W = (float)w() / cols;
        
        int X = x(), Y = y();
        for( int r = 0; r < rows; r++ ) {
            for( int c = 0; c < cols; c++ ) {
                int idx = r * cols + c;
                ((Flx_MdiChild*)child( idx ))->resize( X, Y, W, H );
                X += W;
            }
            X = x();
            Y += H;
        }
    }
    
    void Flx_MdiContainer::setFocusTo( Flx_MdiChild &child ) {
        child.handle( FL_PUSH );
    }
    
    void Flx_MdiContainer::draw( ) {
        //log( "Container.draw" );
        Fl_Group::draw( );
    }

    int Flx_MdiContainer::handle( int evt ) {
        int rc = Fl_Group::handle( evt );
        switch( evt ) {
            case FL_SHOW:
                if( children() > 0 ) {
                    child( children() - 1 )->handle( FL_PUSH );
                }
                break;
            case FL_KEYDOWN:
            {
                int n = Fl::event_key();
                if( Fl::event_state() == FL_CTRL && n == 111 /* 'o' */ )  {
                    //öffne KontextMenü
                    showOpenChildren();
                }                
                rc = 1;
                break;
            }
            default:
                break;
        }
        return rc;
    }
    
    void Flx_MdiContainer::onChildSystemButtonClick( Flx_MdiChild &child, SystemBoxAction &action ) {
        if( action.actionButton == SYSTEMBUTTON_CLOSE ) {
            VetoableCloseAction action;
            signalBeforeChildClose.send( *this, action );
            if( action.canClose ) {
                remove( child );
                parent()->redraw();
            } 
        } else if( action.actionButton == SYSTEMBUTTON_MAXI ) { 
            //wenn nicht maximiert, maximieren;
            //wenn maximiert, auf _recentSize zurücksetzen
            if( child.x() == x() && child.y() == y() && child.w() == w() && child.h() == h() ) {
                //maximized, restore:
                child.restoreSize();
            } else {
                ((Fl_Group&)child).resize( x(), y(), w(), h() );
            }
            parent()->redraw();
        } else {
            //SYSTEMBUTTON_MINI
            //Child unsichtbar machen
            child.hide();
            //wie wird das child wieder sichtbar? ==> über das Fenster-Menü
        }
    }
    
    void Flx_MdiContainer::connectToChildSignals( Flx_MdiChild &child ) {
        child.signalSystemButtonClick.
                connect<Flx_MdiContainer, &Flx_MdiContainer::onChildSystemButtonClick>( this );
    }
    
    void Flx_MdiContainer::disconnectFromChildSignals( Flx_MdiChild &child ) {
        child.signalSystemButtonClick.
                disconnect<Flx_MdiContainer, &Flx_MdiContainer::onChildSystemButtonClick>( this );
    }

    void Flx_MdiContainer::showOpenChildren() {
        //get active child:
        Flx_MdiChild *pChild = (Flx_MdiChild*)child( children() - 1 );
        
        Fl_Menu_Button menu( 1, 1, 1, 1 );
        menu.box( FL_FLAT_BOX );
        menu.down_box( FL_FLAT_BOX );
        menu.color( FL_LIGHT2 );
        menu.labelsize( 11 );
        
        for( int i = children()-1; i >= 0 ; i-- ) {
            menu.add( child( i )->label(), 0, NULL, child( i ) );
        }
        
        int X = ( pChild->x() + pChild->w() ) / 2 - ( menu.w() / 2 );
        int Y = ( pChild->y() + pChild->h() ) / 2 - menu.h();
        
        menu.position( X, Y );
        const Fl_Menu_Item *pItem = menu.popup();
        if( pItem ) {
            ((Flx_MdiChild*)pItem->user_data())->handle( FL_PUSH );
        }
    }

} //ns flx