#include <iostream>
#include "world_test.h"
#include "world_timing.h"
#include <fenv.h>

using namespace std;
using namespace tbb;
/**
 * Trap that signal when nan and infinity occure.
 * Usefull for debuguing.
 **/
     static void __attribute__ ((constructor))
     trapfpe ()
     {
       feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
     }
int myfunc(physvector<3>& v,physvector<3>& v2){
	return (v2-v).Norm();
}
int main() {

	/*World_test w;
	w.Do();*/
	World_timing W;
	 W.Do();
	  
	/*  
	  double x=3;
	  double y=6;
	  double z=10;
	  physvector<3> v(x,y,z);
	  physvector<3> v2(y,x,z);
	return myfunc(v,v2);
	  */
}
