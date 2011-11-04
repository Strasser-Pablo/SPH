/** \file const.h Contain constant used everywhere.
 *
 **/


#ifndef CONST_H
#define CONST_H

/**
 * @brief Dimension used for calculation
 **/
#define DIM_DEF 3
const int DIM=DIM_DEF;

const bool presure_eq_state=true;
const bool presure_laplacien=false;
const bool pressure_guess_pressure=false;



/**
 * @brief Distance after witch kernel is 0.
 **/
const double h=0.015;

/**
 * @brief Time step size.
 **/
const double DT=0.01;
#endif // CONST_H

#ifndef CONST_H_VECTOR
#ifdef VECTOR_FINISH //Assure that physvector is enterely defined.

#define CONST_H_VECTOR


#if DIM_DEF==3
/**
 * @brief Vector G for gravity. It's value is \f$ -9.81 e_y \f$ .
 **/
const  physvector<DIM> G=physvector<DIM>(0,-9.81,0);
#endif

#if DIM_DEF==2
/**
 * @brief Vector G for gravity. It's value is \f$ -9.81 e_y \f$ .
 **/
const  physvector<DIM> G=physvector<DIM>(0,-9.81);
#endif
#endif //POSITION_H
#endif //CONST_H_VECTOR
