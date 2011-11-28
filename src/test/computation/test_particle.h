#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/particle.h"
#include <algorithm>
double eps=1e-10;
class Test_Particle : public CxxTest::TestSuite
{
public:
Test_Particle(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testCreation(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	ParticleReal* Pr1=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	Particle Pa1(Pr1);
	TS_ASSERT_EQUALS(Pa1.Get(),Pr1);
	TS_ASSERT_EQUALS(*Pa1,*Pr1);
	TS_ASSERT_EQUALS(Pa1->GetPos(),Pr1->GetPos());
	Particle Pa2;
	ParticleReal* Pnull=0;
	TS_ASSERT_EQUALS(Pa2.Get(),Pnull);
	delete Pr1;
}
};