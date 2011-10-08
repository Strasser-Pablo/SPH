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
    list<Particles*> m_neighbour;
public:
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
    
    /**
     * @brief Compute the pressure and density for all Particle in this container
     *
     * @return void
     **/
    void ComputePressure_Density();
    /**
     * @brief Compute Internals force for all particle in this container.
     *
     * @return void
     **/
    void ComputeInternal_Force();
    /**
     * @brief Compute gravity Force for all particle in this container.
     *
     * @return void
     **/
    void ComputeGravity_Force();
    
    /**
     * @brief Make Move all the particle in the  container.
     *
     * @param dt Time step
     * @return void
     **/
    void ComputeMove(double dt);
    /**
     * @brief Set The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @param list of Neighbour
     * @return void
     **/
    void SetNeighbour(list<Particles*> list);
    
    list<Particles*> GetNeighbour();
    
    /**
     * @brief Update in wish container is the particle for every particle in container
     *
     * @param list map to all particles.
     * @return void
     **/
    void Update(  Particles_List*  list);
    
     bool operator==(const Particles parts) const;
     
     void Dump(bool voisin=true);
     

      template<class Archive>
 inline  void write(Archive & ar) const;
};


  template<class Archive>
void Particles::write(Archive& ar) const
{
  const bool bt=true;
  const bool bf=false;
for(Particles::const_iterator it=begin();it!=end();it++){
  ar<<boost::serialization::make_nvp("true",bt);
 ar<<boost::serialization::make_nvp("Particle_real",**it); 
 
}
}

#endif // PARTICLES_H
