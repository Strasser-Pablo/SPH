#ifndef BOUNDARY_H
#define BOUNDARY_H
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
};

template<>
class Boundary<3>{
	int m_x;
	int m_y;
	int m_z;
public:
inline	Boundary(int x,int y,int z);
};

#include "boundary.htt"
#endif