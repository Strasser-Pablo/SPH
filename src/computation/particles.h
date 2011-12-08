/*
   Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
 */

#include "particle.h"
#include "voisin.h"
#ifndef PARTICLES_H
	#define PARTICLES_H

    #include <list>
    #include "type.h"
    #include "const.h"
    #include <map>
    #include "key.h"

	class Particle;
	class Particles_List;
	using namespace std;
	/**
	 * @brief Represent a list of Particle, inherit from std::list.
	 *
	 * @invariant If a Particles A is Neighbour (ie is in the Voisin Container)
	 *  of Particles B then B is Neighbour of Particles A. Failling to do so will
	 *  lead to a crash when removing particles.
	 *  Because the Voisin will be corrected from the list of Voisin of the particles to remove.
	 **/
	class Particles : public std::list<Particle>
	{
	/**
	 * @brief Indicated if this Particles will be deleted because it's empty.
	 * 
	 * @attention This variable muss be set only after we are sure that we can deleted
	 * it. We muss ensure that no neighbour as pointer to this particles.
	 **/
	bool m_b_muss_be_deleted;
	/**
	 * @brief Type of particle in container. Unused for the moment.
	 **/
	ParticleType m_type;

	/**
	 * @brief Neighbour of the particles. Used to loop with the neighbouring particle.
	 **/
	Voisin m_neighbour;
	/**
	 * @brief Key in witch is stored the particle.
	 **/
	Key<DIM> m_key;
public:
	
	/**
	 * @brief Construct a list of Particle of type type
	 *
	 * @param type Type of particle of the list
	 **/
	Particles(ParticleType type);
	/**
	 * @brief Copy Constructor
	 *
	 * @param A Particles to copy
	 **/
	Particles(const Particles &A);
	/**
	 * @brief Default constructor, Doesn't specify type.
	 *
	 **/
	Particles();
	/**
	 * @brief Constructor with a predefined key.
	 *
	 * @param k Key of the particles.
	 **/
	Particles(Key<DIM> &k);
	
	/**
	 * @name Structure
	 * This are function to manipulate the structure of the particles
	 **/
	//@{
	void SetMussBeDeleted(bool b);
	bool GetMussBeDeleted();
	/**
	 * @brief Remove information of Neighbour about this particles. Used when deleting neighbour.
	 * @param part Particles to remove
	 * @attention This method need to be called when we delete a particles to ensure that no Neighbour
	 *  Has pointer to this particles.
	 **/
	void RemoveParticlesNeighbour(const Particles * part);
	/**
	 * @brief Set the actual Key.
	 * 
	 * The Key need to correspond to the position of particle inside.
	 **/
	void SetKey(Key<DIM> & k);
	/**
	 * @brief Get the actual Key.
	 **/
	Key<DIM> GetKey() const;
	
	
	/**
	 * @brief Set The Neighbour of the container.
	 *
	 * Neighbour of the container are defined as particle container that are in a radius of h from the container
	 * it need to contain itself.
	 * @param list Voisin that contain all neighbour particles.
	 * @return void
	 **/
	void SetNeighbour(Voisin& list);
	/**
	 * @brief Get The Neighbour of the container.
	 *
	 * Neighbour of the container are defined as particle container that are in a radius of h from the container
	 * it need to contain itself.
	 * @return  Voisin that contain all neighbour particles.
	 **/
	Voisin GetNeighbour() const;
	/**
	 * @brief Get The Neighbour of the container.
	 *
	 * Neighbour of the container are defined as particle container that are in a radius of h from the container
	 * it need to contain itself.
	 * @param  vois that contain all neighbour particles.
	 **/
	void GetNeighbour(Voisin *& vois);
	
	/**
	 * @brief Add particle in the container.
	 **/
	void Add(Particle part);
	/**
	 * @brief Get The Neighbour of the container.
	 *
	 * Neighbour of the container are defined as particle container that are in a radius of h from the container
	 * it need to contain itself.
	 * @param  neigh that contain all neighbour particles.
	 **/
	inline void GetNeighbour(Voisin& neigh) const;
	
	/**
	 * @brief Update in wich container is the particle for every particle in container
	 *
	 * It will mark the container to be deleted if empty, but will not
	 * Remove Neighbour because a particle can enter before the particles is deleted.
	 * Entry of a particle in a Particles that is marked to be deleted cancel it.
	 * @param list map to all particles.
	 * @return void
	 **/
	void Update(  Particles_List*  list);
	//@}
	/**
	 * @name Conjugate Gradient
	 * 
	 * All this method are related to the calculus of conjugate gradient
	 * for incompressible sph
	 **/
	 //@{
	/**
	 * @brief Initialize conjugate gradient for the used in the incompressible algorithm.
	 **/
	 	
	void CorrectPosition();
	void Store0PosAndSpeed();
	void CorrectSpeed();
	double TestSpeedOK(bool &b);
	double TestPositionOK(bool &b);
	void PrepareSpeed();
	void PreparePos();
	void WritePressuresPos(fstream &out)const;
	void WriteDiv(fstream &out)const;
	void WritePressuresSpeed(fstream & out)const;
	void WriteNbItPos(fstream &out)const;
	void WriteNbItSpeed(fstream &out)const;
	void InitializeCG();
	/**
	 * @brief Partial calculate of Beta. For conjugate Gradient.
	 *
	 * @param num Numerator calculated for Beta.
	 * @param b True when converged.
	 * @param alpha Value of alpha to use for calculation.
	 **/
	void CalculateBetaPart(double &num,double alpha,bool &b);
	/**
	 * @brief Partial calculate of alpha. For conjugate Gradient.
	 *
	 * @param num partial calculation of numerator.
	 * @param denom partial calculate of denominator.
	 **/
	void CalculateAlphaPart(double &num,double &denom);
	/**
	 * @brief Calculated last step of conjugate gradient.
	 * @param beta Calculated value of beta.
	 **/
	void CalculateP1(double beta);
	//@}
	
	
	/** @name Command
	*  This are command that are transmitted to all container Particle. 
	*/
	//@{
	/**
	 * @brief Modify the mass to have a correct 0 density.
	 * And return the minimal mass found (minimal because mass at boundary are bigger).
	 * 
	 * @param m The function will modify and put the minimun between the input mass and the calculated one.
	 **/
	void Calculate0Density(double &m);

	/**
	 * @brief Set the mass of the particle Given by the global variable MEAN_MASS.
	 **/
	void SetToMeanMass();
	
	/**
	 * @brief Compute the pressure and density for all Particle in this container
	 *
	 * @return void
	 **/
	void ComputeDensity();


	/**
	 * @brief Make the initial move for the incompressible algorithm.
	 *
	 * @param dt Time step
	 * @return void
	 **/
	bool PreComputeMove(double dt);
	/**
	 * @brief Make Move all the particle in the  container.
	 *
	 * @param dt Time step
	 * @return void
	 **/
	void ComputeMove(double dt);
	
	/**
	 * @brief Compute the final timestep for Beeman
	 * 
	 * @param dt Time Step
	 **/
	void Beeman_compute(double dt);
	/**
	 * @brief Compute the half time step for Beeman methode for all particle in the container.
	 * 
	 * @param dt Time step
	 **/
	void Beeman_precompute(double dt);
	
	/**
	 * @brief make the Beeman_first time calculation using a euler method.
	 * 
	 * @param dt Time step
	 **/
	void Beeman_first_time(double dt);
	/**
	 * @brief Make the initial move for the predictor corrector.
	 *
	 * @param dt Time step
	 * @return void
	 **/
	void preComputeMove_predictor(double dt);
	/**
	 * @brief Correction step for the predictor corrector.
	 *
	 * @param dt Time step
	 * @param b True when not converged.
	 * @return void
	 **/
	void ComputeMove_predictor(double dt,bool &b);
	/**
	 * @brief Final step for the predictor corrector.
	 *
	 * @return void
	 **/
	void DoMove_predictor();
	/**
	 * @brief Write the position in a format for ParaView.
	 *
	 *  @param out Output stream to write.
	 **/
	void WritePos(fstream& out) const;
	/**
	 * @brief Write the density in a format for ParaView.
	 *
	 *  @param out Output stream to write.
	 **/
	void Density(fstream& out) const;
	/**
	 * @brief Write the Pressures in a format for ParaView.
	 *
	 *  @param out Output stream to write.
	 **/
	void Pressures(fstream& out) const;
	/**
	 * @brief Write the Nb_it in a format for ParaView.
	 *
	 *  @param out Output stream to write.
	 **/
	void NB_it(fstream& out) const;
	/**
	 * @brief Write the Mass in a format for ParaView.
	 *
	 *  @param out Output stream to write.
	 **/
	void Mass(fstream& out) const;
	/**
	 * @brief Write the MassDensity in a format for ParaView.
	 *
	 *  @param out Output stream to write.
	 **/
	void MassDensity(fstream& out) const;
	/**
	 * Calculate the timestep restriction that depend on the force.
	 **/
	void NextForceTimeStep(double &dt) const;
	/**
	 * Calculate the timestep restriction that depend on the current and viscosity.
	 **/
	void NextCourantVisciousTimeStep(double &dt) const;
	
	/**
	 * @brief Used on the incompressible algorithm To calculate the second member for the speed step.
	 * And to make a position correction.
	 **/
	void SetB_Speed();
	/**
	 * @brief Used on the incompressible algorithm To calculate the second member for the position step.
	 * And to make a speed correction.
	 *
	 * @param b True if not converged.
	 **/
	void PreparePosition(bool &b);
	/**
	 * @brief Calculate minus the Sub Grid Tensor.
	 **/
	void CalculateSubGridTens();


	void WriteSpeed(fstream & out) const;
	void WriteErf(fstream &out,double t) const;
	void WriteForce(fstream &out) const;
	void WriteForceGravity(fstream &out) const;
	void WriteForcePressure(fstream &out) const;
	void WriteForceViscosity(fstream &out) const;
	void WriteForceTurbulence(fstream &out) const;
	void UpdateForce() const;
	void WriteMussBeDeleted(fstream &out) const;

	//@}
	/**
	 * @brief Comparation operator.
	 **/
	//   bool operator==(const Particles& parts) const;

	
	
	/**
	 * @name Debug and Deprecated
	 * This list method that are normally not used
	 **/
	 //@{
	 /**
	 * @brief Used for Debuging, print information on screen.
	 **/
	void Dump(bool voisin=true);
	 
	 /**
	 * @deprecated
	 **/
	bool FindBoundary(bool b);
	 //@}
	};




	void Particles::GetNeighbour( Voisin &  neigh) const {
		neigh=m_neighbour;
	}

#endif // PARTICLES_H
