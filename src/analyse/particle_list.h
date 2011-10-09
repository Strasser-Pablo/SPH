#ifndef PARTICLE_LIST_H
#define PARTICLE_LIST_H
#include <deque>
#include "particle_real.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>


#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
class Particle_List{
  deque<ParticleReal> m_list;

public:
  Particle_List();
inline  int Size() const;

      template<class Archive>
 inline  void read(Archive & ar) ;
void Draw(GLUquadric* param);
};




#include "particle_list.htt"
#endif