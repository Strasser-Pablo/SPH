/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/

#include "particle_real.h"
#include "particle.h"
#include "debug.h"
Particles ParticleReal::FindNeighbour(list< Particles* > Neighbour, double h)
{
 /* cout<<"begin dummmmmp"<<endl;
DumpNeighbour( Neighbour);
cout<<"end dummmmp"<<endl;
*/
  if(!Neighbour.empty()){
    Particles out;
for(list<Particles*>::iterator it=Neighbour.begin();it!=Neighbour.end();it++){
 for(list<Particle>::iterator it2=(*it)->begin();it2!=(*it)->end();it2++){
  if( Distance2(*it2)<pow(h,2)){
   out.push_back(*it2); 
  }
 }
  
}
/*
cout<<"begin dump out"<<endl;
out.Dump();
cout <<"end dump out"<<endl;
*/
//out.Dump();
return out;
}

 Particles temp;
 return temp;
}


