/*****************************************************************************
 Sphere Class

 NAME:sphere.cpp
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include <math.h>
#include "sphere.h"
#include "zerotest.h"

// Constructor
TSphere::TSphere ()
:TObject()
{
 _Centre=TVector(0.0,0.0,0.0) ;
 _Radius=0.0 ;
}

// Constructor
TSphere::TSphere(const TVector &Centre,double Radius,
                 const TSurfaceProperties SurfaceProperties)
:TObject(SurfaceProperties)
{
 _Centre=Centre ;
 _Radius=Radius ;
}

// The Intersection of a sphere and a line
double TSphere::Intersection(TVector &Point,TVector &Normal,
                             const TLine &Line) const
{
 double B,C,D ;
 double Root1,Root2 ; // the two roots of the equation
 TVector LineDirection ;
 TVector Direction ;
 double Distance ;
 TVector CommonPart ; // part of the roots that is need 3 times calculated for
                      // speed

 LineDirection=(Line.EndPoint()-Line.StartPoint()).Unit() ;

 CommonPart=Line.StartPoint()-_Centre ;
 B=(LineDirection.Dot(CommonPart))*2.0 ;

 C=(CommonPart.Dot(CommonPart))-(_Radius*_Radius) ;

 D=(B*B)-(4*C) ;


 if (D<0.0)
   {
     // no intersection
    Distance=-10 ;
   }
 else
   {
    Root1=(-B+sqrt(D))/2.0 ;
    Root2=(-B-sqrt(D))/2.0 ;

    // find the root that is nearest
    if (Root1<Root2)
      {
       if (LessThanZero(Root1))
         {
          Distance=Root2 ;
         }
       else
         {
          Distance=Root1 ;
         }
      }
    else
      {
       if (LessThanZero(Root2))
         {
          Distance=Root1 ;
         }
       else
         {
          Distance=Root2 ;
         }
      }

   }

   Direction=LineDirection*Distance ;
   Point=Line.StartPoint()+Direction ;

   Normal=(Point-_Centre).Unit() ;

   return (Distance) ;
}

// return the center point of the sphere
TVector TSphere::Center() const
{
 return _Centre ;
}

// return the center of the sphere
double TSphere::Radius() const
{
 return _Radius ;
}

// function to input a sphere
istream &TSphere::Read (istream &In)
{
 char Comma ; // delimter for the items
 char Bracket ; // delimiter for vector and colour parts
 TVector Center ;
 TColour Colour ;
 double  Radius ;
 double  Diffuse ;
 double  Specular ;
 double  Shine ;
 int     Roughness ;

 // read in the sphere
 In>>Bracket>>Center>>Bracket>>Comma>>Radius>>Comma
   >>Bracket>>Colour>>Bracket>>Comma>>Diffuse>>Comma>>
     Specular>>Comma>>Shine>>Comma>>Roughness ;

 // copy to the object
 (*this)=TSphere(Center,Radius,
                TSurfaceProperties(Colour,Diffuse,Specular,Shine,Roughness)) ;

 // return the stream
 return In ;
}

// function to output a sphere
ostream &TSphere::Write (ostream &Out) const
{
 // write out the colour
 Out<<'('<<(*this).Center()<<')'<<','<<(*this).Radius()<<','
    <<'('<<(*this).Colour()<<')'<<','<<(*this).Diffuse()<<','
    <<(*this).Specular()<<','<<(*this).Shine()<<','<<(*this).Roughness() ;

 // return the stream
 return Out ;
}

// function to read in a plane
istream &operator>>(istream &In,TSphere &Sphere)
{
 // input a plane
 return Sphere.Read(In) ;
}

ostream &operator<<(ostream &Out,const TSphere &Sphere)
{
 // output the colour
 return Sphere.Write(Out) ;

}
