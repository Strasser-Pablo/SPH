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
	/**
	 * @brief Type of particle in container. Unused for the moment. 
	 **/
    ParticleType m_type;
	/**
	 * @brief Deprecated.
	 **/ 
	Boundaries<DIM> m_boundary;
	/**
	 * @brief Neighbour of the particles. Used to loop with the neighbouring particle.
	 **/
    Voisin m_neighbour;
	/**
	 * @brief Key in witch is stored the particle.
	 **/
	Key<DIM> m_key;
public:
/**
 * @brief Remove information of Neighbour about this particles. Used when deleting neighbour.
 **/
	void RemoveParticlesNeighbour(const Particles * part);
	/**
 * @brief Set the actual Key.
 **/
	void SetKey(Key<DIM> & k);
	/**
 * @brief Get the actual Key.
 **/
    Key<DIM> GetKey()const;
	/**
 * @brief Modify the mass to have a correct 0 density.
 *  Calculus will only happen once per particle.
 **/
	void Calculate0Density();
	/**
	 * @brief deprecated.
	 **/
	Boundaries<DIM> GetBoundary() const;
	/**
	 * @brief deprecated.
	 **/
	void SetBoundary(Boundaries<DIM> & b);
	/**
	 * @brief deprecated
	 **/
	bool GetIsInBoundaryRegion()const;
	/**
	 * @brief Initialize conjugate gradient for the used in the incompressible algorithm.
	 **/
    void InitializeCG();
	/**
	 * @brief Partial calculate of Beta. For conjugate Gradient.
	 * 
	 * @param num Numerator calculated for Beta.
	 * @param b True when converged.
	 * @param alpha Value of alpha to use for calculation.
	 **/
    void CalculateBetaPart(double &num,bool & b,double alpha);
	/**
	 * @brief Partial calculate of alpha. For conjugate Gradient.
	 * 
	 * @param num partial calculation of numerator.
	 * @param denom partial calculate of denominator.
	 **/
    void CalculateAlphaPart(double &num,double &denom);
	/**
	 * @brief Calculated last step of conjugate gradient.
	 * @param beta Calculated value of beta.
	 **/
    void CalculateP1(double beta);
	/**
	 * @deprecated
	 **/
	 bool FindBoundary(bool b) ;
    /**
     * @brief Construct a list of Particle of type type
     *
     * @param type Type of particle of the list
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
    * @brief Constructor with a predefined key.
    *
	* @param k Key of the particles.
    **/
	Particles(Key<DIM> &k);
    /**
     * @brief Compute the pressure and density for all Particle in this container
     *
     * @return void
     **/
    void ComputeDensity();




    /**
     * @brief Make the initial move for the incompressible algorithm.
     *
     * @param dt Time step
     * @return void
     **/
    bool PreComputeMove(double dt);
	 /**
     * @brief Make Move all the particle in the  container.
     *
     * @param dt Time step
     * @return void
     **/
	   void ComputeMove(double dt);
	    /**
     * @brief Make the initial move for the predictor corrector.
     *
     * @param dt Time step
     * @return void
     **/
	    void preComputeMove_predictor(double dt);
		 /**
     * @brief Correction step for the predictor corrector.
     *
     * @param dt Time step
	 * @param b True when not converged.
     * @return void
     **/
	 void ComputeMove_predictor(double dt,bool &b);
	  /**
     * @brief Final step for the predictor corrector.
     *
     * @return void
     **/
	 void DoMove_predictor();
	 /**
	  * @brief Write the position in a format for ParaView.
	  * 
	  *  @param out Output stream to write.
	  **/
	  void WritePos(fstream& out) const;
	  	 /**
	  * @brief Write the density in a format for ParaView.
	  * 
	  *  @param out Output stream to write.
	  **/
	  void Density(fstream& out) const;
	  	 /**
	  * @brief Write the Pressures in a format for ParaView.
	  * 
	  *  @param out Output stream to write.
	  **/
	  void Pressures(fstream& out) const;
	  /**
	  * @brief Write the Nb_it in a format for ParaView.
	  * 
	  *  @param out Output stream to write.
	  **/
	  void NB_it(fstream& out) const;
	  /**
	  * @brief Write the Mass in a format for ParaView.
	  * 
	  *  @param out Output stream to write.
	  **/
	  void Mass(fstream& out) const;
	   /**
	  * @brief Write the MassDensity in a format for ParaView.
	  * 
	  *  @param out Output stream to write.
	  **/
	  void MassDensity(fstream& out) const;
	    /**
		 * Calculate the timestep restriction that depend on the force.
	  **/
	 void NextForceTimeStep(double &dt) const;
	     /**
		 * Calculate the timestep restriction that depend on the current and viscosity.
	  **/
	 void NextCourantVisciousTimeStep(double &dt) const;
    /**
     * @brief Set The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @param list Voisin that contain all neighbour particles.
     * @return void
     **/
    void SetNeighbour(Voisin& list);
	 /**
     * @brief Get The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @return  Voisin that contain all neighbour particles.
     **/
    Voisin GetNeighbour()const;
	 /**
     * @brief Get The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @param  Voisin that contain all neighbour particles.
     **/
	 void GetNeighbour(Voisin *& vois);

    /**
     * @brief Update in wish container is the particle for every particle in container
     *
     * @param list map to all particles.
     * @return void
     **/
    void Update(  Particles_List*  list);
     /**
	  * @brief Comparation operator.
	  **/
     bool operator==(const Particles& parts) const;
/**
 * Used for Debuging, print information on screen.
 **/
     void Dump(bool voisin=true);

/**
 * @brief Add particle in the container.
 **/
 void Add(Particle part);
 /**
     * @brief Get The Neighbour of the container.
     *
     * Neighbour of the container are defined as particle container that are in a radius of h from the container
     * it need to contain itself.
     * @param  neigh that contain all neighbour particles.
     **/
 inline void GetNeighbour(Voisin& neigh)const;
 
 /**
     * @brief Used on the incompressible algorithm To calculate the second member for the speed step.
	 * And to make a position correction.
     **/
 void SetB_Speed();
  /**
     * @brief Used on the incompressible algorithm To calculate the second member for the position step.
	 * And to make a speed correction.
	 * 
	 * @param b True if not converged.
     **/
void PreparePosition(bool &b);
/**
 * @brief Calculate minus the Sub Grid Tensor.
 **/
void CalculateSubGridTens();


void WriteSpeed(fstream & out) const;
void WriteErf(fstream &out,double t) const;
void WriteForce(fstream &out) const;
void WriteForceGravity(fstream &out) const;
void WriteForcePressure(fstream &out) const;
void WriteForceViscosity(fstream &out) const;
void WriteForceTurbulence(fstream &out) const;
void UpdateForce() const;
};




  void Particles::GetNeighbour( Voisin &  neigh)const{
  neigh=m_neighbour;
  }

#endif // PARTICLES_H
