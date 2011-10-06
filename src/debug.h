#ifndef DEBUG_H
#define DEBUG_H
#include <list>
#include <iostream>
#include "particles.h"

using namespace std;
void  inline DumpNeighbour(list<Particles *> & a){
  for(list<Particles *>::iterator it=a.begin();it!=a.end();it++){
   (*it)->Dump(false); 
  }
}

void  inline GDump(list<Key<DIM> > & a){
  for(list<Key<DIM> >::iterator it=a.begin();it!=a.end();it++){
   it->Dump(); 
  }
}


#endif //DEBUG_H