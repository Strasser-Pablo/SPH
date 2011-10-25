
#ifndef VOISIN_ITERATOR
#define VOISIN_ITERATOR
#include <list>
class particles;

using namespace std;
class Particles;
class Voisin_Iterator;
class Voisin{
	list<Particles*> m_vect;
public:
typedef Voisin_Iterator iterator;
typedef list<Particles*>::iterator iterator_particles;

inline	Voisin(list<Particles*> vect);
inline	Voisin();
inline list<Particles*> GetParticlesVect()const;
inline Voisin_Iterator begin();
inline Voisin_Iterator end();
inline iterator_particles begin_particles();
inline iterator_particles end_particles();
inline void erase(iterator_particles& it);
};
#include "voisin.htt"
#endif //VOISIN_H