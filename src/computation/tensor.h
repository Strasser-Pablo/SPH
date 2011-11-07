#ifndef TENSOR_H
#define TENSOR_H
#include "physvector.h"
template<int N=3>
class Tensor {
    inline Tensor();
};
/**
 * @brief 2d Tensor class of rank 2. Stock as 2 vector.
 * 
 * Provide addition, and tensor vector multiplication for symetric tensor.
 **/
template<>
class Tensor<2> {
physvector<2> m_x;
physvector<2> m_y;

public:
/**
 * @brief Tensor constructor from two vector.
 * 
 * @param x X vector.
 * @param y Y vector.
 * 
 * \f[  T_{ij}=V^{i}_{j} \f]
 * where \f$ V^{1}=x \f$ and \f$ V^{2}=y \f$
 **/
inline Tensor(physvector<2> x,physvector<2> y);
/**
 * @brief Default constructor.
 **/
inline Tensor();

inline Tensor<2> operator+(const Tensor<2>& B)const;
inline void operator+=(const Tensor<2>& B) ;
inline Tensor<2> operator-(const Tensor<2>& B)const;
inline void operator*=(const double c);
inline void operator-=(const Tensor<2>& B);
/**
 * @brief Make tensor symetric.
 * 
 *\f[ T^{new}_{ij}=\frac{1}{2}\left(T_{ij}+T_{ji}\right) \f]
 **/
inline void MakeSymetric();
/**
 * @brief Calculate the norm of the tensor.
 * 
 * \f[ \sqrt{\sum_{i,j} {T_{ij}}^2 } \f]
 **/
inline double Norm()const ;
friend inline Tensor< 2> operator*(const double c,const Tensor<2>& B) ;
friend inline Tensor< 2> operator*(const Tensor<2> &B,const double c) ;
/**
 * @brief Calculate the product tensor vector. For Symetric vector,
 * doesn't depend on order.
 * 
 * \f[ T\cdot V=\sum_{j}T_{ij}V_{j} \f]
 **/
friend inline physvector< 2> operator*(const physvector< 2>& A,const Tensor<2>& B) ;
friend inline physvector< 2> operator*(const Tensor<2>& B,const physvector< 2>& A) ;

};

/**
 * @brief 3d Tensor class of rank 2. Stock as 3 vector.
 * 
 * Provide addition, and tensor vector multiplication for symetric tensor.
 **/
template<>
class Tensor<3> {
physvector<3> m_x;
physvector<3> m_y;
physvector<3> m_z;
public:
/**
 * @brief Tensor constructor from two vector.
 * 
 * @param x X vector.
 * @param y Y vector.
 * @param z Z vector.
 * 
 * \f[  T_{ij}=V^{i}_{j} \f]
 * where \f$ V^{1}=x \f$ and \f$ V^{2}=y \f$ and \f$ V^{3}=z \f$
 **/
inline Tensor(physvector<3> x,physvector<3> y,physvector<3> z);
/**
 * @brief Default constructor.
 **/
inline Tensor();
inline Tensor<3> operator+(const Tensor<3>& B)const;
inline void operator+=(const Tensor<3>& B);
inline Tensor<3> operator-(const Tensor<3>& B)const;
inline void operator-=(const Tensor<3>& B);
inline void operator*=(const double c);
/**
 * @brief Make tensor symetric.
 * 
 *\f[ T^{new}_{ij}=\frac{1}{2}\left(T_{ij}+T_{ji}\right) \f]
 **/
inline void MakeSymetric();
/**
 * @brief Calculate the norm of the tensor.
 * 
 * \f[ \sqrt{\sum_{i,j} {T_{ij}}^2 } \f]
 **/
inline double Norm()const ;
friend inline Tensor< 3> operator*(const double c,const Tensor<3>& B) ;
friend inline Tensor< 3> operator*(const Tensor<3> &B,const double c) ;
/**
 * @brief Calculate the product tensor vector. For Symetric vector,
 * doesn't depend on order.
 * 
 * \f[ T\cdot V=\sum_{j}T_{ij}V_{j} \f]
 **/
friend inline physvector< 3> operator*(const physvector< 3>& A,const Tensor<3>& B) ;
friend inline physvector< 3> operator*(const Tensor<3>& B,const physvector< 3>& A) ;

};

#include "tensor.htt"
#endif