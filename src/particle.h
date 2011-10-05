/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#ifndef PARTICLE_H
#define PARTICLE_H
#include "type.h"
#include "physvector.h"
#include "const.h"
#include <list>
using namespace std;
class Particles;
    /**
   * @brief Represent a individual Particle
   **/
class Particle
{
    physvector<DIM> m_pos;
    double m_m;
    double m_rho;
    double m_p;
    ParticleType m_type;
public:
      /**
   * @brief Default Constructor
   **/
    inline Particle();
    /**
     * @brief Create a individual Particle with givent property
     *
     * @param pos Particle position
     * @param type Particle type
     * @param m Particle mass
     * @param rho Particle density
     * @param p Particle pressure
     **/
    inline Particle(physvector<DIM> pos,ParticleType type,double m,double rho,double p);
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
     * @return physvector< 3 > Postion
     **/
    inline physvector<DIM> GetPos() const;
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
    inline double GetRho() const;
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
    inline void SetRho(double rho);
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
     * @brief Get the particle of distance less than h in the list
     *
     * @param Neighbour list of Particles in witch look
     * @param h distance
     * @return Particles Found List
     **/
    Particles FindNeighbour(list< Particles > Neighbour, double h);
    /**
     * @brief Compute the pressure and density of the given particle using the Particles as Neighbour
     *
     * @param FindVoisin List of Neighbour to evaluate
     * @return void
     **/
    
  inline  void ComputePressure_Density(const Particles & FindVoisin);
};

#include "particle.htt"
#endif // PARTICLE_H
