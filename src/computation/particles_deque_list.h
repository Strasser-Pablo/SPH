#ifndef PARTICLES_DEQUE_LIST_H
#define PARTICLES_DEQUE_LIST_H
#include <deque>
#include <map>
#include "particles.h"
#include "key.h"

using namespace std;
class Particles_Deque_List{
	deque<Particles*> m_vect;
public:
	typedef deque<Particles*>::size_type size_type;
	typedef deque<Particles*>::const_reference const_reference;
	Particles_Deque_List();
	Particles* operator[](size_type index);
	const Particles* operator[](size_type index) const;
	deque<Particles*>::iterator begin();
	deque<Particles*>::const_iterator begin() const;
	deque<Particles*>::iterator end();
	deque<Particles*>::const_iterator end() const;
	Particles_Deque_List::size_type size () const;
	void Update(map<Key<DIM> ,Particles> & mymap);
	void push_back(const_reference part);
};
#endif