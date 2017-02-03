#ifndef sphere_h
#define sphere_h

/*****************************************************************************
 Sphere Class

 NAME:sphere.h
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include "vector.h"
#include "line.h"
#include "object.h"

class TSphere :public TObject
{
 private:
   TVector _Centre ;
   double  _Radius ;

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

 public:
   // Constructors
   TSphere () ;
   TSphere (const TVector &Centre , double Radius ,
            const TSurfaceProperties SurfaceProperties) ;

   // selectors
   TVector Center() const ;
   double Radius() const ;

   // Return the intersection of a sphere and a line
   double Intersection (TVector &Point,TVector &Normal,
                        const TLine &Line) const;


   // streaming operators
   friend istream &operator>>(istream &In, TSphere &Sphere);
   friend ostream &operator<<(ostream &Out,const TSphere &Sphere) ;
} ;

#endif
