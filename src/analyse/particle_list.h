#ifndef PARTICLE_LIST_H
#define PARTICLE_LIST_H
#include <deque>
#include "particle_real.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
using namespace std;
class Particle_List{
  deque<ParticleReal> m_list;
  double m_t;
public:
  Particle_List(double t);
inline  int Size() const;

      template<class Archive>
 inline  void read(Archive & ar) ;

};




#include "particle_list.htt"
#endif