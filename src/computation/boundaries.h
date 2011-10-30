#ifndef BOUNDARIES_H
#define BOUNDARIES_H
#include <vector>
#include "boundary.h"
#include "key.h"
#include "physvector.h"
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
	inline bool HasBoundary() const;
inline void AddBoundary(const Key<2> &k1,const Key<2> &k2);
inline void RemoveBoundary(const Key<2> &k1,const Key<2> &k2);
inline void AddBoundaries(const Key<2> & k1,const list<Key<2> >& key_list);
inline void Dump()const;
inline void GetExteriorDirection(vector<physvector<2> >& v)const;
private:
inline void Update();

};

template<>
class Boundaries<3> :public vector<Boundary<3> >
{
	bool m_all;
public:
	inline Boundaries(const Key<3> & k1,const list<Key<3> >& key_list);
	inline Boundaries();
	inline bool HasBoundary() const;
inline void AddBoundary(const Key<3> &k1,const Key<3> &k2);
inline void RemoveBoundary(const Key<3> &k1,const Key<3> &k2);
inline void AddBoundaries(const Key<3> & k1,const list<Key<3> >& key_list);
inline void Dump()const;
inline void GetExteriorDirection(vector<physvector<3> > & v)const;
private:
inline void Update();
};
#include "boundaries.htt"
#endif // BOUNDARIES_H