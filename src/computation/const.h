/** \file const.h Contain constant
 *  
 **/


#ifndef CONST_H
#define CONST_H

/**
 * @brief Dimension used for calculation 
 **/
#define DIM_DEF 3
const int DIM=DIM_DEF;





/**
 * @brief Distance after witch kernel is 0.
 **/
const double h=0.3;

/**
 * @brief Time step size.
 **/
const double DT=0.002;
#endif // CONST_H

#ifndef CONST_H_VECTOR
#ifdef VECTOR_FINISH //Assure that physvector is enterely defined.

#define CONST_H_VECTOR


#if DIM_DEF==3
/**
 * @brief Vector G for gravity
 **/
const  physvector<DIM> G=physvector<DIM>(0,0,0);
#endif

#if DIM_DEF==2
/**
 * @brief Vector G for gravity
 **/
const  physvector<DIM> G=physvector<DIM>(0,-9.81);
#endif 
#endif //POSITION_H
#endif //CONST_H_VECTOR