#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/key.h"
#include <algorithm>
double eps=1e-10;
class Test_Key : public CxxTest::TestSuite
{
public:
Test_Key(){
	srand ( time(NULL) );
}
void testCreation(void){
	Key<3> k;
	int x=rand();
	int y=rand();
	int z=rand();
	Key<3> k2(x,y,z);
	TS_ASSERT_EQUALS(k.GetX(),0);
	TS_ASSERT_EQUALS(k.GetY(),0);
	TS_ASSERT_EQUALS(k.GetZ(),0);
	TS_ASSERT_EQUALS(k2.GetX(),x);
	TS_ASSERT_EQUALS(k2.GetY(),y);
	TS_ASSERT_EQUALS(k2.GetZ(),z);
}

void testNeighbour(void){
	int x=rand();
	int y=rand();
	int z=rand();
	Key<3> k(x,y,z);
	 list<Key<3> > neigh=k.GetNeighbour();
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y-1,z-1))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y-1,z+0))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y-1,z+1))==1);
	 	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y+0,z-1))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y+0,z+0))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y+0,z+1))==1);
	  TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y+1,z-1))==1);
	   TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y+1,z+0))==1);
	    TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x-1,y+1,z+1))==1);
		
			 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y-1,z-1))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y-1,z+0))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y-1,z+1))==1);
	 	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y+0,z-1))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y+0,z+0))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y+0,z+1))==1);
	  TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y+1,z-1))==1);
	   TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y+1,z+0))==1);
	    TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+0,y+1,z+1))==1);
		
			 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y-1,z-1))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y-1,z+0))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y-1,z+1))==1);
	 	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y+0,z-1))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y+0,z+0))==1);
	 TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y+0,z+1))==1);
	  TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y+1,z-1))==1);
	   TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y+1,z+0))==1);
	    TS_ASSERT(count(neigh.begin(),neigh.end(),Key<3>(x+1,y+1,z+1))==1);
	 
}
void testLess(void){
	int x=rand();
	int y=rand();
	int z=rand();
	Key<3> k(x,y,z);
	TS_ASSERT(k<Key<3>(x+1,y,z));
	TS_ASSERT(k<Key<3>(x,y+1,z));
	TS_ASSERT(k<Key<3>(x,y,z+1));
	TS_ASSERT((Key<3>(x+1,y,z)<k)==false);
	TS_ASSERT((Key<3>(x,y+1,z)<k)==false);
	TS_ASSERT((Key<3>(x,y,z+1)<k)==false);
	TS_ASSERT((k<k)==false);
}
};