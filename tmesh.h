#ifndef tmesh_h
#define tmesh_h

/*****************************************************************************
 Triangle Mesh Class

 NAME:tmesh.h
 DATE:17/12/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include vector class
#include "vector.h"

// and the colour class
#include "colour.h"

// and the line class
#include "line.h"

// and include the object class
#include "object.h"

// and include the triangle class class
#include "tri.h"

// include the queue class
#include "pqueue.h"

class TTriangleMesh :public TObject
{
 private:

   class TTriangleDef
     {
      private:
        int _Point1 ;
        int _Point2 ;
        int _Point3 ;

     public:
        TTriangleDef() ;
        TTriangleDef(int A,int B,int C) ;

        int Point1() const;
        int Point2() const;
        int Point3() const;
     } ;

   TPointerQueue <TVector> _PointList    ;
   TPointerQueue <TTriangleMesh::TTriangleDef> _TriangleList ;

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

public:
   // Constructors
   TTriangleMesh () ;
   TTriangleMesh (TPointerQueue<TVector> &Points,
                  TPointerQueue<TTriangleDef> &TDef,
		  TSurfaceProperties &SurfaceProperties)  ;
   TTriangleMesh (TTriangleMesh &TMesh) ;
   operator= (TTriangleMesh &TMesh) ;

   // Intersection of a line and a plane
   double Intersection(TVector &Point,TVector &Normal,const TLine &Line) const;

   // streaming operators
   friend istream &operator>>(istream &In, TTriangleMesh &TriangleMesh);
   friend ostream &operator<<(ostream &Out,const TTriangleMesh
			                         &TriangleMesh) ;
} ;
#endif
