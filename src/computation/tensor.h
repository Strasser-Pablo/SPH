#ifndef TENSOR_H
#define TENSOR_H
#include "physvector.h"
template<int N=3>
class Tensor {
    inline Tensor();
};

template<>
class Tensor<2> {
physvector<2> m_x;
physvector<2> m_y;

public:
inline Tensor(physvector<2> x,physvector<2> y);
inline Tensor();

inline Tensor<2> operator+(const Tensor<2>& B)const;
inline void operator+=(const Tensor<2>& B) ;
inline Tensor<2> operator-(const Tensor<2>& B)const;
inline void operator*=(const double c);
inline void operator-=(const Tensor<2>& B);
inline void MakeSymetric();
inline double Norm()const ;
friend inline Tensor< 2> operator*(const double c,const Tensor<2>& B) ;
friend inline Tensor< 2> operator*(const Tensor<2> &B,const double c) ;
friend inline physvector< 2> operator*(const physvector< 2>& A,const Tensor<2>& B) ;
friend inline physvector< 2> operator*(const Tensor<2>& B,const physvector< 2>& A) ;

};

template<>
class Tensor<3> {
physvector<3> m_x;
physvector<3> m_y;
physvector<3> m_z;
public:
inline Tensor(physvector<3> x,physvector<3> y,physvector<3> z);
inline Tensor();
inline Tensor<3> operator+(const Tensor<3>& B)const;
inline void operator+=(const Tensor<3>& B);
inline Tensor<3> operator-(const Tensor<3>& B)const;
inline void operator-=(const Tensor<3>& B);
inline void operator*=(const double c);
inline void MakeSymetric();
inline double Norm()const ;
friend inline Tensor< 3> operator*(const double c,const Tensor<3>& B) ;
friend inline Tensor< 3> operator*(const Tensor<3> &B,const double c) ;
friend inline physvector< 3> operator*(const physvector< 3>& A,const Tensor<3>& B) ;
friend inline physvector< 3> operator*(const Tensor<3>& B,const physvector< 3>& A) ;

};

#include "tensor.htt"
#endif