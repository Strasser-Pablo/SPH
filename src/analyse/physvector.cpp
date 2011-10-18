#include "physvector.h"

std::ostream &operator<< (std::ostream& stream, const physvector<2>& A ) {
	stream<<"( "<<A.m_x<<", "<<A.m_y<<" )";
	return stream;
}

std::ostream &operator<< (std::ostream& stream, const physvector<3>& A ) {
	stream<<"( "<<A.m_x<<", "<<A.m_y<<", " <<A.m_z<<" )";
	return stream;
}
