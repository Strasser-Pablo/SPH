#ifndef WORLD_H
#define WORLD_H
#include "particles_list.h"
#include <deque>
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
	inline  void  Add(ParticleReal  part);
	~World();
};

#include "world.htt"

#endif
