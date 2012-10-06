/** @file
 *	@brief Contain constant used everywhere.
 *
 **/

#ifndef CONST_H
	/**
	 * @brief Header guard for const.h. Guard only definition that doesn't depend on physvector.
	 * A second Guard is used for physvector.
	 **/
	#define CONST_H

//Variable giving parameter of calculation like space spacing and method used.
	/**
	 * @brief Dimension used for calculation
	 **/
	#define DIM_DEF 3

	/**
	 * @brief Dimension used for calculation
	 **/
	const int DIM = DIM_DEF;

	/**
	 * @brief Boolean saying if we use an equation of state for Pressure
	 **/
	const bool presure_eq_state = true;

	/**
	 * @brief Boolenan saying if we calculate the laplacien for incompressible sph
	 **/
	const bool presure_laplacien = false;
	#define PRESSURE_LAPLACIEN
	/**
	 * @brief Boolean saying if in incompressible sph we guess the pressure.
	 * @deprecated May be removed
	 **/
	const bool pressure_guess_pressure = false;

	/**
	 * @brief Global Variable indicating the mass needed to have a correct mass density.
	 *
	 * Actually this is defined as the minimal mass needed because in boundary we will have a smaller density.
	 * So mass will be bigger.
	 **/
	extern double MEAN_MASS;

	extern double DT_ACT;
	/**
	 * @brief Global variable used for efficiency purpose.
	 * \code
	 *  DIV_MEAN_MASS=1/MEAN_MASS;
	 *	\endcode
	 **/
	extern double DIV_MEAN_MASS;

	/**
	 * @brief Preprocessore variable, if defined the equation of state will be used.
	 **/
	//#define PRESSURE_EQ_STATE
	//#define PRESSURE_LAPLACIEN

	/**
	 * @brief Distance after witch kernel is 0.
	 **/
	const double h = 0.03;

	/**
	 * @brief Time step size.
	 **/
	const double DT = 1;

#endif // CONST_H

#ifdef DOXYGEN
	#include "physvector.h" 
#endif

#ifndef CONST_H_VECTOR
    #ifdef VECTOR_FINISH        //Assure that physvector is enterely defined.

		/**
		 * @brief Preprocessor Variable used only for compilation purpose.
		 * It's defined when the constant as \f$ g \f$ are defined.
		 **/
		#define CONST_H_VECTOR
//Definition of the gravity constant.

	#if DIM_DEF==3
			/**
			 * @brief Vector G for gravity. It's value is \f$ -9.81 e_y \f$ .
			 **/
			const physvector < DIM > G = physvector < DIM > (0, -9.81, 0);
	#endif

	#if DIM_DEF==2
			/**
			 * @brief Vector G for gravity. It's value is \f$ -9.81 e_y \f$ .
			 **/
			const physvector < DIM > G = physvector < DIM > (0, -9.81);
	#endif
    #endif
	//POSITION_H
#endif //CONST_H_VECTOR
