/*****************************************************************************
 Base class for all object in the raycaster/raytracer

 NAME:object.cpp
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the header file
#include "object.h"

// constructor
TObject::TObject ()
{
 _SurfaceProperties=TSurfaceProperties() ;
}

TObject::TObject (const TSurfaceProperties SurfaceProperties)

{
 _SurfaceProperties=SurfaceProperties ;
}

// return the colour of the object
TColour TObject::Colour() const
{
 return _SurfaceProperties.Colour() ;
}

// return the diffuse value of the object of the object
double TObject::Diffuse() const
{
 return _SurfaceProperties.Diffuse() ;
}

// return the specular value of the object
double TObject::Specular() const
{
 return _SurfaceProperties.Specular() ;
}

// return the roughness of the object
int TObject::Roughness() const
{
 return _SurfaceProperties.Roughness() ;
}

// return the shine of the object
double TObject::Shine() const
{
 return _SurfaceProperties.Shine() ;
}

// return the shine of the object
TSurfaceProperties TObject::SurfaceProperties() const
{
 return _SurfaceProperties ;
}

// copy the surface properties
TObject::Copy(const TSurfaceProperties &Surface)
{
 _SurfaceProperties=Surface ;
}
