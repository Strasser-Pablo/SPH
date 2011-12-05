#ifndef PARTICLES_DEQUE_LIST_H
	#define PARTICLES_DEQUE_LIST_H
#include <deque>
#include <map>
#include "particles.h"
#include "key.h"

	using namespace std;
	/**
	 * @brief Decque of particles used in the parallel case to have direct random acess.
	 **/
	class Particles_Deque_List {
	deque<Particles*> m_vect;
public:
	Particles_Deque_List();
/**
 * @name General Container Manipulation
 **/
 //@{
	typedef deque<Particles*>::size_type size_type;
	typedef deque<Particles*>::const_reference const_reference;
	
	Particles* operator[](size_type index);
	const Particles* operator[](size_type index) const;
	deque<Particles*>::iterator begin();
	deque<Particles*>::const_iterator begin() const;
	deque<Particles*>::iterator end();
	deque<Particles*>::const_iterator end() const;
	Particles_Deque_List::size_type size () const;
	void push_back(const_reference part);
	//@}
	/**
	* @name Specialized Manipulation
	**/
	//@{
	/**
	 * @brief Will delete correctly Particles in list maqued for deletion.
	 * 
	 * @param mymap Map of particles that will be updated (the removed particles will be removed from map)
	 * 
	 * @invariant After call all particles in map and in container will be the same.
	 **/
	void Update(map<Key<DIM>,Particles> & mymap);
	//@}
	};
#endif