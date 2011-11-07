
#ifndef VOISIN_ITERATOR
#define VOISIN_ITERATOR
#include <list>
class particles;

using namespace std;
class Particles;
class Voisin_Iterator;
class Voisin_Const_Iterator;
/**
 * @brief Voisin class. Allow to iterate throught all particle in a list of particles.
 * 
 * Iterator are provided to list particles or particle. In a list of particles.
 **/
class Voisin{
	list<Particles*> m_vect;
public:
typedef Voisin_Iterator iterator;
typedef  Voisin_Const_Iterator const_iterator;
typedef list<Particles*>::iterator iterator_particles;
/**
 * @brief Constructor from a list of particles.
 **/
inline	Voisin(list<Particles*> vect);
/**
 * @brief Default constructor.
 **/
inline	Voisin();
/**
 * @brief return the list of particles.
 * 
 * @return List of particles.
 **/
inline list<Particles*> GetParticlesVect()const;
/**
 * @brief Return a iterator to the begining of the list.
 **/
inline Voisin_Iterator begin();
/**
 * @brief Return a iterator to the ending of the list.
 **/
inline Voisin_Iterator end();
/**
 * @brief Return a const iterator to the begining of the list.
 **/
inline Voisin_Const_Iterator begin()const;
/**
 * @brief Return a const iterator to the ending of the list.
 **/
inline Voisin_Const_Iterator end()const;
/**
 * @brief Return a iterator to the begin of particles.
 **/
inline iterator_particles begin_particles();
/**
 * @brief Return a iterator to the end of particles.
 **/
inline iterator_particles end_particles();
/**
 * @brief Erase a part of the particles list given by the iterator it.
 * Iterator it is invalided.
 * 
 * @param it Is the iterator to erase.
 **/
inline void erase(iterator_particles& it);
};
#include "voisin.htt"
#endif //VOISIN_H