#ifndef cube_h
#define cube_h

/*****************************************************************************
 Plane Class

 NAME:cube.h
 DATE:17/12/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include vector class
#include "vector.h"

// and the colour class
#include "colour.h"

// and the line class
#include "line.h"

// and include the object class
#include "object.h"

class TCube :public TObject
{
 private:
   TVector _TopCorner ;   // Top corner of the cube
   TVector _BottomCorner ; // Bottom corner of the cube

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

public:
   // Constructors
   TCube () ;
   TCube (TVector TopCorner,TVector BottomCorner,
           const TSurfaceProperties) ;

   // Intersection of a line and a plane
   double Intersection(TVector &Point,TVector &Normal,const TLine &Line) const;

   // streaming operators
   friend istream &operator>>(istream &In, TCube &Cube);
   friend ostream &operator<<(ostream &Out,const TCube &Cube) ;
} ;
#endif
