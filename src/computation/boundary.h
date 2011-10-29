#ifndef BOUNDARY_H
#define BOUNDARY_H
#include <iostream>
	#include "const.h"
using namespace std;
template<int n=DIM>
class Boundary{
  Boundary(){};
};

template<>
class Boundary<2>{
	int m_x;
	int m_y;
public:
inline	Boundary(int x,int y);
inline bool operator==(const Boundary &B) const;
inline void Dump()const;
inline int GetMirorID() const;
inline void Get( int &x,int &y)const;
};

template<>
class Boundary<3>{
	int m_x;
	int m_y;
	int m_z;
public:
inline	Boundary(int x,int y,int z);
inline bool operator==(const Boundary &B) const;
inline void Dump()const;
inline int GetMirorID() const;
inline void Get( int &x,int &y,int &z)const;
};

#include "boundary.htt"
#endif