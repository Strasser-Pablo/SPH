#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/kernel.h"
using namespace std;
double eps=1e-10;
#define testing
class Test_Particles : public CxxTest::TestSuite
{
public:
Test_Particles(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testUpdate(void){
	
}
};