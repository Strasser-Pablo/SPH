#ifndef WORLD_H
#define WORLD_H
#include "particles_list.h"
#include <deque>
using namespace std;


class World{
protected:
  deque<ParticleReal> m_particle_real_list;
  Particles_List m_list;
public:
  /**
   * @brief Create a World object
   *
   **/
  World();
  /**
   * @brief Add a real particle in the world. The particle will be copied it can be deleted after.
   *
   * @param part Real Particle to add. 
   * @return void
   **/
 // inline  void  Add(ParticleReal & part);
    inline  void  Add(ParticleReal  part);
   ~World();
};

#include "world.htt"

#endif