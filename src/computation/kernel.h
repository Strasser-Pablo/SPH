

#ifndef KERNEL_H
#define KERNEL_H
#include "physvector.h"
#include "const.h"
#include <cmath>
/** \file kernel.h Contain all the kernel function used
 * 
 **/

/**
 * @brief Sign function
 *
 * Return +1 if positif, -1 if negatif . 0 if 0.
 * @param x number to test
 * @return double value of the function.
 **/
inline double sign(double x) {
    if (x>0) {
        return 1;
    }
    else if (x<0) {
        return -1;
    }
    else if (x==0) {
        return 0;
    }
}


/**
 * @brief Kernel for the Density
 *
 * @param vect postion  where to evaluate the kernel
 * @param h distance h for the kernel
 * @return double Value at the given point
 **/
inline double Kernel_Density(physvector<DIM> vect,double h ) {
    double ret=315.0/(64*M_PI*pow(h,9))*pow(pow(h,2)-vect.Norm2(),3);
    if(ret<=0){
    cout<<vect.Norm2()<<" "<<pow(h,2)<<endl;
    }
    return ret;
}

/**
 * @brief Gradiant of the Kernel for the Pressure
 *
 * @param vect postion  where to evaluate the kernel
 * @param h distance h for the kernel
 * @return double Value at the given point
 **/
inline physvector<DIM>  Kernel_Pressure_Der(physvector<DIM> vect,double h ) {
    double x,y,z;
    double d=vect.Norm();
    double c=pow(h-d,2);
    if(c>0){ 
    }
    vect.Get(x,y,z);
    if (abs(d)<0.001) {
        x=-sign(x)*45/(M_PI*pow(h,6));
    }
    else {
        x=-x/d*45/(M_PI*pow(h,6))*c;
    }
    if (abs(d)<0.001) {
        y=-sign(y)*45/(M_PI*pow(h,6));
    } else {
        y=-y/d*45/(M_PI*pow(h,6))*c;
    }
    if (abs(d)<0.001) {
        z=-sign(z)*45/(M_PI*pow(h,6));
    } else {
        z=-z/d*45/(M_PI*pow(h,6))*c;
    }
   return physvector<DIM>(x,y,z);
}

/**
 * @brief Laplacian of the Kernel for the Viscosity
 *
 * @param vect postion  where to evaluate the kernel
 * @param h distance h for the kernel
 * @return double Value at the given point
 **/
inline double Kernel_viscosity_laplacian(physvector<DIM> vect,double h){
 return 45/(M_PI*pow(h,6))*(h-vect.Norm2()); 
}

inline double Kernel_spline5(physvector<DIM> vect,double h ){
 double d=(3/h*vect).Norm();
 double ret;
 if(d<1./3){
   ret=pow(3-d,5)-6*pow(2-d,5)+15*pow(1-d,5);
 }
 else if(d<2./3){
      ret=pow(3-d,5)-6*pow(2-d,5);
 }else if(d<1.0){
  ret=pow(3-d,5);
}else{
   ret=0;
}
return ret*1/(80*M_PI*h);
}

inline physvector<DIM> Kernel_grad_spline5(physvector<DIM> vect,double h ){
 double d=(3/h*vect).Norm();
 double ret;
 if(d<1./3){
   ret=(-5*pow(3-d,4)+30*pow(2-d,4)-75*pow(1-d,4));
 }
 else if(d<2./3){
      ret=(-5*pow(3-d,4)+30*pow(2-d,4));
 }else if(d<1.0){
  ret=-5*pow(3-d,5);
}else{
  
}
return ret*1/(80*M_PI*h)*vect/d;
}
#endif // KERNEL_H
