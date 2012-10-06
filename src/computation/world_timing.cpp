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
			//	part->SetBoundary(true);
			}
			else{
				Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0,i+k,0),water));
			}
			}
		}

	}
	 */
	

int Nx=4;
	int Ny=2;
	int Nz=4;
	double uy=1.0;
	double r0=0.05;
	for(int j=0; j<Ny; j++) {
		for(int i=0; i<Nx; i++) {

			for(int k=0; k<Nz; k++) {
				double x=i*h/3-Nx/2.*h/3+h/12;
				double y=k*h/3-Nz/2.*h/3+h/12;
				double r2=pow(x,2)+pow(y,2);
				if(r2>pow(r0,2)) {
					continue;
				}
				double Uyrel=uy/pow(r0,2)*(pow(r0,2)-r2);
				Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0, Uyrel,0),water));
			}
		}
	}
//cout<<"bo

/*for(int j=0;j<2;j++){
for(int i=0;i<2;i++){
	for(int k=0;k<2;k++){
		/*if(i==0&&j==0&&k==0){
			Particle part;
Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(3,10,0),water),part);
part->SetBoundary(true);
		}
		else{
Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(3*k,10*i,0),water));
//}
}
}
}*/
	m_list.Calculate0Density();
	//OutputMatrix();
	m_list.write(0.00);
	//Part->SetPos(physvector<3>(0,-h/12,0));
	//ProfilerFlush();
	struct tms ti;
	long deb=times(&ti);
while(true){
		double dt;
		m_list.Compute(dt);
		m_list.write(dt);
		//ProfilerFlush();
	}
	struct tms tf;
	long end=times(&tf);
	double nb=double(sysconf(_SC_CLK_TCK));
	#pragma GCC diagnostic ignored "-Wconversion"
	out<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	#pragma GCC diagnostic pop
}



