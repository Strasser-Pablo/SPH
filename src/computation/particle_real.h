/*
   Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
 */


#include "type.h"
#include "physvector.h"
#include "tensor.h"
#include "const.h"
#include <list>
#include "particles.h"
#include "particle.h"

	/**
	 * \file 
	 * @brief Contain Header for class Particle_Real, containing the particle.
	 *
	 **/
	 
#ifndef PARTICLE_REAL_CLASS
	/**
	 * @brief Header guard for declaration of class Particle_Real
	 **/
	#define PARTICLE_REAL_CLASS
	
	class Voisin;
	
	using namespace std;
	//class Particles;
	/**
	 * @brief Represent an individual Particle. This class contain the actual calculation of pressure, density ...
	 **/
	class ParticleReal
	{

	/**
	 * @brief Cache for the value of force. For not calculating it 2 times.
	 **/
	mutable physvector<DIM> m_force;
	physvector<DIM> m_force2;
	physvector<DIM> m_force3;
	
	mutable physvector<DIM> m_force_pres;
	mutable physvector<DIM> m_force_viscious;
	mutable physvector<DIM> m_force_turbulence;
	mutable physvector<DIM> m_force_gravity;
	/**
	 * @brief Pointer to Voisin.
	 **/
	Voisin*  m_voisin;
	/**
	 * @brief Position
	 **/
	physvector<DIM> m_pos;
	double m_div;
	/**
	 * @brief Position at halfstep;
	 **/
	physvector<DIM> m_pos0_5;
	/**
	 * @brief  Position before correction and other step.
	 **/
	physvector<DIM> m_pos0;
	/**
	 * @brief Speed
	 **/
	physvector<DIM> m_speed;
	/**
	 * @brief Speed at half time step
	 **/
	physvector<DIM> m_speed0_5;
	/**
	 * @brief  speed before correction and other step.
	 **/
	physvector<DIM> m_speed0;
	/**
	 * @brief Type of particle (watter, air, etc). Not a lot used.
	 **/
	ParticleType m_type;
	/**
	 * @brief A fixed particle cannot move.
	 **/
	bool m_fixed;
	/**
	 * @brief Pointer to containing container.
	 **/
	Particles* m_container;
	/**
	 * @brief Density of particle \f$ \sum W \f$
	 *
	 * @attention It's Density of particle, not density of mass.
	 **/
	double m_density;
	/**
	 * @brief Mass
	 **/
	double m_m;
	/**
	 * @brief Second member for solving linear equation, used it the incompressible case.
	 **/
	double m_b;
	
	bool m_once_calculate0Dens;
	physvector<DIM> m_grad_p;
	double m_lap_p;
   #ifdef PRESSURE_LAPLACIEN
   	//Variable used for conjugate gradient.
		/**
		 * @brief Pressure. Used in the incompressible case.
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
   #endif
	/**
	 * @brief True if we have initalized the 0 density.
	 **/
	bool m_b_0_done;
	/**
	 * Number of iteration
	 **/
	int m_nb_it;
	int m_nb_itx;
	int m_nb_itv;
	/**
	 * Value of \f$ \frac{1}{m}\f$
	 **/
	double m_1_over_m;
	/**
	 * Value of \f$ \frac{1}{\sigma^2}\f$
	 **/
	double m_1_over_density_2;
	/**
	 * @brief Indicate if speed need to remain constant.
	 **/
	bool m_const_speed;
	/**
	 * @brief 0 Density of particle. Used for the incompressible case.
	 **/
	double m_density0;


	/**
	 * @brief Tensor for surface force.
	 * @deprecated No used for the moment
	 **/
	physvector<DIM> m_surface_tens;

	/**
	 * @brief the subgrid tensor.
	 **/
	Tensor<DIM> m_sub_grid;


public:

/**
	 * @brief Default Constructor
	 **/
	inline ParticleReal();
	/**
	 * @brief Create a individual Particle with given property with initial speed 0.
	 *
	 * @param pos Particle position
	 * @param type Particle type
	 * @param fixed True if particle is fixed.
	 **/
	inline ParticleReal(physvector<DIM> pos,ParticleType type,bool fixed=false);

	/**
	 * @brief Create a individual Particle with given property
	 *
	 * @param pos Particle position
	 * @param speed Particle speed
	 * @param type Particle type
	 * @param fixed True if particle is fixed.
	 **/
	inline ParticleReal(physvector<DIM> pos,physvector<DIM> speed,ParticleType type,bool fixed=false);
	
	/**
	 * @name Structure
	 **/
	 //@{
	    #ifdef PRESSURE_LAPLACIEN
		/**
		 * Set if boundary.
		 *
		 * @param b If boundary or not.
		 **/
		inline void SetBoundary(bool b);
		
	/**
	 * @brief Return if boundary or not.
	 *
	 * @return True if boundary.
	 **/
	inline bool GetBoundary() const;
   #endif
	 
	 /**
	 * @brief Set to the particles that contain this particle.
	 *
	 * @param container Container that contain the particle.
	 **/
	void SetContainerParticles(Particles * container);
	/**
	 * @brief Obtain the Neighbour of particle.
	 *
	 * @param voisin Neighbour found.
	 **/
	inline void GetVoisin( Voisin & voisin) const;
	 //@}
	 
	 /**
	  * @name Command
	  * 
	  **/
	  //@{
	  /**
	 * @brief Calculate next time step restriction for the force.
	 * 
	 * @param dt Time Step
	 **/
	inline void NextForceTimeStep(double &dt) const;
	/**
	 * @brief Calculate next time step restriction for the courant and viscious term.
	 * 
	 * @param dt Time Step
	 **/
	inline void NextCourantVisciousTimeStep(double &dt) const;
	
	/**
	 * @brief Choose the mass so that we have a correcte rest 0 density.
	 **/
	inline void Calculate0Density(double &m);
	
	/**
	 * @brief Set the Particle mass to the MEAN_MASS
	 **/
	inline void SetToMeanMass();
	
	/**
	 * @brief Compute the pressure and density of the given particle using the Particles as Neighbour
	 *
	 * This will change the particle pressure and density.
	 * The density is defined as:
	 ***\f[ \sigma_{i}=\sum_{j} W_{ij} \f]
	 *
	 * @return void
	 **/
	inline void ComputeDensity();
	/**
	 * @brief compute a move using euler.
	 **/
	inline void ComputeMove(double dt);
	/**
	 * @brief Prepare a move of predictor corrector.
	 *
	 * @attention Don't test if boundary.
	 **/
	inline void preComputeMove_predictor(double dt);
	/**
	 * @brief Loop of predictor corrector move.
	 *
	 * @param dt Time step to use.
	 * @param b This reference will become true if we have not converged.
	 *                      If b has a value of true, it will remain true.
	 **/
	inline void ComputeMove_predictor(double dt,bool &b);
	/**
	 * @brief Effectivelly do the predictor corrector move.
	 **/
	inline void DoMove_predictor();
   #ifdef PRESSURE_LAPLACIEN
		/**
		 * @brief used in the incompressible case
		 **/
		inline bool PreComputeMove(double dt);
   #endif

	inline void Beeman_compute(double dt);
	inline void   Beeman_precompute(double dt);
	inline void Beeman_first_time(double dt);
	
	/**
	 * @brief Calculate minus the Sub Grid Tensor.
	 *              And store it.
	 **/
	inline void CalculateSubGridTens();
	protected:
	/**
	 * @brief Calculate the force.
	 *
	 * @return Force of the particle.
	 **/
	inline physvector<DIM> Force() const __attribute__ ((hot));
	
	public:
		inline void UpdateForce() const;
	
	  //@}
	
	/**
	 * @name Setter and Getter
	 **/
	 //@{
	 
/**
	 * @brief Give the position.
	 *
	 * @return physvector< DIM > Postion
	 **/
	inline physvector<DIM> GetPos() const;

	/**
	 * @brief Give the speed.
	 *
	 * @return physvector< DIM > Speed
	 **/
	inline physvector<DIM> GetSpeed() const;


	/**
	 * @brief Get the mass.
	 *
	 * @return double mass
	 **/
	inline double GetMass() const;
	/**
	 * @brief Get the density.
	 *
	 * @return double Particle density.
	 **/
	inline double GetDensity() const;
	/**
	 * @brief Get the mass density.
	 *
	 * @return double Particle mass density.
	 **/
	inline double GetMassDensity() const;

	/**
	 * Get The pressure calculated from the equation of state.
	 **/
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
	 * @brief Set If particle is constraint to a constant speed
	 *
	 * @param b True if constraint to constant speed.
	 **/
	inline void SetConstSpeed(bool b);
	/**
	 * @brief Get If particle is constraint to a constant speed
	 *
	 * @return True if particle speed is fixed.
	 **/
	inline bool GetConstSpeed();
	
	inline physvector<3> GetForce() const;
	 //@}
	 
	 /**
	  * @name Conjugate Gradient
	  **/
	  
	  //@{
	  inline void GetMaxCGGradCorrection(double &correct);
	  inline void CalculatePressureGradiant();
	  inline void CalculatePressureLaplacian();
	  //Used for conjugate gradient
   #ifdef PRESSURE_LAPLACIEN
   		inline void CorrectPosition();
		inline void Store0PosAndSpeed();
		inline void TestCGSolution(double &R);
		inline void SetPToP1();
		inline void OutputB(fstream &out);
		inline void CorrectSpeed();
		inline void PrepareSpeed();
		inline void PreparePos();
		inline void To0Pos();
		inline double TestSpeedOK(bool &b);
		inline double TestPositionOK(bool &b);
		inline double GetB() const;
		inline void SetB(double val);
		inline double GetLapP();
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

		inline void UpdateRZ();
		inline void PreparePosition(bool &b);
		inline bool OKR(double & rmax) const;
   #endif
	  
	    
   //For conjugate gradiant
	/**
	 * @brief Calculate the A matrice for Gradient conjugate
	 **/
	inline double CalculateA() const;

	
	/**
	 * @brief A sub calculus for the A matrix for the incompressible case.
	 **/
	inline double CalculateABas(const Particle& B) const;
	
	  //@}
	  
	  /**
	   * @name Output
	   * 
	   **/
	   //@{
	   /**
	 * @brief Write position in a file format for ParaView.
	 *
	 * @param out Output to write.
	 **/
	 #ifdef PRESSURE_LAPLACIEN
	 inline void WritePressuresPos(fstream &out) const;
	 #endif
	 inline void WriteDiv(fstream &out) const;
	 
	 #ifdef PRESSURE_LAPLACIEN
	 inline void WritePressuresSpeed(fstream &out) const;
	 	#endif
	inline void WritePos(fstream& out) const;
	inline void WriteSpeed(fstream & out) const;
	inline void WriteErf(fstream & out,double t) const;


	inline void WriteForce(fstream &out) const;
		inline void WriteForceGravity(fstream &out) const;
		inline void WriteForcePressure(fstream &out) const;
		inline void WriteForceViscosity(fstream &out) const;
		inline void WriteForceTurbulence(fstream &out) const;
		inline void WriteForcePressureOneLine(fstream &out) const;
		inline void WriteNbItPos(fstream &out) const;
		inline void WriteNbItSpeed(fstream &out) const;
	   //@}
	   
	   /**
	    * @name Distance and Misceleanus
		**/
		//@{
		
		/**
	 * @brief Get the number of iteration for the predictor correction step.
	 **/
	inline int GetNb_It() const;
	
	/**
	 * @brief Calculate the Distance square of the Particle
	 *
	 * @param A Particle to calculate distance with.
	 * @return double Distance square
	 **/
	inline double Distance2(const Particle & A) const;
	/**
	 * @brief Calculate the Distance of the Particle
	 *
	 * @param A Particle to calculate distance with
	 * @return double Distance.
	 **/
	inline double Distance(const Particle & A) const;

	/**
	 * @brief Calculate the Distance of the particle with max norm of the Particle
	 *
	 * @param A Particle to calculate distance with
	 * @return double Distance.
	 **/
	inline double DistanceMax(const Particle & A) const;
	
	
	/**
	 * @brief Verify that the two object represent the same particle (ie they share the same memory)
	 *
	 * @param part Particle to test
	 * @return bool
	 **/
	inline bool Equal(const Particle part) const;
	
	inline bool operator==(const ParticleReal & B) const;
	inline bool operator==(const Particle & B) const;
	
		//@}
	
		/**
		 * @name Deprecated and Debug
		 * 
		 **/
	
		//@{

	/**
	 * @brief Compute the surface force
	 *
	 * @return void
	 **/
	inline physvector<DIM> ComputeSurface_Force();
	/**
	 * @brief Compute the surface tensor used after to compute surface force.
	 *
	 * @return void
	 **/
	inline void ComputeSurface_Tensor();
	/**
	 * @brief Gradiant of color
	 *
	 * @param A First Color
	 * @param B Second Color
	 * @return physvector< 3 >
	 **/
	inline physvector<DIM> Color_Grad(ParticleType A,ParticleType B) const;
	/**
	 * @brief Compute the surface tensor between two interface type
	 *
	 * @param A First Type
	 * @param B Second Type
	 * @return physvector< 3 >
	 **/
	inline physvector<DIM> ComputeSurface_Tensor_ind(ParticleType A,ParticleType B) const;
		
	/**
	 * @brief Dump the value of the class. Usefull for debuging
	 *
	 * @return void
	 **/
	inline void Dump() const;
		//@}
	
private:

	friend class Test_Particles_List;
	friend class World;

	};
#endif // PARTICLE_REAL_CLASS
#include "particle_real.htt"
