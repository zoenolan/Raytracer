/******************************************************************************
 Raycaster Main file

 NAME:main.c
 DATE:11/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include "raycast.h"

main()
{
 cout<<"INFO:    Raytracer Version 1.0"<<endl ;
 cout<<"INFO:"<<endl ;
 cout<<"INFO:     22nd December 1996"<<endl;
 cout<<"INFO:     By Zoe Nolan"<<endl;
 cout<<"INFO:"<<endl ;
 cout<<"INFO: Opening data file"<<endl ;
 TRaycaster MyRaycaster("world.data") ;

 cout<<"INFO: Rendering Image"<<endl ;
 MyRaycaster.Render() ;

 cout<<"INFO: Displaying Image"<<endl ;
 MyRaycaster.Display() ;

}
