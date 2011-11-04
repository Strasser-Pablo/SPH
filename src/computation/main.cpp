#include <iostream>
#include "world_test.h"
#include <fenv.h>
using namespace std;

     static void __attribute__ ((constructor))
     trapfpe ()
     {
       /* Enable some exceptions.  At startup all exceptions are masked.  */
     
       feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
     }
int main() {

	World_test w;
	w.Do();
}
