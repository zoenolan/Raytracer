/*****************************************************************************
 Camera Class

 NAME:camera.cpp
 DATE:11/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

// include the maths functions
#include <math.h>

#include "camera.h"

// Constructor
TCamera::TCamera ()
{
 (*this)=TCamera(TVector(0,0,0),TVector(0,1,0),TVector(0,0,1),1.0,256,60) ;
}

// Constructor
TCamera::TCamera (const TVector &EyePosition,const TVector &ViewDirection,
            const TVector &Up,const double ScreenXSize,
            const int ScreenPixelWidth,const double Fov)
{
 TVector Right ;

 // set all the main variables
 _EyePosition=EyePosition ;
 _ViewDirection=ViewDirection.Unit() ;
 _Up=(Up-(ViewDirection*(Up.Dot(ViewDirection)))).Unit() ;
 _ScreenXSize=ScreenXSize ;
 _ScreenYSize=ScreenXSize ;
 _ScreenPixelWidth=ScreenPixelWidth ;
 _ScreenPixelHeight=ScreenPixelWidth ;
 _DistanceToScreen=_ScreenXSize/(2*tan(((Fov/360.0)*2*M_PI)/2.0)) ;

 // work out the right vector for the screen
 Right=(_ViewDirection*_Up).Unit() ;

 // set up some variables so the rays can be traced quicker
 _OnePixelDown=(-_Up)*(_ScreenYSize/double(_ScreenPixelHeight)) ;
 _OnePixelRight=Right*(_ScreenXSize/double(_ScreenPixelWidth)) ;

 _TopLeft=_EyePosition+(_ViewDirection*_DistanceToScreen)-
          (_OnePixelRight*((_ScreenPixelWidth-1)/2)+(_OnePixelRight*0.5))-
          (_OnePixelDown*((_ScreenPixelHeight-1)/2)+(_OnePixelDown*0.5)) ;

}

// return the vector to that pixel in the image
TVector TCamera::operator()(int PixelX,int PixelY)
{
 TVector PixelVector ;

 PixelVector=_TopLeft+(_OnePixelRight*PixelX)+(_OnePixelDown*PixelY) ;

 return PixelVector ;
}
