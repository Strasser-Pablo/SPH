#ifndef PRESSURE_H
#define PRESSURE_H

#include <cmath>
#include <iostream>
#include "type.h"
#include "const.h"
using namespace std;





const double rho0=1000;
const double sound_speed=500;
const double B=pow(sound_speed,2)*rho0/7.;
inline double pressure(double rho,ParticleType A) {

	if(A==water) {
	//	rho=rho/NA;
	//	double ret=rho*R*T*(1+rho*(-BSTAR-AVW/(R*T)+ALPHA/(1-LAMBDA*B*rho)));
	//	return ret;
	return B*(pow(rho/rho0,7)-1);
	} else if(A==Gaz) {
		return  4*rho;
	}

	return 0;
}

#endif //PRESSURE_H
