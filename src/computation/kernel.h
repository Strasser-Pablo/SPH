

#ifndef KERNEL_H
#define KERNEL_H
#include "physvector.h"
#include "const.h"
#include <cmath>
/** \file kernel.h Contain all the kernel function used
 *
 **/

/**
 * @brief Sign function.
 *
 * \f[ sign(x)=\begin{cases}-1& \text{if $x<0$}\\ 0& \text{if $x=0$}\\ 1& \text{if $x>0$}  \end{cases}
 \f]
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
inline double Kernel_Density(physvector<DIM> vect,double h_ ) {
    double ret=315.0/(64*M_PI*pow(h_,9))*pow(pow(h_,2)-vect.Norm2(),3);
    if(ret<=0){
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
inline physvector<DIM>  Kernel_Pressure_Der(physvector<DIM> vect,double h_ ) {
    double x,y,z;
    double d=vect.Norm();
    double c=pow(h_-d,2);
    if(c>0){
    }
    vect.Get(x,y,z);
    if (abs(d)<0.001) {
        x=-sign(x)*45/(M_PI*pow(h_,6));
    }
    else {
        x=-x/d*45/(M_PI*pow(h_,6))*c;
    }
    if (abs(d)<0.001) {
        y=-sign(y)*45/(M_PI*pow(h_,6));
    } else {
        y=-y/d*45/(M_PI*pow(h_,6))*c;
    }
    if (abs(d)<0.001) {
        z=-sign(z)*45/(M_PI*pow(h_,6));
    } else {
        z=-z/d*45/(M_PI*pow(h_,6))*c;
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
inline double Kernel_viscosity_laplacian(physvector<DIM> vect,double h_){
 return 45/(M_PI*pow(h_,6))*(h_-vect.Norm2());
}

/**
 * @brief QSpline kernel
 * With \f$ h \f$, and \f$ v \f$ the argument.
 * \f[ s=3\left|\left|\frac{v}{h}\right|\right| \f]
 * \f[ splin5(s)=\frac{1}{80\pi h} \begin{cases} (3-s)^5-6(2-s)^5+15(1-s)^5 & \text{if $s<1$}\\
 * (3-s)^5-6(2-s)^5& \text{if $s<2$}\\
 * (3-s)^5& \text{if $s<3$}\\
 *  0& \text{if $s\geq 3$} \end{cases}  \f]
 * @param vect position to consider
 * @param h compact suport after witch the result is 0.
 * @return double
 **/
inline double Kernel_spline5(physvector<DIM> vect,double h_ ){
 double d=(3/h_*vect).Norm();
 double ret;
 if(d<1){
   ret=pow(3-d,5)-6*pow(2-d,5)+15*pow(1-d,5);
 }
 else if(d<2){
      ret=pow(3-d,5)-6*pow(2-d,5);
 }else if(d<3){
  ret=pow(3-d,5);
}else{
   ret=0;
}
ret=ret*1/(120*M_PI*pow(h_,3));
return ret;
}

/**
 * @brief Qspline kernel gradiant
 *
 * With \f$ h \f$, and \f$ v \f$ the argument.
 * \f[ s=3\left|\left|\frac{v}{h}\right|\right| \f]
 * \f[ splin5\_grad(s)=\frac{1}{80\pi h}\frac{v}{||v||}
 * \begin{cases} 0 & \text{if $s=0$}\\
 * (3-s)^5-6(2-s)^5+15(1-s)^5 & \text{if $s<1$}\\
 * (3-s)^5-6(2-s)^5& \text{if $s<2$}\\
 * (3-s)^5& \text{if $s<3$}\\
 *  0& \text{if $s\geq 3$} \end{cases}  \f]
 * @param vect vector of value
 * @param h compact suport
 * @return physvector< 3 >
 **/
inline physvector<DIM> Kernel_grad_spline5(physvector<DIM> vect,double h_ ){
 double d=(3/h_*vect).Norm();
 if(vect.Norm()==0){
  return physvector< DIM>();
 }
 double ret;
 if(d<1){
   ret=(-5*pow(3-d,4)+30*pow(2-d,4)-75*pow(1-d,4));
 }
 else if(d<2){
      ret=(-5*pow(3-d,4)+30*pow(2-d,4));
 }else if(d<3){
  ret=-5*pow(3-d,5);
}else{
 ret=0;
}
physvector<DIM> rret=ret*1/(40*M_PI*pow(h_,4))*vect/vect.Norm();
return rret;
}

/**
 * @brief Qspline kernel Directional derivatif.
 *
 * With \f$ h \f$, and \f$ v \f$ the argument.
 * \f[ s=3\left|\left|\frac{v}{h}\right|\right| \f]
 * \f[ splin5\_grad(s)=\frac{1}{80\pi h}\frac{v}{||v||}
 * \begin{cases} 0 & \text{if $s=0$}\\
 * (3-s)^5-6(2-s)^5+15(1-s)^5 & \text{if $s<1$}\\
 * (3-s)^5-6(2-s)^5& \text{if $s<2$}\\
 * (3-s)^5& \text{if $s<3$}\\
 *  0& \text{if $s\geq 3$} \end{cases}  \f]
 * @param vect vector of value
 * @param h compact suport
 * @return double directional derivatif.
 **/
inline double Kernel_grad_spline5_dir(physvector<DIM> vect,double h_ ){
 double d=(3/h_*vect).Norm();
 if(vect.Norm()==0){
  return 0.0;
 }
 double ret;
 if(d<1){
   ret=(-5*pow(3-d,4)+30*pow(2-d,4)-75*pow(1-d,4));
 }
 else if(d<2){
      ret=(-5*pow(3-d,4)+30*pow(2-d,4));
 }else if(d<3){
  ret=-5*pow(3-d,5);
}else{
 ret=0;
}
return ret*1/(40*M_PI*pow(h_,4));

}
#endif // KERNEL_H
