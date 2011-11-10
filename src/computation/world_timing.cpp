#include "world_timing.h"
#include <sys/times.h>
#include <fstream>
using namespace std;
/**
* \file World_timing.cpp Implementation file for World_test.
**/


World_timing::World_timing()
{

}

void World_timing::Do()
{
	fstream out ("timing.csv", fstream::out);
	for(int N=1;N<20;N++){
		
int Nx=N;
int Ny=N;
int Nz=N;
out<<N<<" ";
for(int es=0;es<3;es++){
	struct tms ti;
times(&ti);	
for(int j=0;j<Ny;j++){
for(int i=0;i<Nx;i++){
	
		for(int k=0;k<Nz;k++){
			Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0,0,0),water));
}
}
}



m_list.Calculate0Density();
for(int i=0;i<20;i++){
	  double dt;
 m_list.Compute(dt);
  m_list.write(dt);
}
struct tms tf;
times(&tf);
double nb=double(sysconf(_SC_CLK_TCK));
out<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	}
	out<<endl;
	}
}
