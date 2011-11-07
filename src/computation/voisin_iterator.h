#ifndef VOISIN_ITERATOR_H
#define VOISIN_ITERATOR_H
#include "particles.h"
/**
 * @brief Class Voisin_Iterator. Iterator that can be incremented.
 * To iterate throught the particle.
 **/
class Voisin_Iterator{
list<Particles*>::iterator m_particles;
Particles::iterator m_particle;
 list<Particles*>& m_lpart;
public:
/**
 * @brief Construct a Voisin_Iterator from the list of particles and the iterator of particles and particle.
 * 
 * @param lparticles List of particles. To which we need a iterator.
 * @param particles Iterator to wich particles whe are.
 * @param particle Iterator to a particle in a given particles.
 **/
inline Voisin_Iterator(list<Particles*> & lparticles,list<Particles*>::iterator  particles,Particles::iterator  particle);
/**
 * @brief Construct a Voisin_Iterator from the list of particles. No iterator to particle are given. It cannot be dereferenced.
 * 
 * @param lparticles List of particles. To which we need a iterator.
 * @param particles Iterator to wich particles whe are.
 **/
inline Voisin_Iterator(list<Particles*> & lparticles,list<Particles*>::iterator  particles);

inline Voisin_Iterator operator++();
inline Voisin_Iterator operator++(int);
inline Particle operator*();
inline bool operator==(const Voisin_Iterator& B)const;
inline bool operator!=(const Voisin_Iterator& B)const;
friend class Voisin_Const_Iterator;
};

/**
 * @brief Class  Voisin_Const_Iterator. Iterator that can be incremented.
 * To iterate throught the particle. The particle are constant, they cannot be changed.
 **/
class Voisin_Const_Iterator{
list<Particles*>::const_iterator m_particles;
Particles::const_iterator m_particle;
 list<Particles*>& m_lpart;
public:
/**
 * @brief Construct a Voisin_Iterator from the list of particles and the iterator of particles and particle.
 * 
 * @param lparticles List of particles. To which we need a iterator.
 * @param particles Iterator to wich particles whe are.
 * @param particle Iterator to a particle in a given particles.
 **/
inline Voisin_Const_Iterator(list<Particles*> & lparticles,list<Particles*>::const_iterator  particles,Particles::const_iterator  particle);
/**
 * @brief Construct a Voisin_Iterator from the list of particles. No iterator to particle are given. It cannot be dereferenced.
 * 
 * @param lparticles List of particles. To which we need a iterator.
 * @param particles Iterator to wich particles whe are.
 **/
inline Voisin_Const_Iterator(list<Particles*> & lparticles,list<Particles*>::const_iterator  particles);
/**
 * Casting constructor from a Voisin_Iterator to a Constant iterator.
 **/
inline Voisin_Const_Iterator(Voisin_Iterator A);
inline Voisin_Const_Iterator operator++();
inline Voisin_Const_Iterator operator++(int);
inline const Particle operator*();
inline bool operator==(const Voisin_Const_Iterator& B)const;
inline bool operator!=(const Voisin_Const_Iterator& B)const;
};
#include "voisin_iterator.htt"
#endif //VOISIN_ITERATOR_H