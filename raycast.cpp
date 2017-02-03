/*****************************************************************************
 Raycaster Class

 NAME:raycast.cpp
 DATE:11/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include "raycast.h"

#include "fstream.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "aux.h"
#include "zerotest.h"
#include <string.h>
#include "cube.h"
#include "tri.h"
#include "tmesh.h"

#define SMALLVALUE 0.00001

TColour TRaycaster::Shade(const TVector &Normal,const TVector &Point,
                          const TVector &RayStart,
                          const TObject *Object) const
{
 TColour Colour ;
 int Counter ;
 double Distance ;
 double NewDistance ;
 double LightDistance ;
 TVector NewPoint,NewNormal ;
 TLine  Line ;

 // do the ambient lighting
 Colour=(Object->Colour())*_AmbientIntensity ;

 // do the shadow test

 // work out the nearest object intersection
 Line=TLine(Point+(Normal*SMALLVALUE),_Light.Position()) ;

 NewPoint=Point ;
 LightDistance=_Light.Intersection(NewPoint,NewNormal,Line);

 Distance =-10000 ;

 for (Counter=0;Counter<(_ObjectList.Size());Counter++)
  {

   NewDistance=_ObjectList[Counter]->Intersection(NewPoint,NewNormal,Line) ;
   if (NewDistance<Distance)
     {
      if (GreaterThanZero(NewDistance))
        {
         Distance=NewDistance ;
        }
     }
   else
     {
      if ((GreaterThanZero(NewDistance))&&(LessThanZero(Distance)))
        {
         Distance=NewDistance ;
        }
     }
  }

 if ((LightDistance<Distance)||(LessThanZero(Distance)))
   {
    Colour=Colour+_Light.Shade(Normal,Point,RayStart,Object) ;
   }

 // return the colour
 return Colour ;
}

TColour TRaycaster::RenderPixel (const TLine &Line)
{
 TLine Ray ;
 TColour PixelColour ;
 TVector Point ;
 TVector Normal ;
 double  Distance ;
 TObject *Object ;
 TVector Eye,R ;
 int ReflectionCounter ;
 double ReflectionScalar ;
 double FogFactor ;

 Ray=Line ;

 Distance=TraceRay(Ray,Point,Normal,&Object) ;
 if (LessThanZero(Distance))
   {
    PixelColour=_BackgroundColour ;
   }
 else
   {
    PixelColour=(*this).Shade(Normal,Point,Ray.StartPoint(),Object);
    ReflectionCounter=0 ;
    ReflectionScalar=Object->Specular() ;

    // do the reflections
    while ((!(LessThanZero(Distance)))&&
           (ReflectionCounter<_NumberOfReflections)&&
           (ReflectionScalar>(1.0/512.0)))
      {
       // work out the reflected ray
       Eye=(Point-Ray.StartPoint()).Unit() ;
       R=(Eye-(Normal*((Normal.Dot(Eye))*2))).Unit() ;

       Ray=TLine(Point+R*SMALLVALUE,Point+R);
       Distance=TraceRay(Ray,Point,Normal,&Object) ;
       if (LessThanZero(Distance))
         {
          ReflectionCounter=_NumberOfReflections+1 ;
          PixelColour=PixelColour+_BackgroundColour*ReflectionScalar ;
         }
       else
         {
          ReflectionCounter++ ;
          ReflectionScalar=ReflectionScalar*(Object->Specular()) ;
          PixelColour=PixelColour+
                      (*this).Shade(Normal,Point,Ray.StartPoint(),Object)*
                         ReflectionScalar;
         }
      }
   }


 // now fog the colour
 if (Distance>_FogStart)
   {
    if (Distance>_FogEnd)
      {
       // passed fog maximum
       PixelColour=_BackgroundColour ;
      }
    else
      {
       // blend the colour
       FogFactor=(Distance-_FogStart)/(_FogEnd-_FogStart) ;
       PixelColour=TColour(PixelColour.Red()+
                ((_BackgroundColour.Red()-PixelColour.Red())*FogFactor),
                      PixelColour.Green()+
                ((_BackgroundColour.Green()-PixelColour.Green())*FogFactor),
                      PixelColour.Blue()+
                ((_BackgroundColour.Blue()-PixelColour.Blue())*FogFactor)) ;
      }
   }

 return PixelColour ;
}

TRaycaster::TRaycaster()
{
 _Camera=TCamera(TVector(0.0,0.0,0.0),TVector(0.0,1.0,0.0),
                 TVector(0.0,0.0,1.0),1.0,256,60) ;
 _Screen.SetSize(256,256) ;
 _AmbientIntensity=0.5 ;
 _BackgroundColour=TColour(0.0,0.0,0.0) ;
 _Light=TPointLight(TVector(10.0,0.0,10.0),0.7,TColour(1.0,1.0,1.0)) ;
}

TRaycaster::TRaycaster(const char *Filename)
{
 char ObjectType[6] ; // object type as a text name
 char Bracket ; // Bracket buffer
 char Comma ;   // Comma buffer
 int  End=0 ;   // file read end flag
 TPlane Plane ;
 TSphere Sphere ;
 TCube Cube ;
 TSimpleTriangle Triangle ;
 TTriangleMesh Mesh ;

 // temp variables for camera
 TVector EyePosition,Direction,Up ;
 double ScreenSize ;
 int ScreenPixelSize ;
 double Fov ;
 double Intensity ;


 // open the data file
 ifstream fin(Filename) ;

 while (End!=1)
   {
    fin>>ObjectType ;

    if ((strncmp(ObjectType,"camera",6))==0)
      {

       // read in the camera
       fin>>Bracket>>Bracket>>EyePosition>>Bracket>>Comma>>
               Bracket>>Direction>>Bracket>>Comma>>
               Bracket>>Up>>Bracket>>Comma>>ScreenSize>>Comma>>
               ScreenPixelSize>>Comma>>Fov>>Bracket ;

       _Camera=TCamera(EyePosition,Direction,Up,ScreenSize,ScreenPixelSize,
                       Fov) ;
       _Screen.SetSize(ScreenPixelSize,ScreenPixelSize) ;

       // output details
       cout<<"INFO: Camera={"<<"<"<<EyePosition<<">,<"<<Direction<<">,<"<<
           Up<<">,"<<ScreenSize<<","<<ScreenPixelSize<<","<<Fov<<"}"<<endl ;
      }

    else if ((strncmp(ObjectType,"foging",6))==0)
      {
       // read in the fog
       fin>>Bracket>>_FogStart>>Comma>>_FogEnd>>Bracket ;
       cout<<"INFO: Fog start="<<_FogStart<<"  Fog end="<<_FogEnd<<endl ;
      }

    else if ((strncmp(ObjectType,"alight",6))==0)
      {
       // read in the Ambient light intensity
       fin>>Bracket>>Intensity>>Bracket ;

       _AmbientIntensity=Intensity ;

       // output details
       cout<<"INFO: Ambient Light Intensity= {"<<_AmbientIntensity<<"}"<<endl;
      }

    else if ((strncmp(ObjectType,"plight",6))==0)
      {
       // read in a light source
       fin>>Bracket>>_Light>>Bracket ;
       cout<<"INFO: Point Light Source Added"<<endl ;
      }

    else if ((strncmp(ObjectType,"colour",6))==0)
      {
       // read in the background colour
       fin>>Bracket>>_BackgroundColour>>Bracket ;

       // output details
       cout<<"INFO: Background Colour= {"<<_BackgroundColour<<"}"<<endl ;
      }

    else if ((strncmp(ObjectType,"reflec",6))==0)
      {
       fin>>Bracket>>_NumberOfReflections>>Bracket ;
       cout<<"INFO: Number of Reflections={"<<_NumberOfReflections<<"}"<<endl ;
      }

    else if ((strncmp(ObjectType,"iplane",6))==0)
      {
       // read in a plane
       fin>>Bracket>>Plane>>Bracket ;
       _ObjectList.Add(new TPlane (Plane)) ;
       cout<<"INFO: Plane Added"<<endl ;
      }

    else if ((strncmp(ObjectType,"trimes",6))==0)
      {
       // read in a triangle mesh
       fin>>Bracket>>Mesh>>Bracket ;
       _ObjectList.Add(new TTriangleMesh (Mesh)) ;
       cout<<"INFO: Triangle Mesh Added"<<endl ;
      }

    else if ((strncmp(ObjectType,"sphere",6))==0)
      {
       // read in a sphere
       fin>>Bracket>>Sphere>>Bracket ;
       _ObjectList.Add(new TSphere (Sphere)) ;
       cout<<"INFO: Sphere Added"<<endl ;
      }

    else if ((strncmp(ObjectType,"cubeid",6))==0)
      {
       // read in a cube
       fin>>Bracket>>Cube>>Bracket ;
       _ObjectList.Add(new TCube (Cube)) ;
       cout<<"INFO: Cube Added"<<endl ;
      }

    else if ((strncmp(ObjectType,"triang",6))==0)
      {
       // read in a triangle
       fin>>Bracket>>Triangle>>Bracket ;
       _ObjectList.Add(new TSimpleTriangle (Triangle)) ;
       cout<<"INFO: Triangle Added"<<endl ;

      }

    else
      {
       End=1 ;
      }
   }

 // close the file
 fin.close() ;

}

double TRaycaster::TraceRay(const TLine &Line,TVector &Point,TVector &Normal,
			    TObject **Object) const
{
 int Counter ;

 double  Distance ;
 double  NewDistance ;
 TVector NewPoint ;
 TVector NewNormal ;
 int     Index ;

 Distance=-100000 ;
 Index=-1000 ;

 for (Counter=0;Counter<(_ObjectList.Size());Counter++)
   {

    NewDistance=_ObjectList[Counter]->Intersection(NewPoint,NewNormal,Line) ;
    if (NewDistance<Distance)
      {
       if (GreaterThanZero(NewDistance))
         {
          Index=Counter ;
          Distance=NewDistance ;
          Point=NewPoint ;
          Normal=NewNormal ;
         }
      }
    else
      {
       if ((GreaterThanZero(NewDistance))&&(LessThanZero(Distance)))
         {
          Index=Counter ;
          Distance=NewDistance ;
          Point=NewPoint ;
          Normal=NewNormal ;
         }
      }
   }

 if (Index>-1)
   {
    // we need to return all the data we need to do the reflections
    // and shading
    *Object=_ObjectList[Index] ;

    return Distance ;

   }
 else
   {
    return -10000 ;
   }

}

TRaycaster::Render()
{
 int     X,Y ;

 TLine   Ray ;

 TVector ScreenVector ;

 for (Y=0;Y<_Screen.Height();Y++)
   {
    for (X=0;X<_Screen.Width();X++)
      {
       // trace the ray
       ScreenVector=_Camera(X,Y) ;
       Ray=TLine(_Camera.EyePosition(),ScreenVector) ;

       _Screen(X,Y)=RenderPixel(Ray) ;
      }
   }
 // save the image to a file
  ofstream fo ("image.ppm") ;
  _Screen.StreamPPMOut(fo) ;

}

TPixmap *pPixmap ;

// dummy display function
void display(void)
{
 pPixmap->Display() ;
}

// Display the pixmap on the screen
TRaycaster::Display()
{

 // open the window
 auxInitDisplayMode (AUX_SINGLE|AUX_RGB) ;
 auxInitPosition(0,0,_Screen.Width(),_Screen.Height()) ;
 auxInitWindow ("Raytracer Version 1.0") ;
 glClearColor (0.0,0.0,0.0,0.0) ;
 glShadeModel (GL_FLAT) ;

 pPixmap=&_Screen ;
 auxMainLoop(display) ;

}
