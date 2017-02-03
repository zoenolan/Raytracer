#ifndef triangle_h
#define triangle_h

/*****************************************************************************
 Simple Triangle classClass

 NAME:tri.h
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

// and include the plane class
#include "plane.h"

class TSimpleTriangle :public TObject
{
 private:
   TVector _P1 ;   // 1st point of the Triangle
   TVector _P2 ; // 2nd Point of the Triangle
   TVector _P3 ; // 3rd point of the Triangle
   TPlane  _Plane ; // Plane the triangle is in

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

public:
   // Constructors
   TSimpleTriangle () ;
   TSimpleTriangle (TVector P1,TVector P2,TVector P3,
           const TSurfaceProperties) ;

   // Intersection of a line and a plane
   double Intersection(TVector &Point,TVector &Normal,const TLine &Line) const;

   // streaming operators
   friend istream &operator>>(istream &In, TSimpleTriangle &SimpleTriangle);
   friend ostream &operator<<(ostream &Out,const TSimpleTriangle
			                         &SimpleTriangle) ;
} ;
#endif
