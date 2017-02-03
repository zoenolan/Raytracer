/*****************************************************************************
 Cube Class

 NAME:cube.cpp
 DATE:17/12/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the plane header
#include "cube.h"
#include "zerotest.h"

#define BIGNUMBER 1000000

// Constructor
TCube::TCube ()
:TObject()
{
 _TopCorner=TVector(0,0,0) ;
 _BottomCorner=TVector(0,0,0) ;
}

// Constructor
TCube::TCube (TVector TopCorner,TVector BottomCorner,
              const TSurfaceProperties SurfaceProperties)
:TObject(SurfaceProperties)
{
 _TopCorner=TopCorner;
 _BottomCorner=BottomCorner ;
}

// Find the intersection of a plane and a line
double TCube::Intersection (TVector &Point,TVector &Normal,
                            const TLine &Line) const
{
 TVector LineDirection ;
 TVector NewNormal ;
 double t1,t2 ;
 double TNear,TFar ;
 int Hit ;
 double temp ;

 Hit=1 ;
 LineDirection=(Line.EndPoint()-Line.StartPoint()).Unit() ;

 TNear=-BIGNUMBER ;
 TFar=BIGNUMBER ;

 if (IsZero(LineDirection.X()))
   {
    if ((Line.StartPoint().X()<_BottomCorner.X())||
        (Line.StartPoint().X()>_TopCorner.X()))
      {
       // ray missed the cube
       Hit=0;
      }
   }
 else
   {
    // check the x slab
    t1=(_BottomCorner.X()-Line.StartPoint().X())/LineDirection.X() ;
    t2=(_TopCorner.X()-Line.StartPoint().X())/LineDirection.X() ;

    NewNormal=TVector(-1,0,0) ;

    if (t1>t2)
      {
       temp=t2 ;
       t2=t1 ;
       t1=temp ;
       NewNormal=-NewNormal ;
      }

    if (t1>TNear)
      {
       TNear=t1 ;
       Normal=NewNormal ;
      }

    if (t2<TFar)
      {
       TFar=t2 ;
      }

    if (TNear>TFar)
      {
       Hit=0;
      }

    if (TFar<0)
      {
       Hit=0 ;
      }

   }

 // check the Y slab
 if (IsZero(LineDirection.Y()))
   {
    if ((Line.StartPoint().Y()<_BottomCorner.Y())||
        (Line.StartPoint().Y()>_TopCorner.Y()))
      {
       // ray missed the cube
       Hit=0;
      }
   }
 else
   {
    // check the y slab
    t1=(_BottomCorner.Y()-Line.StartPoint().Y())/LineDirection.Y() ;
    t2=(_TopCorner.Y()-Line.StartPoint().Y())/LineDirection.Y() ;

    NewNormal=TVector(0,-1,0) ;

    if (t1>t2)
      {
       temp=t2 ;
       t2=t1 ;
       t1=temp ;
       NewNormal=-NewNormal ;
      }

    if (t1>TNear)
      {
       TNear=t1 ;
       Normal=NewNormal ;
      }

    if (t2<TFar)
      {
       TFar=t2 ;
      }

    if (TNear>TFar)
      {
       Hit=0;
      }

    if (TFar<0)
      {
       Hit=0 ;
      }

   }

 // do the Z slab
 if (IsZero(LineDirection.Z()))
   {
    if ((Line.StartPoint().Z()<_BottomCorner.Z())||
        (Line.StartPoint().Z()>_TopCorner.Z()))
      {
       // ray missed the cube
       Hit=0;
      }
   }
 else
   {
    // check the Z slab
    t1=(_BottomCorner.Z()-Line.StartPoint().Z())/LineDirection.Z() ;
    t2=(_TopCorner.Z()-Line.StartPoint().Z())/LineDirection.Z() ;

    NewNormal=TVector(0,0,-1) ;

    if (t1>t2)
      {
       temp=t2 ;
       t2=t1 ;
       t1=temp ;
       NewNormal=-NewNormal ;
      }

    if (t1>TNear)
      {
       TNear=t1 ;
       Normal=NewNormal ;
      }

    if (t2<TFar)
      {
       TFar=t2 ;
      }

    if (TNear>TFar)
      {
       Hit=0;
      }

    if (TFar<0)
      {
       Hit=0 ;
      }

   }

 // check to see if the cube has been missed
 if (Hit==0)
   {
    TNear=-BIGNUMBER ;
   }

 // now we can work out the intersection
 Point=Line.StartPoint()+(LineDirection*TNear) ;

 // now return the nearest one
 return TNear ;
}

// function to input a plane
istream &TCube::Read (istream &In)
{
 char Comma ; // delimter for the items
 char Bracket ; // delimiter for vector and colour parts
 TVector TopCorner ;
 TVector BottomCorner ;
 TColour Colour;
 double  Diffuse ;
 double  Specular ;
 double  Shine ;
 int     Roughness ;

 // read in the colour
 In>>Bracket>>TopCorner>>Bracket>>Comma>>Bracket>>BottomCorner>>Bracket
   >>Comma>>Bracket>>Colour>>Bracket>>Comma>>Diffuse>>Comma>>Specular>>
     Comma>>Shine>>Comma>>Roughness ;

 // copy to the object
 (*this)=TCube(TopCorner,BottomCorner,
         TSurfaceProperties(Colour,Diffuse,Specular,Shine,Roughness)) ;

 // return the stream
 return In ;
}

// function to output a colour
ostream &TCube::Write (ostream &Out) const
{
 // write out the colour
 Out<<'('<<_TopCorner<<')'<<','<<_BottomCorner<<','
    <<'('<<(*this).Colour()<<','<<(*this).Diffuse()<<','
    <<(*this).Specular()<<','<<(*this).Shine()<<','
    <<(*this).Roughness()<<')' ;

 // return the stream
 return Out ;
}

// function to read in a plane
istream &operator>>(istream &In,TCube &Cube)
{
 // input a plane
 return Cube.Read(In) ;
}

ostream &operator<<(ostream &Out,const TCube &Cube)
{
 // output the colour
 return Cube.Write(Out) ;

}
