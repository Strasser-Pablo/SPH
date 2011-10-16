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
#include "particles.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

/**
 * \file particle_real.h Contain Header for class Particle_Real, containing the particle.
 *
 **/
using namespace std;
//class Particles;
    /**
   * @brief Represent an individual Particle. This class contain the actual calculation of pressure, density ...
   **/
class ParticleReal
{
    //Used for conjugate gradiant
    double m_r;
    double m_z;
    double m_zprec;
    double m_rprec;
    double m_p1;
    double m_px;
    double m_pv;

    double m_p;


    Particles* m_container;
    Particles  m_voisin;

  /**
   * @brief Position
   **/
  physvector<DIM> m_pos;
  /**
   * @brief Speed
   **/
  physvector<DIM> m_speed;
  /**
   * @brief Mass
   **/
  double m_m;
  /**
   * @brief Density of particle \f$ \sum W \f$
   **/
  double m_density;

double m_density0;


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
//For conjugate gradiant

inline double GetR() const;
inline void SetR(double val);

inline double GetRprec() const;
inline void SetRprec(double val);

inline double GetZprec() const;
inline void SetZprec(double val);

inline double GetZ() const;
inline void SetZ(double val);

inline double GetP1() const;
inline void SetP1(double val);

inline double GetP() const;
inline void SetP(double val);

inline void AddR(double val);
inline void AddP1(double val);
inline void AddP(double val);

inline double MultRZ() const;

inline double MultRZprec() const;

inline void UpdateRZ() ;
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
    inline ParticleReal(physvector<DIM> pos,ParticleType type,double r,double rho_0,bool fixed=false);

        /**
     * @brief Create a individual Particle with givent property
     *
     * @param pos Particle position
     * @param speed Particle speed
     * @param type Particle type
     * @param m Particle mass
     **/
      inline ParticleReal(physvector<DIM> pos,physvector<DIM> speed,ParticleType type,double r,double rho_0,bool fixed=false);
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
  inline  void ComputeDensity();



  inline bool PreComputeMove(double dt);
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


  void SetContainerParticles(Particles * container);

private:

 void UpdateVoisin();
/**
   * @brief Compute the surface force
   *
   * @param FindVoisin List of neighbour
   * @return void
   **/
  inline physvector<DIM> ComputeSurface_Force();
  /**
   * @brief Compute the surface tensor used after to compute surface force.
   *
   * @param FindVoisin List of neighbour
   * @return void
   **/
  inline void ComputeSurface_Tensor();
  /**
   * @brief Gradiant of color
   *
   * @param FindVoisin list of neighbour
   * @param A First Color
   * @param B Second Color
   * @return physvector< 3 >
   **/
  inline physvector<DIM> Color_Grad(ParticleType A,ParticleType B) const;
  /**
   * @brief Compute the surface tensor between two interface type
   *
   * @param FindVoisin List of Neighbour
   * @param A First Type
   * @param B Second Type
   * @return physvector< 3 >
   **/
  inline  physvector<DIM> ComputeSurface_Tensor_ind(ParticleType A,ParticleType B) const;
 inline physvector<DIM> Force();
 public:
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
