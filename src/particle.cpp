/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#include "particle.h"

Particles Particle::FindNeighbour(list< Particles > Neighbour, double h)
{
  if(!Neighbour.empty()){
    Particles out(*Neighbour.begin());
for(list<Particles>::iterator it=Neighbour.begin();it!=Neighbour.end();it++){
 for(list<Particle>::iterator it2=it->begin();it2!=it->end();it2++){
  if( Distance2(*it2)<h){
   out.push_back(*it2); 
  }
 }
  
}
return out;
}
 Particles temp;
 return temp;
}


