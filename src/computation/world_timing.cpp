#include "world_timing.h"
#include <sys/times.h>
#include <fstream>
using namespace std;
/**
* \file world_timing.cpp Implementation file for World_test.
**/

World_timing::World_timing()
{

}

World_timing_elem::World_timing_elem()
{

}
void World_timing::Do()
{

	fstream out ("../timing.csv", fstream::out);
	for(int N=5;N<50;N+=5){
		out<<N<<" ";
	World_timing_elem W;
	W.Do(N,out);
out<<endl;
	}

}
	
void World_timing_elem::Do(int N,fstream & out)
{
	
		
int Nx=N;
int Ny=N;
int Nz=N;

	
for(int j=0;j<Ny;j++){
for(int i=0;i<Nx;i++){
	
		for(int k=0;k<Nz;k++){
			Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0,0,0),water));
}
}
}

m_list.Calculate0Density();
m_list.write(0.00);
struct tms ti;
times(&ti);
for(int i=0;i<1;++i){
	  double dt;
 m_list.Compute(dt);
  m_list.write(dt);
}
struct tms tf;
times(&tf);
double nb=double(sysconf(_SC_CLK_TCK));
#pragma GCC diagnostic ignored "-Wconversion"
out<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
#pragma GCC diagnostic pop
	}
	
	

