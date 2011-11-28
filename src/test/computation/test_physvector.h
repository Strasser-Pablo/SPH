#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/physvector.h"
double eps=1e-10;
class Test_Physvector : public CxxTest::TestSuite
{
public:
Test_Physvector(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
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
void testDistance(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	double x2=x;
	double y2=y;
	double z2=z;
	physvector<3>v2(x2,y2,z2);
	double d=v.Distance(v2);
TS_ASSERT_DELTA(sqrt(pow(x-x2,2)+pow(y-y2,2)+pow(z-z2,2)),d,eps);
}
void testDistance2(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	double x2=x;
	double y2=y;
	double z2=z;
	physvector<3>v2(x2,y2,z2);
	double d=v.Distance2(v2);
TS_ASSERT_DELTA(pow(x-x2,2)+pow(y-y2,2)+pow(z-z2,2),d,eps);
}
void testNorm(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	double d=v.Norm();
TS_ASSERT_DELTA(sqrt(pow(x,2)+pow(y,2)+pow(z,2)),d,eps);
}

void testNorm2(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	double d=v.Norm2();
TS_ASSERT_DELTA(pow(x,2)+pow(y,2)+pow(z,2),d,eps);
}

void testSetUnset(void){
	physvector<3>v;
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	v.Set(x,y,z);
	double x2;
	double y2;
	double z2;
	v.Get(x2,y2,z2);
	TS_ASSERT_EQUALS(x,x2);
	TS_ASSERT_EQUALS(y,y2);
	TS_ASSERT_EQUALS(z,z2);
}

void testUnaryMinus(void){
	
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v=-physvector<3>(x,y,z);
	double x2;
	double y2;
	double z2;
	v.Get(x2,y2,z2);
	TS_ASSERT_DELTA(x,-x2,eps);
	TS_ASSERT_DELTA(y,-y2,eps);
	TS_ASSERT_DELTA(z,-z2,eps);
}
void testAssignement(void){
	
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	physvector<3> v2;
	v2=v;
	double x2;
	double y2;
	double z2;
	v2.Get(x2,y2,z2);
	TS_ASSERT_EQUALS(x,x2);
	TS_ASSERT_EQUALS(y,y2);
	TS_ASSERT_EQUALS(z,z2);
}
void testMultConst(void){
	
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double c=rand()/1000.;
	physvector<3>v=physvector<3>(x,y,z)*c;
	physvector<3>v2=c*physvector<3>(x,y,z);
	double x2;
	double y2;
	double z2;
	v.Get(x2,y2,z2);
	double x3;
	double y3;
	double z3;
	v2.Get(x3,y3,z3);
	TS_ASSERT_DELTA(c*x,x2,eps);
	TS_ASSERT_DELTA(c*y,y2,eps);
	TS_ASSERT_DELTA(c*z,z2,eps);
	TS_ASSERT_DELTA(c*x,x3,eps);
	TS_ASSERT_DELTA(c*y,y3,eps);
	TS_ASSERT_DELTA(c*z,z3,eps);
}
void testMult(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	double s=physvector<3>(x,y,z)*physvector<3>(x2,y2,z2);
	TS_ASSERT_DELTA(x*x2+y*y2+z*z2,s,eps);
}
void testMultConstEgal(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double c=rand()/1000.;
	double x2;
	double y2;
	double z2;
	physvector<3> v(x,y,z);
	v*=c;
	v.Get(x2,y2,z2);
	TS_ASSERT_DELTA(x*c,x2,eps);
	TS_ASSERT_DELTA(y*c,y2,eps);
	TS_ASSERT_DELTA(z*c,z2,eps);
}
void testDivConst(void){
	
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double c=rand()/1000.;
	physvector<3>v=physvector<3>(x,y,z)/c;
	double x2;
	double y2;
	double z2;
	v.Get(x2,y2,z2);
	TS_ASSERT_DELTA(x/c,x2,eps);
	TS_ASSERT_DELTA(y/c,y2,eps);
	TS_ASSERT_DELTA(z/c,z2,eps);
}
void testMultElem(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	physvector<3>v2(x2,y2,z2);
	physvector<3>v=physvector<3>(x,y,z).prod(v2);
	double xres;
	double yres;
	double zres;
	v.Get(xres,yres,zres);
	TS_ASSERT_DELTA(x*x2,xres,eps);
	TS_ASSERT_DELTA(y*y2,yres,eps);
	TS_ASSERT_DELTA(z*z2,zres,eps);
}

void testSmaller(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	physvector<3>v2(x,y,z+1);
	physvector<3>v3(x,y+1,z);
	physvector<3>v4(x+1,y,z);
	TS_ASSERT((v<v)==false)
	TS_ASSERT(v<v2)
	TS_ASSERT(v<v3)
	TS_ASSERT(v<v4)
	TS_ASSERT((v2<v)==false)
	TS_ASSERT((v3<v)==false)
	TS_ASSERT((v4<v)==false)
}
void testTo0(void){
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	physvector<3>v(x,y,z);
	v.To0();
	double x2;
	double y2;
	double z2;
	v.Get(x2,y2,z2);
	TS_ASSERT_EQUALS(0,x2);
	TS_ASSERT_EQUALS(0,y2);
	TS_ASSERT_EQUALS(0,z2);
}
void testIsNull(void){

	physvector<3>v(0,0,0);
	physvector<3>v2(1,1,1);
	TS_ASSERT(v.IsNull());
	TS_ASSERT(v2.IsNull()==false);
}
void testToKey(void){
	physvector<3>v(1,1,1);
	Key<3> k= v.ToKey(1.0);
	Key<3> k2= v.ToKey(0.6);
	physvector<3>v2(0.5,0.5,0.5);
	Key<3> k3= v2.ToKey(2);
	TS_ASSERT_EQUALS(k.GetX(),1);
	TS_ASSERT_EQUALS(k.GetY(),1);
	TS_ASSERT_EQUALS(k.GetZ(),1);
	TS_ASSERT_EQUALS(k2.GetX(),1);
	TS_ASSERT_EQUALS(k2.GetY(),1);
	TS_ASSERT_EQUALS(k2.GetZ(),1);
	TS_ASSERT_EQUALS(k3.GetX(),0);
	TS_ASSERT_EQUALS(k3.GetY(),0);
	TS_ASSERT_EQUALS(k3.GetZ(),0);
}
};
