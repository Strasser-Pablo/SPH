/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/
/** \file particles.cpp
 * @brief Implementation file for particles.
 *
 */


#include "particles.h"
#include "particle.h"
#include "particles_list.h"
#include "debug.h"
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
    for (list<Particle>::iterator it=begin();it!=end();it++) {
        (*it)->ComputeGravity_Force();
    }
}


void Particles::SetNeighbour(list< Particles *> list )
{
    m_neighbour=list;
}

list<Particles*> Particles::GetNeighbour(){
  return m_neighbour;
}


void Particles::ComputeMove(double dt)
{
    for (list<Particle>::iterator it=begin();it!=end();it++) {
        (*it)->ComputeMove( dt);
    }
}

void Particles::Update( Particles_List*  plist)
{
  list<Particle>::iterator it=begin();
    while (it!=end()) {
      //iterator effectly used
      list<Particle>::iterator it2=it;
      //we increase the iterator before that we splice to don't have problem when it2 is invalided
      it++;
      plist->Update(it2,this);
	}
    
}

bool Particles::operator==(const Particles parts) const
{
return this==&parts;
}


void Particles::Dump(bool voisin)
{
  cout<<"begin Particles"<<endl;
for(Particles::iterator it=begin();it!=end();it++){
 (*it)->Dump(); 
}
if(voisin){
cout<<"dump of neighbour"<<endl;
DumpNeighbour(m_neighbour);
cout<<"end dump of neighbour"<<endl;
}
cout<<"end Particles"<<endl;
}

