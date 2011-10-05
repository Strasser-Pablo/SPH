/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#ifndef PARTICLES_H
#define PARTICLES_H
#include <list>
#include "type.h"
#include "const.h"
class Particle;
using namespace std;
/**
* @brief Represent a list of Particle, inherit from std::list.
*
**/

class Particles: public list<Particle>
{
    ParticleType m_type;
    list<Particles> m_neighbour;
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
    void ComputePressure_Density();
    void SetNeighbour(list<Particles> list);
};

#endif // PARTICLES_H
