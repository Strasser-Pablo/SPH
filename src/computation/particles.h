/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/
#include "particle.h"

#ifndef PARTICLES_H
#define PARTICLES_H
#include <list>
#include "type.h"
#include "const.h"
#include <map>
#include "key.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "boundaries.h"


class Particle;
class Particles_List;
using namespace std;
/**
* @brief Represent a list of Particle, inherit from std::list.
*
**/

class Particles: public std::list<Particle>
{
    ParticleType m_type;
	Boundaries<DIM> m_boundary;
    list<Particles*> m_neighbour;
	Key<DIM> m_key;
public:
	void RemoveParticlesNeighbour(const Particles * part);
	void SetKey(Key<DIM> & k);
    Key<DIM> GetKey()const;
	void Calculate0Density();
	Boundaries<DIM> GetBoundary() const;
	void SetBoundary(Boundaries<DIM> & b);
    void InitializeCG();
    void CalculateBetaPart(double &num,bool & b,double alpha);
    void CalculateAlphaPart(double &num,double &denom);
    void CalculateP1(double beta);
    /**
     * @brief Construct a list of Particle of type type
     *
     * @param type Type of particle of the list
#include <boost/archive/xml_iarchive.hpp>
     **/
    Particles(ParticleType type);
    /**
    * @brief Copy Constructor
    *
    * @param A Particles to copy
    **/
    Particles(const Particles &A);
    /**
    * @brief Default constructor, Doesn't specify type.
    *
    **/
    Particles();
	Particles(Key<DIM> &k);
    /**
     * @brief Compute the pressure and density for all Particle in this container
     *
     * @return void
     **/
    void ComputeDensity();




    /**
     * @brief Make Move all the particle in the  container.
     *
     * @param dt Time step
     * @return void
     **/
    bool PreComputeMove(double dt);
    /**
     * @brief Set The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @param list of Neighbour
     * @return void
     **/
    void SetNeighbour(list<Particles*> list);

    list<Particles*> GetNeighbour()const;

    /**
     * @brief Update in wish container is the particle for every particle in container
     *
     * @param list map to all particles.
     * @return void
     **/
    void Update(  Particles_List*  list);

     bool operator==(const Particles& parts) const;

     void Dump(bool voisin=true);


      template<class Archive>
 inline  void write(Archive & ar) const;

 void Add(Particle part);

 inline void GetNeighbour(list<Particles *> & neigh)const;
 
 void SetB_Speed();
void PreparePosition(bool &b);
};


  template<class Archive>
void Particles::write(Archive& ar) const
{
  const bool bt=true;
  const bool bf=false;
for(Particles::const_iterator it=begin();it!=end();it++){
  ar<<boost::serialization::make_nvp("true",bt);
 ar<<boost::serialization::make_nvp("Particle_real",**it);

 #ifdef DOXYGEN
  ParticleReal p;
 p.serialize(ar,0);
 #endif //DOXYGEN
}
}

  void Particles::GetNeighbour( list<Particles *> &  neigh)const{
  neigh=m_neighbour;
  }

#endif // PARTICLES_H
