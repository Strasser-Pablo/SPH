#include "world_timing.h"
#include <sys/times.h>
#include <fstream>
#include <google/profiler.h>
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
	//ProfilerStart("profile.prof");
	fstream out ("../timing.csv", fstream::out);
	for(int N=2; N<3; N+=5) {
		out<<N<<" ";
		World_timing_elem W;
		W.Do(N,out);
		out<<endl;
	}
	//ProfilerStop();
}

void World_timing_elem::Do(int N,fstream & out)
{

/*
	int Nx=N;
	int Ny=N;
	int Nz=N;


	for(int j=0; j<Ny; j++) {
		for(int i=0; i<Nx; i++) {

			for(int k=0; k<Nz; k++) {
				if(k==0&&i==0&&j==0){
					Particle part;
				Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0,i+k,0),water),part);
				part->SetBoundary(true);
			}
			else{
				Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0,i+k,0),water));
			}
			}
		}

	}
	 */

Particle part;
Add(ParticleReal(physvector< 3  >(0,0,0),physvector< 3  >(1,0,0),water),part);
				part->SetBoundary(true);
				Particle part2;
Add(ParticleReal(physvector< 3  >(0,h/3,0),physvector< 3  >(-1,0,0),water),part2);
			
	m_list.Calculate0Density();
	m_list.write(0.00);
	ProfilerFlush();
	struct tms ti;
	long deb=times(&ti);
	for(int i=0; i<500; ++i) {
		double dt;
		m_list.Compute(dt);
		m_list.write(dt);
		ProfilerFlush();
	}
	struct tms tf;
	long end=times(&tf);
	double nb=double(sysconf(_SC_CLK_TCK));
	#pragma GCC diagnostic ignored "-Wconversion"
	out<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	#pragma GCC diagnostic pop
}



