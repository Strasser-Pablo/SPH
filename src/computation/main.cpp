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

int main() {

	 /*World_test w;
	w.Do();*/
	 
	World_timing W;
	   W.Do();
	    
}
