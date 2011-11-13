#ifndef PARTICLES_LIST_H
#define PARTICLES_LIST_H
#include <map>
#include "particles.h"
#include "particle.h"

#include "key.h"


using namespace std;

/**
 * @brief Contain all the particles object in a map. Creating the geometric relation between particles.
 *
 **/
class Particles_List
{
	/**
	 * @brief Map of particles.
	 **/
	map<Key<DIM> ,Particles> m_list;
	/**
	 * @brief Current time of the simulation.
	 **/
	double m_t;
	/**
	 * @brief Total number of particles. Needed for output.
	 **/
	int m_n;
protected:
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
	double CalculateBeta(double &denom,bool &b,double alpha);
	/**
	 * @brief Last step for conjugate gradient using beta.
	 *
	 * @param bet Beta value to use.
	 **/
	void CalculateP1(double bet);
	/**
	 * @brief Calculate the conjugate gradient for the incompressible sph step.
	 **/
	void ConjugateGradiant();

	/**
	   * @brief Uttility function, update neighbour of key k and it's neighbour
	   *
	   * @param k where to update
	   * @return void
	   **/
	inline  void AddNeighbour(Key<DIM> k);

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
	
	/**
	 * @brief Deprecated
	 **/
	void FindBoundary();
	
	void UpdateForce()const;
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
	/**
	 * @brief Choose the mass for new particles so that the particles is at rest density.
	 * Need to be called after somes particles.
	 *
	 * The computation is only make one time per particle.
	 **/
	void Calculate0Density();

	/**
	 * @brief Create a empty list of particles.
	 *
	 **/
	Particles_List();

	/**
	 * @brief Add the particle in the list. Adding it in the good particles. And creating the link.
	 *
	 * @param part Particle to add.
	 * @return void
	 **/
	inline  void Add(Particle  part);

	/**
	 * @brief Compute a complete time iteration.
	 * If particles were added Calculate0Density() need to be called before to have a correct result.
	 * @return void
	 **/
	  void Compute(double &dt);

	/**
	 * @brief Used for debuging purpose. Print somes usefull informations.
	 **/
	void Dump();
	/**
	 * @brief Remove particles because it's empty.
	 *
	 * @param parts Particles to remove.
	 **/
	inline void RemoveParticles(const Particles * Parts);

	/**
	 * @brief Output data for the current timestep to file.
	 *
	 * File are numbered from 0. And begin with outXXXX
	 * File are in a format to be read by ParaView
	 *
	 **/
	inline  void write(double dt) const;
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
	 * @brief Get the current time.
	 **/
	inline	double GetTime() const;


};




#include "particles_list.htt"

#endif // PARTICLES_LIST_H
