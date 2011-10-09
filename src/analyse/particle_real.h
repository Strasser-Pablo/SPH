/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#ifndef PARTICLE_REAL_H
#define PARTICLE_REAL_H
#include "type.h"
#include "physvector.h"
#include "const.h"
#include <list>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

/**
* @brief Represent a individual Particle
**/
class ParticleReal
{
    physvector<DIM> m_pos;
    physvector<DIM> m_speed;
    double m_m;
    double m_rho;
    double m_p;
    double m_r;
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
    inline ParticleReal(physvector<DIM> pos,ParticleType type,double m,double rho,double p);

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
    inline ParticleReal(physvector<DIM> pos,physvector<DIM> speed,ParticleType type,double m,double rho,double p);
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
   
   
   
   inline void Draw(GLUquadric* param); 

inline double GetRadius();

private:
    friend class boost::serialization::access;
    template<class Archive>
    inline void serialize(Archive & ar, const unsigned int version);
};


void ParticleReal::Draw(GLUquadric* param)
{
  glPushMatrix(); 
  double x,y,z;

  m_pos.Get(x,y,z);
  if(m_type==water){
       glColor3ub(0, 0, 255); 
  }else{
       glColor3ub(0, 255, 0); 
  }
   glTranslated(x,y,z);
gluSphere( param,GetRadius(),20,20);
glPopMatrix();
}


#include "particle_real.htt"
#endif // PARTICLE_REAL_H
