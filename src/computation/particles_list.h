#ifndef PARTICLES_LIST_H
	#define PARTICLES_LIST_H
	#include <map>
	#include "particles.h"
	#include "particle.h"
	#include "particles_deque_list.h"
	#include "key.h"
	#include "tbb/tbb.h"
	#include <sys/times.h>
	class World;
	/**
	 * @brief Preprocessor variable if defined we use parallel method for calculation
	 **/
	#define PARALLEL
	/**
	 * @brief Preprocessor variable if defined we output information on timing of all calculation
	 * Usefull for profiling.
	 **/
	#define OUTPUT_PART_TIMING
	
	/**
	 * @brief Global Constant used in parallel method, indicate the number of Particles treated in one block.
	 * 
	 **/
	const int CHUNK_SIZE=1;
	using namespace std;
	using namespace tbb;
	/**
	 * @brief Contain all the particles object in a map. Creating the geometric relation between particles.
	 *
	 **/
	class Particles_List
	{
private:
	World *m_w;
	/**
	 * @brief Used in the parallel version. Object passed to all parallel_for,
	 * Parallel_Reduce, this allow to have the calculation done in the same physical processor.
	 **/
	mutable affinity_partitioner m_af;
	/**
	 * @brief Map of particles.
	 **/
	map<Key<DIM>,Particles> m_list;
	/**
	 * @brief Deque of particles containing all particles.
	 * 
	 * Usefull in parallel calculation because of the direct acess.
	 **/
	Particles_Deque_List m_vect;
	
	/**
	 * @brief Current time of the simulation.
	 **/
	double m_t;
	
	/**
	 * @brief Total number of particles. Needed for output.
	 **/
	int m_n;
	
public:
	/**
	 * @brief Create a empty list of particles.
	 *
	 **/
	Particles_List(World * w);
	
	/**
	 * @name Public Interface
	 *
	 **/
	//@{
	 
	 /**
	 * @brief Compute a complete time iteration.
	 * If particles were added Calculate0Density() need to be called before to have a correct result.
	 * @return void
	 **/
	void Compute(double &dt);
	
	/**
	 * @brief Output data for the current timestep to file.
	 *
	 * File are numbered from 0. And begin with outXXXX
	 * File are in a format to be read by ParaView
	 *
	 **/
	inline void write(double dt) const;
	
	/**
	 * @brief Get the current time.
	 **/
	inline double GetTime() const;
	
	 /**
	 * @brief Add the particle in the list. Adding it in the good particles. And creating the link.
	 *
	 * @param part Particle to add.
	 * @return void
	 **/
	inline void Add(Particle part);
	
		
	/**
	 * @brief Choose the mass for new particles so that the particles is at rest density.
	 * Need to be called after somes particles are added.
	 *
	 * This function need to be called only once.
	 **/
	void Calculate0Density();
	 //@}
protected:

	/**
	 * @name Structure
	 * This method are used for structural change of the structur
	 **/
	 //@{
	 /**
	 * @brief Uttility function, update neighbour of key k and it's neighbour
	 *
	 * @param k where to update
	 * 
	 * @invariant It's very important that the neighbour of the key are correctly added.
	 * Because when we delete a Particles we need to delete all reference to it.
	 * @return void
	 **/
	inline void AddNeighbour(Key<DIM> k);
	
	public:
	/**
	 * @brief Update particle container for iterator it in part container.
	 *
	 * @param it Iterator to particle to update.
	 * @param part Particles in wish the particle curently is.
	 *
	 * \attention it may be invalided because of splicing.
	 **/
	inline void Update(list<Particle>::iterator & it,Particles * part);
	protected:
	 //@}
	 
	 /**
	  * @name Conjugate Gradient
	  **/
	  //@{
	  #ifdef PRESSURE_LAPLACIEN
	 inline void CalculatePressureGradiant();
	 inline void CalculatePressureLaplacian();
	 public:
	 inline void CalculatePressForConjugateGradiant();
protected:
	  void GetMaxCGGradCorrection(double &corect);
	  void CorrectPosition();
	  void SolveLinearSystem();
	  void OutputB(fstream &out);
	  void SetPToP1();
	 void Store0PosAndSpeed();
	void CorrectSpeed();
	void PrepareSpeed();
	void PreparePos();
	double TestPositionOK(bool &b);
	double TestSpeedOK(bool &b);;
	void TestPositionOKShort(bool &b);
	void TestSpeedOKShort(bool &b);;
	void To0Pos();
	  /**
	 * @brief Used for incompressible sph. Initialize for conjugate gradient.
	 * using the matrice and value store by the particles.
	 **/
	void InitializeCG();
	
	/**
	 * @brief Calculate Alpha for conjugate gradient.
	 *
	 * @param num The numerator will be stored there it's used for calculating beta.
	 * @param b Return true if we have converged.
	 **/
	double CalculateAlpha(double &num,bool &b);
	
	/**
	 * @brief Calculate Beta for conjugate gradient.
	 *
	 * @param denom The numerator calculated for Alpha and reused as denominator.
	 * @param b Return true if we have converged.
	 * @param alpha Value of alpha used to calculate beta.
	 **/
	double CalculateBeta(double &denom,double alpha,double &rmax);
	
	/**
	 * @brief Last step for conjugate gradient using beta.
	 *
	 * @param bet Beta value to use.
	 **/
	void CalculateP1(double bet);
	
	/**
	 * @brief Calculate the conjugate gradient for the incompressible sph step.
	 **/
	void ConjugateGradiant(fstream &out);
	bool ConjugateGradiantOneiter(double &rmax);
	/**
	 * @brief Use incompressible correction algorithm to correct position and speed
	 *
	 **/
	inline void  CorrectDensity();
	
	/**
	 * @brief used in incompressible correction algorithm for pasing to the speed iteration.
	 * It correct the position with the result of pressure at the same time.
	 **/
	void SetB_Speed();
	/**
	 * @brief used in incompressible correction algorithm for pasing to the Position iteration.
	 * It correct the speed with the result of pressure at the same time.
	 *
	 * @param b True if not converged.
	 **/
	void PreparePosition(bool &b);
	
	void TestCGSolution(double &R);
	#endif
	  //@}
	
	
	/**
	 * @name Command
	 **/
	
	//@{
	/**
	 * @brief Update the force. Need to be called before all method that need a correct force.
	 **/
	void UpdateForce() const;

	
	/**
	 * @brief Compute the next position and speed using a predictor corrector algorithm
	 *
	 * @param DT Time step to use.
	 **/
	void predictor_corrector_compute(double DT);
	/**
	 * @brief Estimated the next timestep.
	 **/
	double NextTimeStep() const;
	
	/**
	 * @brief Compute the next time step with Beeman method.
	 * 
	 * @param DT Time step.
	 **/
	void beeman_compute(double DT);
	//@}
	
	/**
	 * @name Debug and Deprecated
	 **/
	//@{
	/**
	 * @brief Deprecated
	 **/
	void FindBoundary();
	/**
	 * @brief Used for debuging purpose. Print somes usefull informations.
	 **/
	void Dump();
	//@}

	friend class Test_Particles;
	friend class Test_Particles_List;
	};



#include "particles_list.htt"

#endif // PARTICLES_LIST_H
