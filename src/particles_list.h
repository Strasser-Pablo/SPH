#ifndef PARTICLES_LIST_H
#define PARTICLES_LIST_H
#include <map>
#include "particles.h"
#include "key.h"
using namespace std;

  /**
   * @brief Contain all the particles object in a map. Creating the geometric relation between particles.
   *
   **/
class Particles_List{
  
  map<Key<DIM> ,Particles> m_list;
  double m_t;
protected:
public:
  /**
   * @brief Create a empty list of particles
   *
   **/
  Particles_List();
  
  /**
   * @brief Add the particle in the list. Adding it in the good particles. And creating the link.
   *
   * @param part ...
   * @return void
   **/
  inline  void Add(Particle  part);
  
  /**
   * @brief Compute a complete step
   *
   * @return void
   **/
  void Compute();
  
  /**
   * @brief Uttility function, update neighbour of key k and it's neighbour
   *
   * @param k where to update
   * @return void
   **/
  inline  void AddNeighbour(Key<DIM> k);
  
  void Dump();
};




#include "particles_list.htt"

#endif // PARTICLES_LIST_H