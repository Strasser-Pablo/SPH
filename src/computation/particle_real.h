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

/**
 * \file particle_real.h Contain Header for class Particle_Real, containing the particle.
 *
 **/
using namespace std;
class Particles;
    /**
   * @brief Represent an individual Particle. This class contain the actual calculation of pressure, density ...
   **/
class ParticleReal
{
  /**
   * @brief Position
   **/
  physvector<DIM> m_pos;
  /**
   * @brief Speed
   **/
  physvector<DIM> m_speed;
  /**
   * @brief Acceleration
   **/
  physvector<DIM> m_a;
  /**
   * @brief Mass
   **/
  double m_m;
  /**
   * @brief Density of particle \f$ \sum W \f$
   **/
  double m_density;

  /**
   * @brief Pressure
   **/
  double m_p;

  /**
   * @brief Surface tension
   **/
  physvector<DIM> m_surface_tens;
  /**
   * @brief Type of particle.
   **/
  ParticleType m_type;

  /**
  * @brief A fixed particle cannot move.
  **/
  bool m_fixed;
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
     **/
    inline ParticleReal(physvector<DIM> pos,ParticleType type,double m,bool fixed=false);

        /**
     * @brief Create a individual Particle with givent property
     *
     * @param pos Particle position
     * @param speed Particle speed
     * @param type Particle type
     * @param m Particle mass
     **/
      inline ParticleReal(physvector<DIM> pos,physvector<DIM> speed,ParticleType type,double m,bool fixed=false);
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

    /**
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
     * @brief Add the Acceleration to the current acceleration
     *
     * @param force Acceleration to add
     * @return void
     **/
    inline void AddAcceleration(physvector<DIM> force);

    /**
    * @brief Put the actual acceleration to 0.
    *
    **/
	  inline void ResetAcceleration();

	   /**
     * @brief Get the particle of distance less than h in the list
     *
     * @param Neighbour list of Particles in witch look
     * @param h distance
     * @return Particles Found List
     **/
    void FindNeighbour(list< Particles* > Neighbour, double h,Particles& Find);
    /**
     * @brief Compute the pressure and density of the given particle using the Particles as Neighbour
     *
     * This will change the particle pressure and density.
     * The density is defined as:
     *\f[ \sigma_{i}=\sum_{j} W_{ij} \f]
     *
     * @param FindVoisin List of Neighbour to evaluate
     * @return void
     **/
  inline  void ComputePressure_Density(const Particles & FindVoisin);


  /**
   * @brief Compute internal force. The computed force will be added to the force variable of the particle
   *
   * For the acceleration:
   * \f[ a^p_i=-\frac{1}{m_i}\sum_{j\neq i}\left(\frac{p_i}{\sigma_{i}^2}+\frac{p_j}{\sigma_{j}^2}\right)\nabla W_{ij} \f]
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


  /**
   * @brief Dump the value of the class. Usefull for debuging
   *
   * @return void
   **/
  inline void Dump();
  /**
   * @brief Compute the surface force
   *
   * @param FindVoisin List of neighbour
   * @return void
   **/
  inline void ComputeSurface_Force(const Particles & FindVoisin);
  /**
   * @brief Compute the surface tensor used after to compute surface force.
   *
   * @param FindVoisin List of neighbour
   * @return void
   **/
  inline void ComputeSurface_Tensor(const Particles &FindVoisin);
  /**
   * @brief Gradiant of color
   *
   * @param FindVoisin list of neighbour
   * @param A First Color
   * @param B Second Color
   * @return physvector< 3 >
   **/
  inline physvector<DIM> Color_Grad(const Particles &FindVoisin,ParticleType A,ParticleType B) const;
  /**
   * @brief Compute the surface tensor between two interface type
   *
   * @param FindVoisin List of Neighbour
   * @param A First Type
   * @param B Second Type
   * @return physvector< 3 >
   **/
  inline  physvector<DIM> ComputeSurface_Tensor_ind(const Particles &FindVoisin,ParticleType A,ParticleType B) const;
  #ifndef DOXYGEN
private:
  friend class boost::serialization::access;
    #endif //DOXYGEN
      /**
       * @brief Used to Serialize the class
       *
       * @param ar Archive to witch read or write
       * @param version version number, Unused.
       * @return void
       **/
        template<class Archive>
      inline void serialize(Archive & ar, const unsigned int version);
};



#include "particle_real.htt"
#endif // PARTICLE_REAL_H
