#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/physvector.h"
double eps=1e-10;
class Test_Physvector : public CxxTest::TestSuite
{
public:
Test_Physvector(){
	srand ( time(NULL) );
}
void testAddition( void )
{
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	physvector<3> v(x,y,z);
	physvector<3> v2(x2,y2,z2);
	physvector<3> v3=v+v2;
	double xres;
	double yres;
	double zres;
	v3.Get(xres,yres,zres);
TS_ASSERT_DELTA( x+x2,xres,eps );
TS_ASSERT_DELTA( y+y2,yres,eps );
TS_ASSERT_DELTA( z+z2,zres,eps );
}
void testAddition_Equal( void )
{
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	physvector<3> v(x,y,z);
	physvector<3> v2(x2,y2,z2);
	v+=v2;
	double xres;
	double yres;
	double zres;
	v.Get(xres,yres,zres);
TS_ASSERT_DELTA( x+=x2,xres,eps );
TS_ASSERT_DELTA( y+=y2,yres,eps );
TS_ASSERT_DELTA( z+=z2,zres,eps );
}
void testSoustraction_Equal( void )
{
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	physvector<3> v(x,y,z);
	physvector<3> v2(x2,y2,z2);
	v-=v2;
	double xres;
	double yres;
	double zres;
	v.Get(xres,yres,zres);
TS_ASSERT_DELTA( x-=x2,xres,eps );
TS_ASSERT_DELTA( y-=y2,yres,eps );
TS_ASSERT_DELTA( z-=z2,zres,eps );
}
void testSoustraction( void )
{
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	physvector<3> v(x,y,z);
	physvector<3> v2(x2,y2,z2);
	physvector<3> v3=v-v2;
	double xres;
	double yres;
	double zres;
	v3.Get(xres,yres,zres);
TS_ASSERT_DELTA( x-x2,xres,eps );
TS_ASSERT_DELTA( y-y2,yres,eps );
TS_ASSERT_DELTA( z-z2,zres,eps );
}
void testCreation(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	double xres;
	double yres;
	double zres;
	v.Get(xres,yres,zres);
	TS_ASSERT_DELTA( x,xres,eps );
	TS_ASSERT_DELTA( y,yres,eps );
	TS_ASSERT_DELTA( z,zres,eps );
}
void testEqual(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	double x2=x;
	double y2=y;
	double z2=z;
	physvector<3>v2(x2,y2,z2);
TS_ASSERT_EQUALS(v,v2);	
physvector<3>v3(x2+1,y2,z2);
TS_ASSERT_DIFFERS(v,v3);	
physvector<3>v4(x2,y2+1,z2);
TS_ASSERT_DIFFERS(v,v4);	
physvector<3>v5(x2,y2,z2+1);
TS_ASSERT_DIFFERS(v,v5);	
}
};
