#ifndef BOUNDARIES_H
#define BOUNDARIES_H
#include <vector>
#include "boundary.h"
#include "key.h"
using namespace std;

template<int n=DIM>
class Boundaries :public vector<Boundary<n> >
{
	Boundaries();
};


template<>
class Boundaries<2> :public vector<Boundary<2> >
{
	bool m_all;
public:
	inline Boundaries(const Key<2>& k1,const list<Key<2> >& key_list);
	inline Boundaries();
	
private:
inline Update();
inline bool HasBoundary();
};

template<>
class Boundaries<3> :public vector<Boundary<3> >
{
	bool m_all;
public:
	inline Boundaries(const Key<3> & k1,const list<Key<3> >& key_list);
	inline Boundaries();
private:
inline Update();
inline bool HasBoundary();
};
#include "boundaries.htt"
#endif // BOUNDARIES_H
