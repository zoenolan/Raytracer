#ifndef raycast_h
#define raycast_h

/******************************************************************************
 Raycaster class

 NAME:raycast.h
 DATE:11/10/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include "colour.h"
#include "pixmap.h"
#include "vector.h"
#include "line.h"
#include "plane.h"
#include "sphere.h"
#include "plight.h"
#include "camera.h"
#include "pqueue.h"
#include "object.h"
#define  LIST_SIZE 100 // queue should be here

class TRaycaster
{
 private:
   // Pixmap to hold the image
   TPixmap _Screen ;
   // Camera
   TCamera _Camera ;

   // Ambient Intensity
   double  _AmbientIntensity ;

   // background colour
   TColour _BackgroundColour ;

   // object queue
   TPointerQueue <TObject> _ObjectList ;

   // number of levels of reflection
   int _NumberOfReflections ;

   // Light sources
   TPointLight _Light ;

   // fog values
   double _FogStart ;
   double _FogEnd ;

   TColour Shade(const TVector &Normal,const TVector &Point,
                 const TVector &RayStart,const TObject *Object) const ;

   double TraceRay (const TLine &Line,TVector &Point,TVector &Normal,
                    TObject **Object ) const;

   TColour RenderPixel (const TLine &Line) ;

public:
   TRaycaster() ;
   TRaycaster(const char *Filename) ;

   Render() ;
   Display() ;

} ;
#endif
