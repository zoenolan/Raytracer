/*****************************************************************************
 Simple Triangle Class

 NAME:tri.cpp
 DATE:17/12/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the triangle header
#include "tri.h"
#include "zerotest.h"

// Constructor
TSimpleTriangle::TSimpleTriangle()
:TObject()
{
 _P1=_P2=_P3=TVector(0.0,0.0,0.0) ;
 _Plane=TPlane() ;
}

// Constructor
TSimpleTriangle::TSimpleTriangle (TVector P1,TVector P2,TVector P3,
                                 const TSurfaceProperties SurfaceProperties)
:TObject(SurfaceProperties)
{
 TVector Side1,Side2 ; // Vector for the sides of the triangle ;
 TVector Normal ;
 TVector TempNormal ;
 double  D ;
 double  TempD ;

 // set the triangle points
 _P1=P1 ;
 _P2=P2 ;
 _P3=P3 ;

 // now work out the plane the triangle is in
 Side1=_P1-_P2 ;
 Side2=_P3-_P2 ;
 Normal=(Side2*Side1).Unit() ;
 D=Normal.Dot(P1) ;
 _Plane=TPlane(Normal,D,TSurfaceProperties());
}

// Find the intersection of a plane and a line
double TSimpleTriangle::Intersection (TVector &Point,TVector &Normal,
                            const TLine &Line) const
{
 TVector LineDirection ;
 TVector P1,P2,P3;
 TVector Side1,Side2,Side3 ;
 double Distance;
 double Flag1,Flag2,Flag3 ;

 LineDirection=(Line.EndPoint()-Line.StartPoint()).Unit() ;

 // find the distance to the intersection
 Distance=_Plane.Intersection(Point,Normal,Line) ;

 if (GreaterThanZero(Distance))
   {
    // check to see if the ray hits the triangle

    // translate the points
    P1=_P1-Point ;
    P2=_P2-Point ;
    P3=_P3-Point ;

    // create the sides
    Side1=P1*P2 ;
    Side2=P2*P3 ;
    Side3=P3*P1 ;

    Flag1=(Side1.Dot(Side2));;
    Flag2=(Side2.Dot(Side3));
    Flag3=(Side3.Dot(Side1));

    // check the Flag to see if all 3 are greater than 0
    if ((LessThanZero(Flag1))||(LessThanZero(Flag2))||(LessThanZero(Flag3)))
      {
       // no intersection, so set the distance to a negative number
       Distance=-1000 ;
      }
   }

 // return the distance
 return Distance ;

}

// function to input a plane
istream &TSimpleTriangle::Read (istream &In)
{
 char Comma ; // delimter for the items
 char Bracket ; // delimiter for vector and colour parts
 TVector P1 ;
 TVector P2 ;
 TVector P3 ;
 TColour Colour;
 double  Diffuse ;
 double  Specular ;
 double  Shine ;
 int     Roughness ;

 // read in the colour
 In>>Bracket>>P1>>Bracket>>Comma>>Bracket>>P2>>Bracket>>Comma>>Bracket>>
   P3>>Bracket>>Comma>>Bracket>>Colour>>Bracket>>Comma>>Diffuse>>Comma>>
   Specular>>Comma>>Shine>>Comma>>Roughness ;

 // copy to the object
 (*this)=TSimpleTriangle(P1,P2,P3,
         TSurfaceProperties(Colour,Diffuse,Specular,Shine,Roughness)) ;

 // return the stream
 return In ;
}

// function to output a colour
ostream &TSimpleTriangle::Write (ostream &Out) const
{
 // write out the colour
 Out<<'('<<_P1<<')'<<','<<'('<<_P2<<')'<<','<<'('<<_P3<<')'
    <<'('<<(*this).Colour()<<','<<(*this).Diffuse()<<','
    <<(*this).Specular()<<','<<(*this).Shine()<<','
    <<(*this).Roughness()<<')' ;

 // return the stream
 return Out ;
}

// function to read in a plane
istream &operator>>(istream &In,TSimpleTriangle &SimpleTriangle)
{
 // input a plane
 return SimpleTriangle.Read(In) ;
}

ostream &operator<<(ostream &Out,const TSimpleTriangle &SimpleTriangle)
{
 // output the colour
 return SimpleTriangle.Write(Out) ;
}
