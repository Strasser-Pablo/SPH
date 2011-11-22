#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/voisin.h"
class Test_Key : public CxxTest::TestSuite
{
public:
Test_Key(){
	srand ( time(NULL) );
}
void testCreation(void){
	Voisin v;
	list<Particles*>listvois= v.GetParticlesVect();
	TS_ASSERT(listvois.Empty());
	
	list<Particles*>listvois2;
	Particles * P1=new Particles;
	Particles * P2=new Particles;
	listvois2.Push_back(P1);
	listvois2.Push_back(P2);
	Voisin v2(lisvois2);
	list<Particles*>listvoisres= v2.GetParticlesVect();
	Particles *Pres1=listvoisres.back();
	listvoisres.Pop_back();
	Particles *Pres2=listvoisres.back();
	TS_ASSERT_EQUALS(P1,Pres1);
	TS_ASSERT_EQUALS(P2,Pres2);
	TS_ASSERT(listvoisres.Empty());
}