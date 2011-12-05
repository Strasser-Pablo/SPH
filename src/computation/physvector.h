/*
   Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
 */

#ifndef POSITION_H
	#define POSITION_H
#include <iostream>
#include <fstream>
#include "key.h"

	/**
	 * @brief Class that cannot be used. Only spezialitation can be used.
	 *
	 **/
	template<int N=3>
	class physvector {
	inline physvector();
public:
	inline double Distance2(physvector<N> A);
	};


	/**
	 * @brief Specialized class for 3d vector.
	 *
	 * This class has overloaded member for addition, substraction, dot product.
	 **/
	template<>
	class physvector<3> {

	double m_x;
	double m_y;
	double m_z;
public:
	/**
	 * @brief Create a null 3d vector
	 *
	 **/
	inline physvector();
	/**
	 * @brief create a 3d vector
	 *
	 * @param x xvalue
	 * @param y yvalue
	 * @param z yvalue
	 **/
	inline physvector(const double x,const double y,const double z);
	
	
	inline void Set(const double x,const double y,const double z);

	/**
	 * @brief Get the value of the vector
	 *
	 * @param x Reference that will be modified to the xvalue
	 * @param y Reference that will be modified to the yvalue
	 * @param z Reference that will be modified to the zvalue
	 * @return void
	 **/
	inline void Get(double &x,double &y,double &z) const;
	
	/**
	   *@brief Asignement. Assign argument.
	 * @param A Vector to assign.
	 * @return void.
	 **/
	inline void operator=( const physvector<3> &A);
	
	/**
	 * @brief Output Stream Operator for cout<< for example
	 *
	 * @param stream
	 * @param A physvector to output
	 * @return :ostream&
	 **/
	friend std::ostream& operator<< (std::ostream& stream, const physvector<3>& A );
	/**
	 * @brief Convert the physvector position to key with the good index given by h spacing.
	 *
	 * @param h
	 * @return Key<3> Key in wish container this position is.
	 **/
	inline Key<3> ToKey(double h);
	/**
	 * @brief Return true if it's a null vector.
	 **/
	inline bool IsNull() const;
	/**
	 * @brief Write position to stream. In a format compatible with paraview.
	 *
	 * @param out Stream to output.
	 **/
	inline void WritePos(fstream & out) const;
	inline void WritePosOneLine(fstream & out) const;
	
	inline bool operator<(const physvector<3> A) const;
	inline bool operator<=(const physvector<3> A) const;
	inline bool operator>=(const physvector<3> A) const;
	inline bool operator==(const physvector<3> A) const;
	inline void To0();
	
	/**
	 * @name Distance
	 **/
	 //@{
	 /**
	 * @brief Get the euclidian distance \f$\sqrt{(x-x2)^2+(y-y2)^2+(z-z2)^2}\f$
	 *
	 * @param A Other vector
	 * @return double Distance.
	 **/
	inline double Distance(const physvector<3>& A) const;
	/**
	 * @brief Get the square euclidian distance \f$(x-x2)^2+(y-y2)^2+(z-z2)^2\f$
	 *
	 * @param A Other vector
	 * @return double Distance
	 **/
	inline double Distance2(const physvector<3>& A) const;

	/**
	 * @brief Get the max distance \f$ max(|x-x2|,|y-y2|,|z-z2|) \f$
	 *
	 * @param A Other vector
	 * @return double Distance
	 **/
	inline double DistanceMax(const physvector<3>& A) const;
	/**
	 * @brief Calculate the euclidian norm \f$\sqrt{x^2+y^2+z^2}\f$
	 *
	 * @return double
	 **/
	inline double Norm() const;
	/**
	 * @brief Calculate the euclidian norm square \f$x^2+y^2+z^2\f$
	 *
	 * @return double
	 **/
	inline double Norm2() const;

	/**
	 * @brief Calculate the maximun norm \f$ max(x,y,z) \f$
	 *
	 * @return double
	 **/
	inline double NormMax() const;
	/**
	 * @brief Set the value of the vector
	 *
	 * @param x xvalue
	 * @param y yvalue
	 * @param z zvalue
	 * @return void
	 **/
	 //@}
	
	/**
	 * @name Operation
	 **/
	 //@{
	 
	 /**
	 * @brief Add element by element. Overload + operator.
	 * @param A physvector to add.
	 * @return physvector<3> added vector.
	 **/
	inline physvector<3> operator+(const physvector<3>& A) const;
	/**
	 * @brief Make Dot Product for two vector. Overload * operator.
	 * @param A physvector to Multiply.
	 * @return double Result from dot product.
	 **/
	inline double operator*(const physvector<3>& A) const;
	/**
	 * @brief Substract element by element. Overload - operator.
	 * @param A physvector to substract.
	 * @return physvector<3> Substracted vector.
	 **/
	inline physvector<3> operator-(const physvector<3>& A) const;
	/**
	 * @brief Unary minus element by element. Overload - operator.
	 * @return physvector<3>  minus vector.
	 **/
	inline physvector<3> operator-() const;
	
	/**
	 * @brief Assign and add. Add the current vector to the argument vector, element by element.
	 *
	 * @param A vector to add.
	 * @return void.
	 **/
	inline void operator+=(const physvector<3> &A);
	/**
	 * @brief Assign and substract. Stbstract the current vector to the argument vector, element by element.
	 *
	 * @param A vector to Subtstract.
	 * @return void.
	 **/
	inline void operator-=(const physvector<3> &A);
	/**
	 * @brief Assign and Multiply. Multiply the current vector to the argument vector, element by element.
	 *
	 * @param c constant to Multiply.
	 * @return void.
	 **/
	inline void operator*=(const double c);
	/**
	 * @brief Divide all element by the constant.
	 *
	 * @param c constant to divide by.
	 * @return physvector<3> after division.
	 **/
	inline physvector<3> operator/(const double c) const;
	
	friend inline physvector< 3> operator*(const double c,const physvector<3>& a);
	friend inline physvector< 3> operator*(const physvector<3>& a,const double c);
	 
	 /**
	 * @brief Component by component product.
	 *
	 * @param a Element to multiply by.
	 **/
	inline physvector<3> prod(const physvector<3>& a) const;
	
	 //@}
	 
	
   #ifndef DOXYGEN
private:
   #endif     //DOXYGEN

	};




	/**
	 * @brief Specialized class for 2d vector
	 *
	 **/
	template<>
	class physvector<2> {

	double m_x;
	double m_y;
public:
	/**
	 * @brief Create a null 2d vector
	 *
	 **/
	inline physvector();
	/**
	 * @brief create a 2d vector
	 *
	 * @param x xvalue
	 * @param y yvalue
	 **/
	inline physvector(const double x,const double y);
	
	/**
	 * @brief Set the value of the vector
	 *
	 * @param x xvalue
	 * @param y yvalue
	 * @return void
	 **/
	inline void Set(const double x,const double y);
	/**
	 * @brief Get the value of the vector
	 *
	 * @param x Reference that will be modified to the xvalue
	 * @param y Reference that will be modified to the yvalue
	 * @return void
	 **/
	inline void Get(double &x,double &y) const;
	
	/**
	 * @brief Output Stream Operator for cout<< for example
	 *
	 * @param stream
	 * @param A physvector to output
	 * @return :ostream&
	 **/
	friend std::ostream & operator<< (std::ostream& stream, const physvector<2>& A );
	/**
	 * @brief Convert the physvector position to key with the good index given by h spacing.
	 *
	 * @param h
	 * @return Key<2> Key in wish container this position is.
	 **/
	inline Key<2> ToKey(double h);
	/**
	 * @brief Write position to output stream in a format compatible with paraview.
	 *
	 * @param out output stream.
	 **/
	inline void WritePos(fstream & out) const;
	inline void WritePosOneLine(fstream & out) const;
	/**
	 * @brief Return if we are a null vector.
	 *
	 * @return True if null vector.
	 **/
	inline bool IsNull() const;
	inline bool operator<(const physvector<2> A) const;
	inline bool operator==(const physvector<2> A) const;
	inline void To0();
	
	/**
	 * @name Distance
	 **/
	//@{
	
	/**
	 * @brief Get the euclidian distance \f$\sqrt{(x-x2)^2+(y-y2)^2}\f$
	 *
	 * @param A Other vector
	 * @return double Distance.
	 **/
	inline double Distance(const physvector<2>& A) const;
	/**
	 * @brief Get the square euclidian distance \f$(x-x2)^2+(y-y2)^2\f$
	 *
	 * @param A Other vector
	 * @return double Distance
	 **/
	inline double Distance2(const physvector<2>& A) const;
	/**
	 * @brief Get the max distance \f$ max(|x-x2|,|y-y2|) \f$
	 *
	 * @param A Other vector
	 * @return double Distance
	 **/
	inline double DistanceMax(const physvector<2>& A) const;
	/**
	 * @brief Calculate the euclidian norm \f$\sqrt{x^2+y^2}\f$
	 *
	 * @return double
	 **/
	inline double Norm() const;
	/**
	 * @brief Calculate the euclidian norm square \f$x^2+y^2\f$
	 *
	 * @return double
	 **/
	inline double Norm2() const;
	/**
	 * @brief Calculate the maximun norm \f$ max(x,y) \f$
	 *
	 * @return double
	 **/
	inline double NormMax() const;

	//@}
	/**
	 * @name Operator
	 **/
	 //@{
	inline physvector<2> operator+(const physvector<2>& A) const;
	inline double operator*(const physvector<2>& A) const;
	inline physvector<2> operator-(const physvector<2> &A) const;
	inline void operator=(const physvector<2> &A);
	inline void operator+=(const physvector<2> &A);
	inline void operator-=(const physvector<2> &A);
	inline void operator*=(const double c);
	inline physvector<2> operator/(const double c) const;
	friend inline physvector< 2> operator*(const double c,const physvector<2>& a);
	friend inline physvector< 2> operator*(const physvector<2> &a,const double c);
	/**
	 * @brief Component by component product.
	 *
	 * @param a Vector to with we make the product.
	 * @return Return the product component by component.
	 **/
	inline physvector<2> prod(const physvector<2>& a) const;
	//@}
	
	};



	#define VECTOR_FINISH //Used in const.h to assure that physvector is enterely defined.
#include "physvector.htt"


#endif // POSITION_H

