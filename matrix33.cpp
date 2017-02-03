/***************************************************************************
 3 by 3 Matrix class

 NAME  :matrix33.cpp
 DATE  :23/11/95
 AUTHOR: Z.A. Nolan

***************************************************************************/


#include <iostream.h>
#include <math.h>
#include "zerotest.h"
#include "matrix33.h"

// Default constructor that makes the matrix all zero
TMatrix33::TMatrix33()
{
 // set up the matrix as all zero's
 _Mx[0][0]=0 ;
 _Mx[0][1]=0 ;
 _Mx[0][2]=0 ;
 _Mx[1][0]=0 ;
 _Mx[1][1]=0 ;
 _Mx[1][2]=0 ;
 _Mx[2][0]=0 ;
 _Mx[2][1]=0 ;
 _Mx[2][2]=0 ;

 // set the error flag
 _Error=0 ;
}

// Constructor that set the matrix to whatever the parameters are
TMatrix33::TMatrix33
                     (double Element00,double Element10,double Element20,
                      double Element01,double Element11,double Element21,
                      double Element02,double Element12,double Element22)
{

 // set up the matrix as the values specified
 _Mx[0][0]=Element00 ;
 _Mx[1][0]=Element10 ;
 _Mx[2][0]=Element20 ;
 _Mx[0][1]=Element01 ;
 _Mx[1][1]=Element11 ;
 _Mx[2][1]=Element21 ;
 _Mx[0][2]=Element02 ;
 _Mx[1][2]=Element12 ;
 _Mx[2][2]=Element22 ;

 // Set the error flag
 _Error=0 ;
}

// () operator (Selector)
double TMatrix33::operator() (int I,int J) const
{

 // return the matrix item
 return _Mx [I][J] ;

}

// () operator (Modifier)
double &TMatrix33::operator() (int I,int J)
{

 // return the matrix item
 return _Mx[I][J] ;
}

// + operator
TMatrix33 TMatrix33::operator+ (const TMatrix33 &Matrix) const
{
 TMatrix33 Result ; // Result matrix

 // do the matrix addition
 Result._Mx[0][0]=_Mx[0][0]+Matrix._Mx[0][0] ;
 Result._Mx[1][0]=_Mx[1][0]+Matrix._Mx[1][0] ;
 Result._Mx[2][0]=_Mx[2][0]+Matrix._Mx[2][0] ;
 Result._Mx[0][1]=_Mx[0][1]+Matrix._Mx[0][1] ;
 Result._Mx[1][1]=_Mx[1][1]+Matrix._Mx[1][1] ;
 Result._Mx[2][1]=_Mx[2][1]+Matrix._Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][2]+Matrix._Mx[0][2] ;
 Result._Mx[1][2]=_Mx[1][2]+Matrix._Mx[1][2] ;
 Result._Mx[2][2]=_Mx[2][2]+Matrix._Mx[2][2] ;

 // return the result
 return (Result) ;
}

// - operator
TMatrix33 TMatrix33::operator- (const TMatrix33 &Matrix) const
{
 TMatrix33 Result ; // Result matrix

 // do the matrix subtraction
 Result._Mx[0][0]=_Mx[0][0]-Matrix._Mx[0][0] ;
 Result._Mx[1][0]=_Mx[1][0]-Matrix._Mx[1][0] ;
 Result._Mx[2][0]=_Mx[2][0]-Matrix._Mx[2][0] ;
 Result._Mx[0][1]=_Mx[0][1]-Matrix._Mx[0][1] ;
 Result._Mx[1][1]=_Mx[1][1]-Matrix._Mx[1][1] ;
 Result._Mx[2][1]=_Mx[2][1]-Matrix._Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][2]-Matrix._Mx[0][2] ;
 Result._Mx[1][2]=_Mx[1][2]-Matrix._Mx[1][2] ;
 Result._Mx[2][2]=_Mx[2][2]-Matrix._Mx[2][2] ;

 // return the result
 return (Result) ;
}

// += operator
TMatrix33 TMatrix33::operator+= (const TMatrix33 &Matrix)
{
 // do the += addition
 _Mx[0][0]+=Matrix._Mx[0][0] ;
 _Mx[1][0]+=Matrix._Mx[1][0] ;
 _Mx[2][0]+=Matrix._Mx[2][0] ;
 _Mx[0][1]+=Matrix._Mx[0][1] ;
 _Mx[1][1]+=Matrix._Mx[1][1] ;
 _Mx[2][1]+=Matrix._Mx[2][1] ;
 _Mx[0][2]+=Matrix._Mx[0][2] ;
 _Mx[1][2]+=Matrix._Mx[1][2] ;
 _Mx[2][2]+=Matrix._Mx[2][2] ;

}

// -= operator
TMatrix33 TMatrix33::operator-= (const TMatrix33 &Matrix)
{
 // do the -= subtraction
 _Mx[0][0]-=Matrix._Mx[0][0] ;
 _Mx[1][0]-=Matrix._Mx[1][0] ;
 _Mx[2][0]-=Matrix._Mx[2][0] ;
 _Mx[0][1]-=Matrix._Mx[0][1] ;
 _Mx[1][1]-=Matrix._Mx[1][1] ;
 _Mx[2][1]-=Matrix._Mx[2][1] ;
 _Mx[0][2]-=Matrix._Mx[0][2] ;
 _Mx[1][2]-=Matrix._Mx[1][2] ;
 _Mx[2][2]-=Matrix._Mx[2][2] ;

}

// * operator (for a matrix)
TMatrix33 TMatrix33::operator* (const TMatrix33 &Matrix) const
{
 TMatrix33 Result ;  // the result matrix

 // do the matrix multiply
 Result._Mx[0][0]=_Mx[0][0]*Matrix._Mx[0][0]+
                  _Mx[0][1]*Matrix._Mx[1][0]+
                  _Mx[0][2]*Matrix._Mx[2][0] ;
 Result._Mx[1][0]=_Mx[1][0]*Matrix._Mx[0][0]+
                  _Mx[1][1]*Matrix._Mx[1][0]+
                  _Mx[1][2]*Matrix._Mx[2][0] ;
 Result._Mx[2][0]=_Mx[2][0]*Matrix._Mx[0][0]+
                  _Mx[2][1]*Matrix._Mx[1][0]+
                  _Mx[2][2]*Matrix._Mx[2][0] ;
 Result._Mx[0][1]=_Mx[0][0]*Matrix._Mx[0][1]+
                  _Mx[0][1]*Matrix._Mx[1][1]+
                  _Mx[0][2]*Matrix._Mx[2][1] ;
 Result._Mx[1][1]=_Mx[1][0]*Matrix._Mx[0][1]+
                  _Mx[1][1]*Matrix._Mx[1][1]+
                  _Mx[1][2]*Matrix._Mx[2][1] ;
 Result._Mx[2][1]=_Mx[2][0]*Matrix._Mx[0][1]+
                  _Mx[2][1]*Matrix._Mx[1][1]+
                  _Mx[2][2]*Matrix._Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][0]*Matrix._Mx[0][2]+
                  _Mx[0][1]*Matrix._Mx[1][2]+
                  _Mx[0][2]*Matrix._Mx[2][2] ;
 Result._Mx[1][2]=_Mx[1][0]*Matrix._Mx[0][2]+
                  _Mx[1][1]*Matrix._Mx[1][2]+
                  _Mx[1][2]*Matrix._Mx[2][2] ;
 Result._Mx[2][2]=_Mx[2][0]*Matrix._Mx[0][2]+
                  _Mx[2][1]*Matrix._Mx[1][2]+
                  _Mx[2][2]*Matrix._Mx[2][2] ;

 // return the result
 return Result ;
}

// *= operator (for a matrix)
TMatrix33 &TMatrix33::operator*= (const TMatrix33 &Matrix)
{
 TMatrix33 Result ;  // the result matrix

 // Do the multiply
 Result._Mx[0][0]=_Mx[0][0]*Matrix._Mx[0][0]+
                  _Mx[0][1]*Matrix._Mx[1][0]+
                  _Mx[0][2]*Matrix._Mx[2][0] ;
 Result._Mx[1][0]=_Mx[1][0]*Matrix._Mx[0][0]+
                  _Mx[1][1]*Matrix._Mx[1][0]+
                  _Mx[1][2]*Matrix._Mx[2][0] ;
 Result._Mx[2][0]=_Mx[2][0]*Matrix._Mx[0][0]+
                  _Mx[2][1]*Matrix._Mx[1][0]+
                  _Mx[2][2]*Matrix._Mx[2][0] ;
 Result._Mx[0][1]=_Mx[0][0]*Matrix._Mx[0][1]+
                  _Mx[0][1]*Matrix._Mx[1][1]+
                  _Mx[0][2]*Matrix._Mx[2][1] ;
 Result._Mx[1][1]=_Mx[1][0]*Matrix._Mx[0][1]+
                  _Mx[1][1]*Matrix._Mx[1][1]+
                  _Mx[1][2]*Matrix._Mx[2][1] ;
 Result._Mx[2][1]=_Mx[2][0]*Matrix._Mx[0][1]+
                  _Mx[2][1]*Matrix._Mx[1][1]+
                  _Mx[2][2]*Matrix._Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][0]*Matrix._Mx[0][2]+
                  _Mx[0][1]*Matrix._Mx[1][2]+
                  _Mx[0][2]*Matrix._Mx[2][2] ;
 Result._Mx[1][2]=_Mx[1][0]*Matrix._Mx[0][2]+
                  _Mx[1][1]*Matrix._Mx[1][2]+
                  _Mx[1][2]*Matrix._Mx[2][2] ;
 Result._Mx[2][2]=_Mx[2][0]*Matrix._Mx[0][2]+
                  _Mx[2][1]*Matrix._Mx[1][2]+
                  _Mx[2][2]*Matrix._Mx[2][2] ;

 // copy the result to the matrix
 _Mx[0][0]=Result._Mx[0][0] ;
 _Mx[1][0]=Result._Mx[1][0] ;
 _Mx[2][0]=Result._Mx[2][0] ;
 _Mx[0][1]=Result._Mx[0][1] ;
 _Mx[1][1]=Result._Mx[1][1] ;
 _Mx[2][1]=Result._Mx[2][1] ;
 _Mx[0][2]=Result._Mx[0][2] ;
 _Mx[1][2]=Result._Mx[1][2] ;
 _Mx[2][2]=Result._Mx[2][2] ;

 // return the result
 return (*this) ;
}

// *= operator (for a scalar)
TMatrix33 TMatrix33::operator*= (double Scalar)
{

 // do the scalar multiply
 _Mx[0][0]*=Scalar ;
 _Mx[1][0]*=Scalar ;
 _Mx[2][0]*=Scalar ;
 _Mx[0][1]*=Scalar ;
 _Mx[1][1]*=Scalar ;
 _Mx[2][1]*=Scalar ;
 _Mx[0][2]*=Scalar ;
 _Mx[1][2]*=Scalar ;
 _Mx[2][2]*=Scalar ;

}

// * operator (for a scalar)
TMatrix33 TMatrix33::operator* (double Scalar) const
{
 TMatrix33 Result ;  // Result matrix

 // do the scalar multiply
 Result._Mx[0][0]=_Mx[0][0]*Scalar ;
 Result._Mx[1][0]=_Mx[1][0]*Scalar ;
 Result._Mx[2][0]=_Mx[2][0]*Scalar ;
 Result._Mx[0][1]=_Mx[0][1]*Scalar ;
 Result._Mx[1][1]=_Mx[1][1]*Scalar ;
 Result._Mx[2][1]=_Mx[2][1]*Scalar ;
 Result._Mx[0][2]=_Mx[0][2]*Scalar ;
 Result._Mx[1][2]=_Mx[1][2]*Scalar ;
 Result._Mx[2][2]=_Mx[2][2]*Scalar ;

 // return the result
 return Result ;
}

// scale the matrix in x
TMatrix33 TMatrix33::ScaleX(double Scalar) const
{
 TMatrix33 Result ; // result matrix

 // do the scaling in X
 Result._Mx[0][0]=_Mx[0][0]*Scalar ;
 Result._Mx[1][0]=_Mx[1][0] ;
 Result._Mx[2][0]=_Mx[2][0] ;
 Result._Mx[0][1]=_Mx[0][1] ;
 Result._Mx[1][1]=_Mx[1][1] ;
 Result._Mx[2][1]=_Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][2] ;
 Result._Mx[1][2]=_Mx[1][2] ;
 Result._Mx[2][2]=_Mx[2][2] ;

 // return the result
 return (Result) ;
}

// scale the matrix in y
TMatrix33 TMatrix33::ScaleY(double Scalar) const
{
 TMatrix33 Result ;  // result matrix

 // do the scaling in Y
 Result._Mx[0][0]=_Mx[0][0] ;
 Result._Mx[1][0]=_Mx[1][0]*Scalar ;
 Result._Mx[2][0]=_Mx[2][0] ;
 Result._Mx[0][1]=_Mx[0][1] ;
 Result._Mx[1][1]=_Mx[1][1] ;
 Result._Mx[2][1]=_Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][2] ;
 Result._Mx[1][2]=_Mx[1][2] ;
 Result._Mx[2][2]=_Mx[2][2] ;

 // return the result
 return (Result) ;
}

// scale the matrix in z
TMatrix33 TMatrix33::ScaleZ(double Scalar) const
{
 TMatrix33 Result ; // result matrix

 // do the scaling in Z
 Result._Mx[0][0]=_Mx[0][0] ;
 Result._Mx[1][0]=_Mx[1][0] ;
 Result._Mx[2][0]=_Mx[2][0]*Scalar ;
 Result._Mx[0][1]=_Mx[0][1] ;
 Result._Mx[1][1]=_Mx[1][1] ;
 Result._Mx[2][1]=_Mx[2][1] ;
 Result._Mx[0][2]=_Mx[0][2] ;
 Result._Mx[1][2]=_Mx[1][2] ;
 Result._Mx[2][2]=_Mx[2][2] ;

 // return the result
 return (Result) ;
}

// Rotate X
TMatrix33 TMatrix33::RotateX (double Radians) const
{
 TMatrix33 Result ; // result matrix
 double  CosValue,SinValue ; // cos aznd sin values

 // calculate the cos and sin
 CosValue=cos (Radians) ;
 SinValue=sin (Radians) ;

 // make the rotation matrix
 Result._Mx[0][0]=1 ;
 Result._Mx[1][0]=0 ;
 Result._Mx[2][0]=0 ;
 Result._Mx[0][1]=0 ;
 Result._Mx[1][1]=CosValue ;
 Result._Mx[2][1]=-SinValue ;
 Result._Mx[0][2]=0 ;
 Result._Mx[1][2]=SinValue ;
 Result._Mx[2][2]=CosValue ;

 // do the rotation
 Result=(*this)*Result ;

 // return the result
 return (Result) ;
}

// Rotate Y
TMatrix33 TMatrix33::RotateY (double Radians) const
{
 TMatrix33 Result ; // result matrix
 double  CosValue,SinValue ; // cos aznd sin values

 // calculate the cos and sin
 CosValue=cos (Radians) ;
 SinValue=sin (Radians) ;

 // make the rotation matrix
 Result._Mx[0][0]=CosValue ;
 Result._Mx[1][0]=0 ;
 Result._Mx[2][0]=SinValue ;
 Result._Mx[0][1]=0 ;
 Result._Mx[1][1]=1 ;
 Result._Mx[2][1]=0 ;
 Result._Mx[0][2]=-SinValue ;
 Result._Mx[1][2]=0 ;
 Result._Mx[2][2]=CosValue ;

 // do the rotation
 Result=(*this)*Result ;

 // return the result
 return (Result) ;
}

// Rotate Z
TMatrix33 TMatrix33::RotateZ (double Radians) const
{
 TMatrix33 Result ; // result matrix
 double  CosValue,SinValue ; // cos aznd sin values

 // calculate the cos and sin
 CosValue=cos (Radians) ;
 SinValue=sin (Radians) ;

 // make the rotation matrix
 Result._Mx[0][0]=CosValue ;
 Result._Mx[1][0]=-SinValue ;
 Result._Mx[2][0]=0 ;
 Result._Mx[0][1]=SinValue ;
 Result._Mx[1][1]=CosValue ;
 Result._Mx[2][1]=0 ;
 Result._Mx[0][2]=0 ;
 Result._Mx[1][2]=0 ;
 Result._Mx[2][2]=1 ;

 // do the rotation
 Result=(*this)*Result ;

 // return the result
 return (Result) ;
}

// Transpose function
TMatrix33 TMatrix33::Transpose () const
{
 TMatrix33 Result ;  // result matrix

 // transpose the matrix
 Result._Mx[0][0]=_Mx[0][0] ;
 Result._Mx[1][0]=_Mx[0][1] ;
 Result._Mx[2][0]=_Mx[0][2] ;
 Result._Mx[0][1]=_Mx[1][0] ;
 Result._Mx[1][1]=_Mx[1][1] ;
 Result._Mx[2][1]=_Mx[1][2] ;
 Result._Mx[0][2]=_Mx[2][0] ;
 Result._Mx[1][2]=_Mx[2][1] ;
 Result._Mx[2][2]=_Mx[2][2] ;

 // return the result
 return Result ;
}

// determinant
double TMatrix33::Determinant() const
{
 double Result ;  // the result

 // do the maths
 Result=_Mx[0][0]*_Mx[1][1]*_Mx[2][2]-_Mx[0][0]*_Mx[2][1]*_Mx[1][2]-
        _Mx[1][0]*_Mx[0][1]*_Mx[2][2]+_Mx[1][0]*_Mx[2][1]*_Mx[0][2]+
        _Mx[2][0]*_Mx[0][1]*_Mx[1][2]-_Mx[2][0]*_Mx[0][2]*_Mx[1][1] ;

 // return the result
 return (Result) ;

}


// Invert
TMatrix33 TMatrix33::Invert() const
{
 TMatrix33 Result ; // the result matrix
 double    Deter ;  // the determinant of the starting matrix

 // workout values and transpose the matrix
 Result._Mx[0][0]=(_Mx[1][1]*_Mx[2][2]-_Mx[2][1]*_Mx[1][2]) ;
 Result._Mx[0][1]=-(_Mx[0][1]*_Mx[2][2]-_Mx[2][1]*_Mx[0][2]) ;
 Result._Mx[0][2]=(_Mx[0][1]*_Mx[1][2]-_Mx[1][1]*_Mx[0][2]) ;

 Result._Mx[1][0]=-(_Mx[1][0]*_Mx[2][2]-_Mx[2][0]*_Mx[1][2]) ;
 Result._Mx[1][1]=(_Mx[0][0]*_Mx[2][2]-_Mx[2][0]*_Mx[0][2]) ;
 Result._Mx[1][2]=-(_Mx[0][0]*_Mx[1][2]-_Mx[1][1]*_Mx[0][2]) ;

 Result._Mx[2][0]=(_Mx[0][1]*_Mx[2][1]-_Mx[2][0]*_Mx[1][1]) ;
 Result._Mx[2][1]=-(_Mx[0][0]*_Mx[2][1]-_Mx[2][0]*_Mx[0][2]) ;
 Result._Mx[2][2]=(_Mx[0][0]*_Mx[1][1]-_Mx[1][0]*_Mx[0][1]) ;

 // do the scalar multiply and
 Deter=(*this).Determinant() ;

 // check for divide by zero
 if (IsZero(Deter))
   {
    Result=Result*(1/Deter) ;
   }
 else
   {
    Result._Error=1 ;
   }

 // return the result /
 return (Result) ;
}


// function to check the error flag
int TMatrix33::Error()
{
 // return flase if no error has happened else return true
 if (_Error==0)
   {
    return (0) ;
   }
 else
   {
    return (1) ;
   }
}


// function to output a matrix
ostream& operator<<(ostream &Out,const TMatrix33 &Matrix)
{
 // output the matrix
 return Out
        <<Matrix._Mx[0][0]<<'|'<<Matrix._Mx[1][0]<<'|'<<Matrix._Mx[2][0]<<endl
        <<Matrix._Mx[0][1]<<'|'<<Matrix._Mx[1][1]<<'|'<<Matrix._Mx[2][1]<<endl
        <<Matrix._Mx[0][2]<<'|'<<Matrix._Mx[1][2]<<'|'<<Matrix._Mx[2][2]<<endl;
}

// function to do Matrix*Vector
TVector TMatrix33::operator* (const TVector &Vector) const
{
 TVector Result  // result vector
   (
 // do the *

    (Vector.X()*_Mx[0][0])+(Vector.Y()*_Mx[1][0])+(Vector.Z()*_Mx[2][0]),
    (Vector.X()*_Mx[0][1])+(Vector.Y()*_Mx[1][1])+(Vector.Z()*_Mx[2][1]),
    (Vector.X()*_Mx[0][2])+(Vector.Y()*_Mx[1][2])+(Vector.Z()*_Mx[2][2])
   ) ;

  // return the result
  return Result ;
}
