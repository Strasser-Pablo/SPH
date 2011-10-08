

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
    return 315.0/(64*M_PI*pow(h,9))*pow(pow(h,2)-vect.Norm2(),3);
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
    double d=vect.Norm2();
    vect.Get(x,y,z);
    if (abs(x)<0.001) {
        x=sign(x)*45/(M_PI*pow(h,6));
    }
    else {
        x=x/d*45/(M_PI*pow(h,6))*pow(h-d,2);
    }
    if (abs(y)<0.001) {
        y=sign(y)*45/(M_PI*pow(h,6));
    } else {
        y=y/d*45/(M_PI*pow(h,6))*pow(h-d,2);
    }
    if (abs(z)<0.001) {
        z=sign(z)*45/(M_PI*pow(h,6));
    } else {
        z=z/d*45/(M_PI*pow(h,6))*pow(h-d,2);
    }
    physvector<DIM>(x,y,z);
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
#endif // KERNEL_H