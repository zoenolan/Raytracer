#ifndef object_h
#define object_h

/*****************************************************************************
 Base class for all object in the raycaster/raytracer

 NAME:object.h
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the colour class
#include "surface.h"

class TObject
{
 private:
   TSurfaceProperties _SurfaceProperties ;

 public:
   // constuctor
   TObject () ;
   TObject (const TSurfaceProperties SurfaceProperties) ;

   virtual ~TObject() {}

   // return the colour
   TColour Colour() const;
   double  Diffuse() const ;
   double  Specular() const ;
   double  Shine() const ;
   int     Roughness() const ;
   TSurfaceProperties SurfaceProperties() const ;
   Copy (const TSurfaceProperties &Surface) ;

   // intersection
   virtual double Intersection(TVector &Point,TVector &Normal,
                               const TLine &Line) const =0 ;

} ;

#endif
