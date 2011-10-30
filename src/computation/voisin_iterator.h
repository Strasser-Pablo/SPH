#ifndef VOISIN_ITERATOR_H
#define VOISIN_ITERATOR_H
#include "particles.h"

class Voisin_Iterator{
list<Particles*>::iterator m_particles;
Particles::iterator m_particle;
 list<Particles*>& m_lpart;
public:
inline Voisin_Iterator(list<Particles*> & lparticles,list<Particles*>::iterator  particles,Particles::iterator  particle);
inline Voisin_Iterator(list<Particles*> & lparticles,list<Particles*>::iterator  particles);

inline Voisin_Iterator operator++();
inline Voisin_Iterator operator++(int);
inline Particle operator*();
inline bool operator==(const Voisin_Iterator& B)const;
inline bool operator!=(const Voisin_Iterator& B)const;
friend class Voisin_Const_Iterator;
};

class Voisin_Const_Iterator{
list<Particles*>::const_iterator m_particles;
Particles::const_iterator m_particle;
 list<Particles*>& m_lpart;
public:
inline Voisin_Const_Iterator(list<Particles*> & lparticles,list<Particles*>::const_iterator  particles,Particles::const_iterator  particle);
inline Voisin_Const_Iterator(list<Particles*> & lparticles,list<Particles*>::const_iterator  particles);
inline Voisin_Const_Iterator(Voisin_Iterator A);
inline Voisin_Const_Iterator operator++();
inline Voisin_Const_Iterator operator++(int);
inline const Particle operator*();
inline bool operator==(const Voisin_Const_Iterator& B)const;
inline bool operator!=(const Voisin_Const_Iterator& B)const;
};
#include "voisin_iterator.htt"
#endif //VOISIN_ITERATOR_H