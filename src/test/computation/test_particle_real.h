#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/particle_real.h"
double eps=1e-10;
class Test_Particle_Real : public CxxTest::TestSuite
{
public:
Test_Particle_Real(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testCreation(void){
	ParticleReal pr1;
	physvector<3> v0;
	TS_ASSERT_EQUALS(pr1.GetPos(),v0);
	TS_ASSERT_EQUALS(pr1.GetSpeed(),v0);
	TS_ASSERT_EQUALS(pr1.GetMass(),1);
	ParticleReal pr2;
	TS_ASSERT_EQUALS(pr1,pr2);
	TS_ASSERT(pr1.Equal(Particle(&pr2)));
    double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	ParticleReal Pr3(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	ParticleReal Pr4(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	
	physvector<3> vpos(x,y,z);
	physvector<3> vspeed(x2,y2,z2);
	
	TS_ASSERT_EQUALS(Pr3.GetPos(),vpos);
	TS_ASSERT_EQUALS(Pr3.GetSpeed(),vspeed);
	TS_ASSERT_EQUALS(Pr3.GetMass(),1);
	TS_ASSERT_EQUALS(Pr3,Pr4);
	TS_ASSERT(Pr3.Equal(Particle(&Pr4)))
	 x=rand()/1000.;
	 y=rand()/1000.;
	 z=rand()/1000.;
	 
	ParticleReal pr4(physvector< 3  >(x,y,z),water);
	 vpos=physvector< 3  >(x,y,z);
	 vspeed=physvector< 3  >(0,0,0);
	
	TS_ASSERT_EQUALS(pr4.GetPos(),vpos);
	TS_ASSERT_EQUALS(pr4.GetSpeed(),vspeed);
	TS_ASSERT_EQUALS(pr4.GetMass(),1);
}
void testMass(void){
	ParticleReal pr1;
	 double m=rand()/1000.;
	pr1.SetM(m);
	double mres=pr1.GetMass();
	TS_ASSERT_DELTA(mres,m,eps);
}
//only if incompressible
void xtestBoundary(void){
	/*
   ParticleReal pr1;
   pr1.SetBoundary(true);
   TS_ASSERT_EQUALS(true,pr1.GetBoundary());
   pr1.SetBoundary(false);
   TS_ASSERT_EQUALS(false,pr1.GetBoundary());
    */
}
void testSetDensity(void){
	ParticleReal pr1;
	double dens=rand()/1000.;
   pr1.SetDensity(dens);
   TS_ASSERT_EQUALS(pr1.GetDensity(),dens);
   double m=rand()/1000.;
	pr1.SetM(m);
	TS_ASSERT_EQUALS(pr1.GetMassDensity(),dens*m);
}

void testPressure(void){
	ParticleReal pr1;
	double dens=rand()/1000.;
   pr1.SetDensity(dens);
   double m=rand()/1000.;
	pr1.SetM(m);
	TS_ASSERT_EQUALS(pr1.GetPressure(),pressure(dens*m,water));
}
void testSetPos(void){
	ParticleReal pr1;
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3> pos(x,y,z);
	pr1.SetPos(pos);
	TS_ASSERT_EQUALS(pr1.GetPos(),pos);
}
void testSetSpeed(void){
	ParticleReal pr1;
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3> speed(x,y,z);
	pr1.SetSpeed(speed);
	TS_ASSERT_EQUALS(pr1.GetSpeed(),speed);	
}
void testDistance(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	double x3=rand()/1000.;
	double y3=rand()/1000.;
	double z3=rand()/1000.;
	double x4=rand()/1000.;
	double y4=rand()/1000.;
	double z4=rand()/1000.;
	ParticleReal Pr1(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	ParticleReal *Pr2=new ParticleReal(physvector< 3  >(x3,y3,z3),physvector< 3  >(x4,y4,z4),water);
	Particle Pa2(Pr2);
	TS_ASSERT_DELTA(Pr1.Distance(Pa2),physvector<3>(x,y,z).Distance(physvector<3>(x3,y3,z3)),eps);
    TS_ASSERT_DELTA(Pr1.Distance2(Pa2),physvector<3>(x,y,z).Distance2(physvector<3>(x3,y3,z3)),eps);
	delete Pr2;
}
void testComputeDensity(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	double x3=rand()/1000.;
	double y3=rand()/1000.;
	double z3=rand()/1000.;
	double x4=rand()/1000.;
	double y4=rand()/1000.;
	double z4=rand()/1000.;
	ParticleReal *Pr1=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	ParticleReal *Pr2=new ParticleReal(physvector< 3  >(x3,y3,z3),physvector< 3  >(x4,y4,z4),water);
	Particles part;
	part.push_back(Particle(Pr1));
	part.push_back(Particle(Pr2));
	list<Particles*> partlist;
	partlist.push_back(&part);
	Voisin vois(partlist);
	part.SetNeighbour(vois);
	Pr1->SetContainerParticles(&part);
	Pr1->ComputeDensity();
	physvector<3> v1(x,y,z);
	physvector<3> v2(x3,y3,z3);
	
	double dens=Kernel_spline5(v2-v1,h)+Kernel_spline5(v1-v1,h);
	TS_ASSERT_DELTA(Pr1->GetDensity(),dens,eps);
	delete Pr1;
	delete Pr2;
}

void testCompute0Dens(void){
	double dens0=rand()/1000.;
	ParticleReal part;
	part.SetDensity(dens0);
	double m;
	part.Calculate0Density(m);
	TS_ASSERT_DELTA(part.GetMassDensity(),1000,eps);
	part.SetDensity(3*dens0);
	part.Calculate0Density(m);
	TS_ASSERT_DELTA(part.GetMassDensity(),1000,eps);
}
void testMoveComputation(void){
	double x=(rand()%10)/1000.;
	double y=(rand()%10)/1000.;
	double z=(rand()%10)/1000.;
	double x2=(rand()%10)/1000.;
	double y2=(rand()%10)/1000.;
	double z2=(rand()%10)/1000.;
	double x3=(rand()%10)/1000.;
	double y3=(rand()%10)/1000.;
	double z3=(rand()%10)/1000.;
	double x4=(rand()%10)/1000.;
	double y4=(rand()%10)/1000.;
	double z4=(rand()%10)/1000.;
	ParticleReal *PrA1=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	ParticleReal *PrA2=new ParticleReal(physvector< 3  >(x3,y3,z3),physvector< 3  >(x4,y4,z4),water);
	Particles partA;
	partA.push_back(Particle(PrA1));
	partA.push_back(Particle(PrA2));
	list<Particles*> partlistA;
	partlistA.push_back(&partA);
	Voisin voisA(partlistA);
	partA.SetNeighbour(voisA);
	PrA1->SetContainerParticles(&partA);
	PrA2->SetContainerParticles(&partA);
	
	ParticleReal *PrB1=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	ParticleReal *PrB2=new ParticleReal(physvector< 3  >(x3,y3,z3),physvector< 3  >(x4,y4,z4),water);
	Particles partB;
	partB.push_back(Particle(PrB1));
	partB.push_back(Particle(PrB2));
	list<Particles*> partlistB;
	partlistB.push_back(&partB);
	Voisin voisB(partlistB);
	partB.SetNeighbour(voisB);
	PrB1->SetContainerParticles(&partB);
	PrB2->SetContainerParticles(&partB);
	partA.ComputeDensity();
	double m;
	partA.Calculate0Density(m);
	partB.ComputeDensity();
	partB.Calculate0Density(m);
	double dt=0.0001;
	partA.UpdateForce();
	partB.UpdateForce();
	for(int i=0;i<10;i++){
	
		partA.ComputeDensity();
		partB.ComputeDensity();
		partB.UpdateForce();
		bool b=true;
			partA.preComputeMove_predictor(dt);
while(b){
	b=false;
	partA.ComputeDensity();
	partA.UpdateForce();
	partA.ComputeMove_predictor(dt,b);
}
		partA.DoMove_predictor();
	if(i==0){
		partB.Beeman_first_time(dt);
	}
	else{
		partB.Beeman_precompute(dt);
		partA.ComputeDensity();
	    partA.UpdateForce();
		partB.Beeman_compute(dt);
	}
	}
	physvector<3> veps(dt,dt,dt);
	TS_ASSERT_DELTA(PrA1->GetPos(),PrB1->GetPos(),veps);
	TS_ASSERT_DELTA(PrA2->GetPos(),PrB2->GetPos(),veps);
	TS_ASSERT_DELTA(PrA1->GetSpeed(),PrB1->GetSpeed(),veps);
	TS_ASSERT_DELTA(PrA2->GetSpeed(),PrB2->GetSpeed(),veps);
	delete PrA1;
	delete PrA2;
	delete PrB1;
	delete PrB2;
}
};