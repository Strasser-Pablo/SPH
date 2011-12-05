/** @file
 * @brief Contain Debug uttility.
 *
 **/

#ifndef DEBUG_H

	/**
	 * @brief Header guard for debug.h
	 **/
	#define DEBUG_H
#include <list>
#include <iostream>

#include "particles.h"

	using namespace std;

	/**
	 * @brief Dump all particles in list. Used to dump Neighbour
	 *
	 * @param a list of neighbour
	 *
	 * @return void
	 * 
	 * @deprecated Will possibly be removed, or changed to use Voisin.
	 **/
	void inline DumpNeighbour(list<Particles *> & a)
	{
		for(list<Particles *>::iterator it=a.begin(); it!=a.end(); ++it)
		{
			(*it)->Dump(false);
		}
	}

	/**
	 * @brief Dump a list of key
	 *
	 * @param a list of key to dump.
	 * @return void
	 **/
	void inline GDump(list<Key<DIM> > & a)
	{
		for(list<Key<DIM> >::iterator it=a.begin(); it!=a.end(); ++it)
		{
			it->Dump();
		}
	}


#endif //DEBUG_H
