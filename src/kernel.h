

#ifndef KERNEL_H
#define KERNEL_H
#include "physvector.h"
#include "const.h"
#include <cmath>
/**
 * @brief Kernel for the Density
 * 
 * @param vect postion  where to evaluate the kernel
 * @param h distance h for the kernel
 * @return double Value at the given point
 **/
inline double Kernel_Density(physvector<DIM> vect,double h ){
 return 315.0/(64*M_PI*pow(h,9))*pow(pow(h,2)-vect.Norm2(),3);
}
  #endif // KERNEL_H