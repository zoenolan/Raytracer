/*****************************************************************************
 Triangle Mesh Class

 NAME:tmesh.cpp
 DATE:17/12/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the triangle mesh header
#include "tmesh.h"

#include <string.h>
#include "zerotest.h"

// Constructor
TTriangleMesh::TTriangleMesh()
:TObject(),
_PointList(TPointerQueue<TVector>()),
_TriangleList(TPointerQueue<TTriangleMesh::TTriangleDef>())
{
}

// Find the intersection of a plane and a line
double TTriangleMesh::Intersection (TVector &Point,TVector &Normal,
                            const TLine &Line) const
{
  double Distance,NewDistance ;
 TVector NewPoint,NewNormal ;
 TSimpleTriangle Triangle ;
 int counter ;

 Distance=-1000 ;
 cout<<"hello"<<endl ;
 for (counter=0;counter<_TriangleList.Size();counter++)
   {
    // get the triangle
    Triangle=TSimpleTriangle(*_PointList[_TriangleList[counter]->Point1()],
                             *_PointList[_TriangleList[counter]->Point2()],
                             *_PointList[_TriangleList[counter]->Point3()],
                             TSurfaceProperties()) ;

     cout<<*_PointList[_TriangleList[counter]->Point1()] ;
     // *_PointList[_TriangleList[counter]->Point2()]<<" "<<
     // *_PointList[_TriangleList[counter]->Point3()]<<endl ;
    // find the distance to the intersection
    NewDistance=Triangle.Intersection(NewPoint,NewNormal,Line) ;

    if (GreaterThanZero(NewDistance))
      {
       // check to see if the ray hits the triangle nearer than the last
       if ((NewDistance<Distance)||(LessThanZero(Distance)))
         {
          Distance=NewDistance ;
         }
      }
    }

 // return the distance
 return Distance ;

}

// function to input a plane
istream &TTriangleMesh::Read (istream &In)
{
 char Comma ; // delimter for the items
 char Bracket ; // delimiter for vector and colour parts
 char ObjectType[6] ;
 TVector P1 ;
 int Index1,Index2,Index3 ;
 TColour Colour;
 double  Diffuse ;
 double  Specular ;
 double  Shine ;
 int     Roughness ;
 int End=0 ;

 while (End!=1)
   {
    In>>ObjectType ;

    if ((strncmp(ObjectType,"vertex",6))==0)
      {
       In>>Bracket>>P1>>Bracket ;
       _PointList.Add(new TVector (P1)) ;
      }

    else if ((strncmp(ObjectType,"tridef",6))==0)
      {
       In>>Bracket>>Index1>>Comma>>Index2>>Comma>>Index3>>Bracket ;
       _TriangleList.Add(new TTriangleMesh::TTriangleDef
                                         (Index1,Index2,Index3)) ;
      }

    else if ((strncmp(ObjectType,"colour",6))==0)
      {
       In>>Bracket>>Bracket>>Colour>>Bracket>>Comma>>Diffuse>>Comma>>
       Specular>>Comma>>Shine>>Comma>>Roughness>>Bracket ;

       (*this).Copy(TSurfaceProperties(Colour,Diffuse,Specular,
                    Shine,Roughness)) ;
      }

    else
      {
       End=1 ;
      }
   }

 // return the stream
 return In ;
}

// function to output a colour
ostream &TTriangleMesh::Write (ostream &Out) const
{
 // write out the colour
 Out<<"Triangle Mesh" ;

 // return the stream
 return Out ;
}

// function to read in a plane
istream &operator>>(istream &In,TTriangleMesh &TriangleMesh)
{
 // input a mesh
 return TriangleMesh.Read(In) ;
}

ostream &operator<<(ostream &Out,const TTriangleMesh &TriangleMesh)
{
 // output the colour
 return TriangleMesh.Write(Out) ;
}


TTriangleMesh::TTriangleMesh (TPointerQueue<TVector> &Points,
                              TPointerQueue<TTriangleDef> &TDef,
		               TSurfaceProperties &SurfaceProperties)
:TObject(SurfaceProperties)
{
 _PointList=Points ;
 _TriangleList=TDef ;
}

TTriangleMesh::TTriangleMesh (TTriangleMesh &TMesh)
:TObject(TMesh.SurfaceProperties())
{
 _PointList=TMesh._PointList ;
 _TriangleList=TMesh._TriangleList ;
}


TTriangleMesh::operator= (TTriangleMesh &TMesh)
{
 _PointList=TMesh._PointList ;
 _TriangleList=TMesh._TriangleList ;
 (*this).Copy(TMesh.SurfaceProperties()) ;
}

TTriangleMesh::TTriangleDef::TTriangleDef()
{
 _Point1=0 ;
 _Point2=0 ;
 _Point3=0 ;
}

TTriangleMesh::TTriangleDef::TTriangleDef(int A,int B,int C)
{
 _Point1=A ;
 _Point2=B ;
 _Point3=C ;
}

int TTriangleMesh::TTriangleDef::Point1() const
{
 return _Point1 ;
}


int TTriangleMesh::TTriangleDef::Point2() const
{
 return _Point2 ;
}


int TTriangleMesh::TTriangleDef::Point3() const
{
 return _Point3 ;
}
