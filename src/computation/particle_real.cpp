/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

	#include "particle_real.h"
#include "particle.h"
#include "debug.h"

void ParticleReal::SetContainerParticles(Particles *container){
m_container=container;
m_container->GetNeighbour(m_voisin);
}


