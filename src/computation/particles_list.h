#ifndef PARTICLES_LIST_H
#define PARTICLES_LIST_H
#include <map>
#include "particles.h"
#include "particle.h"

#include "key.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
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
void Calculate0Density();
 void InitializeCG();
double CalculateAlpha(double &num,bool &b);
double CalculateBeta(double &denom,bool &b,double alpha);
void CalculateP1(double bet);
void ConjugateGradiant();
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

  void Prepare();
  /**
   * @brief Uttility function, update neighbour of key k and it's neighbour
   *
   * @param k where to update
   * @return void
   **/
  inline  void AddNeighbour(Key<DIM> k);
  inline void Update(list<Particle>::iterator & it,Particles * part);
  void Dump();
  inline void RemoveParticles(const Particles & Parts);


      template<class Archive>
   inline  void write(Archive & ar) const;
   private:
 void  CorrectDensity();
 void SetB_Speed();
 void PreparePosition(bool &b);

};




#include "particles_list.htt"

#endif // PARTICLES_LIST_H
