#ifndef camera_h
#define camera_h

/******************************************************************************
 Camera Class

 NAME:camera.h
 DATE:11/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include "vector.h"

class TCamera
{
 private:
   TVector _EyePosition ;
   TVector _ViewDirection ;
   TVector _Up ;
   double  _ScreenXSize ;
   double  _ScreenYSize ;
   int     _ScreenPixelWidth ;
   int     _ScreenPixelHeight ;
   double  _DistanceToScreen ;

   // data member used to speed up calculations
   TVector _TopLeft ;
   TVector _OnePixelRight ;
   TVector _OnePixelDown  ;

 public:
   TCamera () ;
   TCamera (const TVector &EyePosition,const TVector &ViewDirection,
            const TVector &Up,const double ScreenXSize,
            const int ScreenPixelWidth,const double Fov) ;

   // return the eye position
   TVector EyePosition() const { return _EyePosition ; }

   // return the vector to that pixel in the image
   TVector operator()(int PixelX,int PixelY) ;

} ;

#endif
