
#ifndef CONST_H
#define CONST_H
#include "physvector.h"
/**
 * @brief Dimension used for calculation 
 **/
#define DIM_DEF 3
const int DIM=DIM_DEF;





/**
 * @brief Distance after witch kernel is 0.
 **/
const double h=1.0;
static const bool D3=DIM==3;
static const bool D2=DIM==2;
#if DIM_DEF==3
const  physvector<DIM> G=physvector<DIM>(0,-9.81,0);
#endif

#if DIM_DEF==2
const  physvector<DIM> G=physvector<DIM>(0,-9.81);
#endif



#endif // CONST_H