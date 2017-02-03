#ifndef matrix33_h
#define matrix33_h

/*****************************************************************************
 3 by 3 Matrix class

 NAME:matrix33.h
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include <iostream.h>
#include "vector.h"
class TMatrix33
{
 private:
    double _Mx[3][3] ;
    int    _Error ;

 public:
    // Constructors and Destructor
    TMatrix33 () ;
    TMatrix33 (double Element00,double Element01,double Element02,
               double Element10,double Element11,double Element12,
               double Element20,double Element21,double Element22) ;

    // Operators
    double operator()(int I,int J) const ;
    double &operator()(int I,int J) ;

    TMatrix33 operator+(const TMatrix33 &Matrix) const;
    TMatrix33 operator-(const TMatrix33 &Matrix) const;
    TMatrix33 operator+= (const TMatrix33 &Matrix) ;
    TMatrix33 operator-= (const TMatrix33 &Matrix) ;

    TMatrix33 &operator*= (const TMatrix33 &Matrix) ;
    TMatrix33 operator*(const TMatrix33 &Matrix) const;
    TMatrix33 operator*= (double Scalar) ;
    TMatrix33 operator*(double Scalar) const;

    // Rotation
    TMatrix33 RotateX (double Radian) const ;
    TMatrix33 RotateY (double Radian) const ;
    TMatrix33 RotateZ (double Radain) const ;

    // Scale
    TMatrix33 ScaleX (double Scalar) const ;
    TMatrix33 ScaleY (double Scalar) const ;
    TMatrix33 ScaleZ (double Scalar) const;

    // Other functions
    TMatrix33 Transpose() const ;
    TMatrix33 Invert() const ;
    double Determinant() const ;

    // Matrix * Vector
    TVector operator* (const TVector &Vector) ;

    // Streams
    friend ostream& operator<<(ostream &Out,const TMatrix33 &Matrix) ;

    // error checking function
    int Error() ;
};

#endif
