#ifndef PRESSURE_H
#define PRESSURE_H

#include <cmath>
#include <iostream>
#include "type.h"
using namespace std;
const double T=253.15+10;

const double TB=1408.4;

const double VB=4.1782E-5;

const double LAMBDA=0.3159;

const double ALPHA=2.145*VB;
const double BSTAR=1.0823*VB;
const double B1=0.02774;
const double B2=0.23578;
const double AVW=0.5542;
const double B=VB*(0.25*exp(1/(2.3*T/TB+0.5))-B1*exp(2.3*T/TB)+B2);
const double R=8.314472;
const double NA=5;
inline double pressure(double rho,ParticleType A){

 if(A==water){
     rho=rho/NA;
   double ret=rho*R*T*(1+rho*(-BSTAR-AVW/(R*T)+ALPHA/(1-LAMBDA*B*rho)));
   return ret;
 }else if(A==Gaz){
   return  4*rho;
 }

 return 0;
}

#endif //PRESSURE_H
