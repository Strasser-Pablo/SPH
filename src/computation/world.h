#ifndef WORLD_H
	#define WORLD_H
#include "particles_list.h"
#include <deque>
#include <map>
	using namespace std;
	/**
	 * \file world.h
	 * @brief Contain Header for class World
	 **/
	/**
	 * @brief This class is used to add particle to the system.
	 *
	 */
	class World {
protected:
	deque<ParticleReal> m_particle_real_list;
	Particles_List m_list;
public:
	/**
	 * @brief Create a World object
	 *
	 **/
	World();
	/**
	 * @brief Add a real particle in the world. The particle will be copied so it can be deleted after.
	 *
	 * @param part Real Particle to add.
	 * @return void
	 **/
	inline void  Add(ParticleReal part);
	/**
	 * @brief Add a real particle in the world. The particle will be copied so it can be deleted after.
	 *
	 * @param part Real Particle to add.
	 * @param partic Return a particle wich point to the ParticleReal.
	 * @return void
	 **/
	inline void  Add(ParticleReal part,Particle & partic);
	#ifdef PRESSURE_LAPLACIEN
	 void OutputMatrix();
	 void SolveMatrix();
private:
	 inline physvector<DIM> DivFactor(ParticleReal& i,ParticleReal& j);
	 inline physvector<DIM> GradFactor(ParticleReal& i,ParticleReal& j);
	 void CreateMatLink();
	 inline double Matrice(int i,int j);
	 map<Voisin*,Voisin> m_mat_link;
	 map<ParticleReal*,int> m_part_to_int;
	 public:
	 #endif
	~World();
	};

#include "world.htt"

#endif
