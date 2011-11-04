/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#ifndef PARTICLE_REAL_H
#define PARTICLE_REAL_H

#include "type.h"
#include "physvector.h"
#include "tensor.h"
#include "const.h"
#include <list>
#include "particle.h"
#include "particles.h"

class Voisin;
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
	
	/** 
	 * @brief Cache for the value of force. For not calculating it 2 times.
	 **/
mutable	physvector<DIM> m_force;
//Variable for conjugate gradient


	


		/**
	 * @brief Point to Voisin.
	 **/
    Voisin*  m_voisin;

  /**
   * @brief Position
   **/
  physvector<DIM> m_pos;
  physvector<DIM> m_pos0_5;
   physvector<DIM> m_pos0;
  /**
   * @brief Speed
   **/
  physvector<DIM> m_speed;
  physvector<DIM> m_speed0_5;
  physvector<DIM> m_speed0;

  

  



    /**
  * @brief A fixed particle cannot move.
  **/



 
     
	  
	
    
    
    
    

    
    
    
 
 
		    /**
   * @brief Density of particle \f$ \sum W \f$
   **/

    
	 ParticleType m_type;
	  bool m_fixed;
	      Particles* m_container;
		  double m_density;
		   /**
   * @brief Mass
   **/
  double m_m;
   double m_b;
  /**
   * @brief Surface tension
   **/
   double m_p;
	double m_pv;
	double m_px;
	    double m_p1;
		double m_r;
		double m_rprec;
		double m_zprec;
		double m_z;
		bool m_boundary;
			bool m_converged;
			/** 
	 * @brief True if we have initalized the 0 density.
	 **/
	bool m_b_0_done;
  int m_nb_it;
      double m_1_over_m;
  double m_1_over_density_2;

	  	bool m_const_speed;
		
			/**
	 * @brief Pointer to the container.
	 **/
   
	
	 
	  
	  double m_density0;
	
    
	 /**
   * @brief Type of particle.
   **/
  physvector<DIM> m_surface_tens;
 
 Tensor<DIM> m_sub_grid;

public:
/**
	 * @brief Calculate next time step restriction for the force.
	 **/
inline void NextForceTimeStep(double &dt)const;
/**
	 * @brief Calculate next time step restriction for the courant and viscious term.
	 **/
inline void NextCourantVisciousTimeStep(double &dt) const;
/**
	 * @brief Get the number of iteration for the predictor correction step.
	 **/
inline int GetNb_It()const;
/**
	 * @brief Write position in a file format for ParaView.
	 * 
	 * @param out Output to write.
	 **/
inline void WritePos(fstream& out)const;
inline void SetBoundary(bool b);
//For conjugate gradiant
/**
	 * @brief Calculate the A matrice for Gradient conjugate
	 **/
inline double CalculateA(const Particle& B)const;

inline void Calculate0Density();

inline double CalculateABas(const Particle& B)const;

inline bool GetBoundary() const;


inline double GetB() const;
inline void SetB(double val);

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
inline void AddRprec(double val);
inline void AddP1(double val);
inline void AddP(double val);

inline void SetB_Speed();

inline double MultRZ() const;

inline double MultRZprec() const;

inline void UpdateRZ() ;
inline void PreparePosition(bool &b);
inline bool OKR() const;
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
    inline ParticleReal(physvector<DIM> pos,ParticleType type,bool fixed=false);

        /**
     * @brief Create a individual Particle with givent property
     *
     * @param pos Particle position
     * @param speed Particle speed
     * @param type Particle type
     * @param m Particle mass
     **/
      inline ParticleReal(physvector<DIM> pos,physvector<DIM> speed,ParticleType type,bool fixed=false);
    /**
     * @brief Calculate the Distance square of the Particle
     *
     * @param A Particle to calculate distance with
     * @return double Distance
     **/
    inline double Distance2(const Particle & A) const;

      inline double Distance(const Particle & A) const;
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
    inline double GetMass() const;
    /**
     * @brief Get the density
     *
     * @return double rho
     **/
    inline double GetDensity() const;

inline double GetMassDensity() const;

inline double GetPressure() const;
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

  inline void ComputeMove(double dt);
	inline void preComputeMove_predictor(double dt);
	inline void ComputeMove_predictor(double dt,bool &b);
	inline void DoMove_predictor();
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
  inline void Dump() const;


  void SetContainerParticles(Particles * container);
inline void GetVoisin( Voisin & voisin) const;
 inline void SetConstSpeed(bool b);
 inline bool GetConstSpeed();
 inline void CalculateSubGridTens();
private:

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
 inline physvector<DIM> Force() const;
 
 inline bool GetIsInBoundaryRegion()const;
 


};



#include "particle_real.htt"
#endif // PARTICLE_REAL_H
