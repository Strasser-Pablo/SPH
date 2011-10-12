/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#ifndef PARTICLE_REAL_H
#define PARTICLE_REAL_H
#include "type.h"
#include "physvector.h"
#include "const.h"
#include <list>
#include "particle.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
using namespace std;
class Particles;
    /**
   * @brief Represent a individual Particle
   **/
class ParticleReal
{
    physvector<DIM> m_pos;
    physvector<DIM> m_speed;
      physvector<DIM> m_a;
    double m_m;
    double m_density;
    double m_p;
    physvector<DIM> m_surface_tens;
    ParticleType m_type;
public:
      /**
   * @brief Default Constructor
   **/
    inline ParticleReal();
    /**
     * @brief Create a individual Particle with givent property with initial speed 0.
     *
     * @param pos Particle position
     * @param type Particle type
     * @param m Particle mass
     * @param rho Particle density
     * @param p Particle pressure
     **/
    inline ParticleReal(physvector<DIM> pos,ParticleType type,double m);
    
        /**
     * @brief Create a individual Particle with givent property
     *
     * @param pos Particle position
     * @param speed Particle speed
     * @param type Particle type
     * @param m Particle mass
     * @param rho Particle density
     * @param p Particle pressure
     **/
      inline ParticleReal(physvector<DIM> pos,physvector<DIM> speed,ParticleType type,double m);
    /**
     * @brief Calculate the Distance square of the Particle
     *
     * @param A Particle to calculate distance with
     * @return double Distance
     **/
    inline double Distance2(Particle & A);
    /**
     * @brief Give the position
     *
     * @return physvector< DIM > Postion
     **/
    inline physvector<DIM> GetPos() const;
    
    /**
     * @brief Give the speed
     *
     * @return physvector< DIM > Speed
     **/
    inline physvector<DIM> GetSpeed() const;
    
    /**void ParticleReal::serialize(Archive& ar, const unsigned int version)
{
ar & m_pos;
ar &m_speed;
ar &m_rho;
ar &m_
}
     * @brief Give the current calculated force
     *
     * @return physvector< DIM > Force
     **/
    inline physvector<DIM> GetAcceleration() const;
    /**
     * @brief Get the mass
     *
     * @return double mass
     **/
    inline double GetM() const; 
    /**
     * @brief Get the density
     *
     * @return double rho
     **/
    inline double GetDensity() const;
        /**
     * @brief Get the pressure
     *
     * @return double rho
     **/
    inline double GetP() const;
    /**
     * @brief Set the mass
     *
     * @param m Mass
     * @return void
     **/
    inline void SetM(double m);
    /**
     * @brief Set the density
     *
     * @param rho density
     * @return void
     **/
    inline void SetDensity(double rho);
    /**
     * @brief Set the pressure
     *
     * @param p pressure
     * @return void
     **/
    inline void SetP(double p);
    /**
     * @brief Set the postion
     *
     * @param pos postion
     * @return void
     **/
    inline void SetPos(physvector<DIM> pos);
   
    
    /**
     * @brief Set the speed
     *
     * @param speed Speed
     * @return void
     **/
    inline void SetSpeed(physvector<DIM> speed);
     
    /**
     * @brief Set the force
     *
     * @param force Force
     * @return void
     **/
    inline void SetAcceleration(physvector<DIM> force);
	  
    /**
     * @brief Add the force to the current force
     *
     * @param force Force to add
     * @return void
     **/
    inline void AddAcceleration(physvector<DIM> force);
	  
	  inline void ResetAcceleration();
	  
	   /**
     * @brief Get the particle of distance less than h in the list
     *
     * @param Neighbour list of Particles in witch look
     * @param h distance
     * @return Particles Found List
     **/
    Particles FindNeighbour(list< Particles* > Neighbour, double h);
    /**
     * @brief Compute the pressure and density of the given particle using the Particles as Neighbour
     * 
     * This will change the particle pressure and density.
     * 
     * @param FindVoisin List of Neighbour to evaluate
     * @return void
     **/
  inline  void ComputePressure_Density(const Particles & FindVoisin);
  
  
  /**
   * @brief Compute internal force. The computed force will be added to the force variable of the particle
   *
   * @param FindVoisin ...
   * @return void
   **/
  inline void ComputeInternal_Force(const Particles &FindVoisin);
  /**
   * @brief Compute the gravity force and add it to the particle force.
   *
   * @return void
   **/
  inline void ComputeGravity_Force();
  /**
   * @brief Move the particle with the calculated force, updating position and velocity.
   *
   * The euler algorithm is used. With \f$ v \f$ 
   * the velocity , \f$ x \f$ the position, \f$ a \f$ the acceleration
   * and \f$ \Delta t \f$  the time step.
   * \f{align*}{
   * v_{i+1}&=v_{i}+\Delta t a_{i}\\
   * x_{i+1}&=x_{i}+\Delta t v_{i+1}
   * \f}
   * @param dt time step
   * @return void
   **/
  inline void ComputeMove(double dt);
   /**
   * @brief Verify that the two object represent the same particle (ie they share the same memory)
   *
   * @param part Particle to test
   * @return bool
   **/
  inline bool Equal(const Particle part) const;
  
  
    inline void Dump();
   inline void ComputeSurface_Force(const Particles & FindVoisin);
   inline void ComputeSurface_Tensor(const Particles &FindVoisin);
   inline physvector<DIM> Color_Grad(const Particles &FindVoisin,ParticleType A,ParticleType B) const;
 inline  physvector<DIM> ComputeSurface_Tensor(const Particles &FindVoisin,ParticleType A,ParticleType B) const;
private:
  friend class boost::serialization::access;
      template<class Archive>
   inline void serialize(Archive & ar, const unsigned int version);
};



#include "particle_real.htt"
#endif // PARTICLE_REAL_H
