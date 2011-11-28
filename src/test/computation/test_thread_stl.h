#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include <deque>
#include <cmath>
#include "test_thread_stl_h.h"
using namespace std;
double eps=1e-10;
#define testing
using namespace tbb;

class ApplyAdd2{
	deque<double> & mydeque;
	public:
	ApplyAdd2( deque<double> & vect):mydeque(vect){
	};
	void operator()( const blocked_range<size_t>& r ) const {
		for(size_t i=r.begin();i!=r.end();i++){
			mydeque[i]+=M_PI;
		}
		}
};

class ApplyAdd2red{
	deque<double> & mydeque;
	int nb_split;
	public:
	ApplyAdd2red( deque<double> & vect):mydeque(vect),nb_split(0){
	};
	ApplyAdd2red( ApplyAdd2red & B,split):mydeque(B.mydeque),nb_split(1){
	};
	void operator()( const blocked_range<size_t>& r ) const {
		for(size_t i=r.begin();i!=r.end();i++){
			mydeque[i]+=M_PI;
		}
		}
	void join(const ApplyAdd2red & B){
		nb_split=nb_split+B.nb_split;
	}
};

class Test_Thread_Stl : public CxxTest::TestSuite
{
public:
Test_Thread_Stl(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testConcurentDequeRead(void){
		#pragma GCC diagnostic ignored "-Wconversion"
	deque<double> mydeque(200);
	for(size_t i=0;i<mydeque.size();++i){
	mydeque[i]=M_PI*i;
		
}
parallel_for(blocked_range<size_t>(0,mydeque.size()), ApplyAdd2(mydeque));	
for(size_t i=0;i<mydeque.size();++i){
	TS_ASSERT_DELTA((i+1)*M_PI,mydeque[i],eps);
}
	#pragma GCC diagnostic pop
}
void testConcurentDequeRead2(void){
		#pragma GCC diagnostic ignored "-Wconversion"
		deque<double> mydeque(200);
	for(size_t i=0;i<mydeque.size();++i){
	mydeque[i]=M_PI*i;
}
ApplyAdd2red add(mydeque);
parallel_for(blocked_range<size_t>(0,mydeque.size()), add);	
for(size_t i=0;i<mydeque.size();++i){
	TS_ASSERT_DELTA((i+1)*M_PI,mydeque[i],eps);
}
	#pragma GCC diagnostic pop
}
};