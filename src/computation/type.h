
#ifndef TYPE_H
#define TYPE_H
/**
 * @brief Type of particle
 */
enum ParticleType{none,water,Gaz,Fixed};

/**
 * @brief Class Containing constant for Material
 */
struct MatterConstant{
 double rho0;
 double k;
 double eta;
};

extern MatterConstant WaterConst;

inline MatterConstant Mat_Const(ParticleType type){
 switch(type){
   case water:
     return WaterConst;
 }
}

inline double surface_Const(ParticleType A,ParticleType B){
 ParticleType a;
 ParticleType b;
 if(A<B){
  a=A;b=B; 
 }else{
  a=B;b=A; 
 }
 if(a==water&&b==Gaz){
   return 1.0;
 }
 return 0.0;
}



/**
 * @brief Function to initialize constant for Material
 */

#endif // CONST_H
