#ifndef pixmap_h
#define pixmap_h

/******************************************************************************
 Pixmap Class

 NAME:pixmap.h
 DATE:10/11/1196
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include <iostream.h>
#include "colour.h"

class TPixmap
{
 private:
   int _Width ;
   int _Height ;
   TColour *_Pixmap ;

 public:
   // constructors
   TPixmap () ;
   TPixmap (int Width,int Height) ;

   // Destructor
   ~TPixmap () ;

   // Selectors
   TColour operator() (int Width,int Height) const;

   // Modifiers
   TColour &operator() (int Width,int Height) ;
   Clear() ;
   Clear (TColour Colour) ;
   SetSize(int X,int Y) ;
   Display() ;
   int Width() ;
   int Height() ;

   // output
   ostream &StreamPPMOut (ostream &Out) ;

} ;

#endif
