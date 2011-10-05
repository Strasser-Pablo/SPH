/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/
/** \file particles.cpp
 * @brief Implementation file for particles.
 *
 */


#include "particles.h"
#include "particle.h"
using namespace std;
Particles::Particles(ParticleType type): list<Particle>(),m_type(type)
{

}

Particles::Particles(const Particles& A):m_type(A.m_type),list<Particle>(A) {

}

Particles::Particles():m_type(none)
{

}


void Particles::ComputePressure_Density()
{
    Particles list_compute;
    for (list<Particle>::iterator it=begin();it!=end();it++) {
        list_compute=(*it)->FindNeighbour(m_neighbour,h);
        for (Particles::iterator it2=list_compute.begin();it2!=list_compute.end();it2++) {
            (*it2)->ComputePressure_Density(list_compute);
        }
    }
}


void Particles::ComputeInternal_Force()
{
    Particles list_compute;
    for (list<Particle>::iterator it=begin();it!=end();it++) {
        list_compute=(*it)->FindNeighbour(m_neighbour,h);
        for (Particles::iterator it2=list_compute.begin();it2!=list_compute.end();it2++) {
            (*it2)->ComputeInternal_Force(list_compute);
        }
    }
}

void Particles::ComputeGravity_Force()
{
for(list<Particle>::iterator it=begin();it!=end();it++){
 (*it)->ComputeGravity_Force(); 
}
}


void Particles::SetNeighbour(list< Particles > list )
{
    m_neighbour=list;
}




