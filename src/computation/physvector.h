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
    inline    double Distance2(physvector<N> A);
};


 /**
   * @brief Specialized class for 3d vector
   *
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
    inline  double Distance2(const physvector<3>& A) const;
          /**
     * @brief Calculate the euclidian norm \f$\sqrt{x^2+y^2+z^2}\f$
     *
     * @return double
     **/
    inline double Norm()const;
          /**
     * @brief Calculate the euclidian norm square \f$x^2+y^2+z^2\f$
     *
     * @return double
     **/
    inline double Norm2()const;
    /**
     * @brief Set the value of the vector
     *
     * @param x xvalue
     * @param y yvalue
     * @param z zvalue
     * @return void
     **/
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
    inline  physvector<3> operator+(const physvector<3>& A) const;
     inline  double operator*(const physvector<3>& A) const;
    inline physvector<3> operator-(const physvector<3>& A) const;
        inline physvector<3> operator-() const;
    inline void operator=( const physvector<3> &A);
    inline void operator+=(const physvector<3> &A);
    inline void operator-=(const physvector<3> &A);
     inline  void operator*=(const double c);
         inline physvector<3> operator/(const double c) const;
        /**
     * @brief Output Stream Operator for cout<< for example
     *
     * @param stream
     * @param A physvector to output
     * @return :ostream&
     **/
    friend std::ostream& operator<< (std::ostream& stream, const physvector<3>& A );
    friend inline physvector< 3> operator*(const double c,const physvector<3>& a);
     friend inline physvector< 3> operator*(const physvector<3>& a,const double c);
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
		inline bool IsNull()const;
			/**
		 * @brief Write position to stream. In a format compatible with paraview.
		 * 
		 * @param out Stream to output.
		 **/
		inline void WritePos(fstream & out) const;
			/**
		 * @brief Component by component product.
		 * 
		 * @param out Stream to output.
		 **/
		inline physvector<3> prod(const physvector<3>& a) const;
		inline bool operator<(const physvector<3> A)const;
		inline bool operator==(const physvector<3> A)const;
     #ifndef DOXYGEN
private:
       #endif //DOXYGEN

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
    inline  physvector(const double x,const double y);
    /**
     * @brief Get the euclidian distance \f$\sqrt{(x-x2)^2+(y-y2)^2}\f$
     *
     * @param A Other vector
     * @return double Distance.
     **/
    inline  double Distance(const physvector<2>& A) const;
    /**
     * @brief Get the square euclidian distance \f$(x-x2)^2+(y-y2)^2\f$
     *
     * @param A Other vector
     * @return double Distance
     **/
    inline  double Distance2(const physvector<2>& A) const;

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
    inline physvector<2> operator+(const physvector<2>& A)const;
	 inline  double operator*(const physvector<2>& A) const;
    inline physvector<2> operator-(const physvector<2> &A) const;
    inline  void operator=(const physvector<2> &A);
    inline void operator+=(const physvector<2> &A)  ;
    inline  void operator-=(const physvector<2> &A);
    inline  void operator*=(const double c);
    inline physvector<2> operator/(const double c) const;
    /**
     * @brief Output Stream Operator for cout<< for example
     *
     * @param stream
     * @param A physvector to output
     * @return :ostream&
     **/
    friend std::ostream & operator<< (std::ostream& stream, const physvector<2>& A );
    friend inline physvector< 2> operator*(const double c,const physvector<2>& a) ;
    friend inline physvector< 2> operator*(const physvector<2> &a,const double c) ;
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
		/**
		 * @brief Component by component product.
		 * 
		 * @param a Vector to with we make the product.
		 * @return Return the product component by component.
		 **/
	inline	physvector<2> prod(const physvector<2>& a) const;
	/**
	 * @brief Return if we are a null vector.
	 * 
	 * @return True if null vector.
	 **/
	inline bool IsNull()const;
		inline bool operator<(const physvector<2> A)const;
		inline bool operator==(const physvector<2> A)const;
};



#define VECTOR_FINISH  //Used in const.h to assure that physvector is enterely defined.
#include "physvector.htt"


#endif // POSITION_H

