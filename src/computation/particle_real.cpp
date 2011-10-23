/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#include "particle_real.h"
#include "particle.h"
#include "debug.h"
void ParticleReal::FindNeighbour(list< Particles* > Neighbour, double h,Particles& Find)
{
 /* cout<<"begin dummmmmp"<<endl;
DumpNeighbour( Neighbour);
cout<<"end dummmmp"<<endl;
*/
    Find.clear();

for(list<Particles*>::iterator it=Neighbour.begin();it!=Neighbour.end();++it){
 for(list<Particle>::iterator it2=(*it)->begin();it2!=(*it)->end();++it2){
  if( Distance2(*it2)<pow(h,2)){
   Find.push_back(*it2);
  }
 }

}

if(m_container->GetBoundary().HasBoundary()){
Boundaries<DIM> bound=m_container->GetBoundary();
cout<<"has boundary"<<endl;
}
}


void ParticleReal::SetContainerParticles(Particles *container){
m_container=container;
}

void ParticleReal::UpdateVoisin(){
    list<Particles *> neigh;
    m_container->GetNeighbour(neigh);
FindNeighbour(neigh,h,m_voisin);
}
