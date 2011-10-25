#ifndef VOISIN_ITERATOR_H
#define VOISIN_ITERATOR_H
#include "particles.h"
class Voisin_Iterator{
list<Particles*>::iterator m_particles;
Particles::iterator m_particle;
 list<Particles*> m_lpart;
public:
inline Voisin_Iterator(list<Particles*> & lparticles,list<Particles*>::iterator  particles,Particles::iterator  particle);
inline Voisin_Iterator operator++();
inline Voisin_Iterator operator++(int);
inline Particle operator*();
inline bool operator==(const Voisin_Iterator& B);
inline bool operator!=(const Voisin_Iterator& B);
};
#include "voisin_iterator.htt"
#endif //VOISIN_ITERATOR_H