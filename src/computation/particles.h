/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#include "particle.h"
#include "voisin.h"
#ifndef PARTICLES_H
#define PARTICLES_H

#include <list>
#include "type.h"
#include "const.h"
#include <map>
#include "key.h"
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
    Voisin m_neighbour;
	Key<DIM> m_key;
public:
	void RemoveParticlesNeighbour(const Particles * part);
	void SetKey(Key<DIM> & k);
    Key<DIM> GetKey()const;
	void Calculate0Density();
	Boundaries<DIM> GetBoundary() const;
	void SetBoundary(Boundaries<DIM> & b);
	bool GetIsInBoundaryRegion()const;
    void InitializeCG();
    void CalculateBetaPart(double &num,bool & b,double alpha);
    void CalculateAlphaPart(double &num,double &denom);
    void CalculateP1(double beta);
	 bool FindBoundary(bool b) ;
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
	   void ComputeMove(double dt);
	    void preComputeMove_predictor(double dt);
	 void ComputeMove_predictor(double dt,bool &b);
	 void DoMove_predictor();
	  void WritePos(fstream& out) const;
	  void Density(fstream& out) const;
	  void Pressures(fstream& out) const;
	  void NB_it(fstream& out) const;
	  void Mass(fstream& out) const;
	  void MassDensity(fstream& out) const;
	 void NextForceTimeStep(double &dt) const;
	 void NextCourantVisciousTimeStep(double &dt) const;
    /**
     * @brief Set The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @param list of Neighbour
     * @return void
     **/
    void SetNeighbour(Voisin& list);

    Voisin GetNeighbour()const;
	 void GetNeighbour(Voisin *& vois);

    /**
     * @brief Update in wish container is the particle for every particle in container
     *
     * @param list map to all particles.
     * @return void
     **/
    void Update(  Particles_List*  list);

     bool operator==(const Particles& parts) const;

     void Dump(bool voisin=true);




 void Add(Particle part);

 inline void GetNeighbour(Voisin& neigh)const;
 
 void SetB_Speed();
void PreparePosition(bool &b);
};




  void Particles::GetNeighbour( Voisin &  neigh)const{
  neigh=m_neighbour;
  }

#endif // PARTICLES_H
