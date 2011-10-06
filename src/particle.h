#ifndef PARTICLE_H
#define PARTICLE_H

class ParticleReal;

 /**
   * @brief Opaque Pointer to ParticleReal
   *
   * This allow to have multiple copy of Particle. That all point on the same physical Particle.
   * To access the particle pointed, we dereference the class.
   * 3d Example
   * \code
   * ParticleReal real(physvector<3>(3.0,4.0,5.0),water,3.0,2.0,1.0);
   * Paricle p1(real);
   * Particle p2(real);
   * p1->SetM(4.0);
   * cout<<p1->GetM()<<" "<<p2->GetM()<<endl
   * \endcode
   * Will produce 4.0 4.0.
   * 
   * \attention The real ParticleReal used to create 
   * the Particle need to be delete only after all acces to Particle. 
   * No teste are done before deferencing the pointer.
   * 
   **/
class Particle{
 ParticleReal* m_data; 

public:
  
  /**
   * @brief Create a Particle linked to real particle ParticleReal.
   *
   * @param part Real Particle to be linked with.
   **/
  inline Particle(ParticleReal * part);
  /**
   * @brief Return a Pointer to the linked Particle
   *
   * @return ParticleReal* Linked Particle
   **/
 inline ParticleReal* Get();
 /**
  * @brief Return a Pointer on constant to the linked Particle
  *
  * @return const ParticleReal* Linked Particle
  **/
 inline const ParticleReal* Get() const;
 /**
  * @brief Return a Reference on the linked Particle
  *
  * @return ParticleReal& Linked Particle
  **/
 inline ParticleReal& operator *();
 /**
  * @brief Return a constant Reference on the linked Particle
  *
  * @return const ParticleReal& Linked Particle
  **/
 inline const ParticleReal& operator *() const;
 /**
  * @brief Return a pointer of Particle.
  *
  * @return Particle* Pointer to this.
  **/
  inline Particle* operator &();
   /**
  * @brief Return a pointer on constant of Particle.
  *
  * @return const Particle* Pointer to this.
  **/
    inline  const Particle* operator &() const;
    /**
     * @brief Allow to access member of Linked Particle.
     *
     * @return ParticleReal*
     **/
 inline ParticleReal* operator ->();
     /**
     * @brief Allow to access member of Linked Particle.
     *
     * @return ParticleReal*
     **/
  inline const ParticleReal* operator ->() const;


};




#include "particle.htt"
//Need to include after and not before for not having incomplete type.
#include "particle_real.h"

#endif