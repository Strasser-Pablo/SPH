/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test_physvector.h"

static Test_Physvector suite_Test_Physvector;

static CxxTest::List Tests_Test_Physvector = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Test_Physvector( "test_physvector.h", 6, "Test_Physvector", suite_Test_Physvector, Tests_Test_Physvector );

static class TestDescription_Test_Physvector_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_Test_Physvector_testAddition() : CxxTest::RealTestDescription( Tests_Test_Physvector, suiteDescription_Test_Physvector, 12, "testAddition" ) {}
 void runTest() { suite_Test_Physvector.testAddition(); }
} testDescription_Test_Physvector_testAddition;

#include <cxxtest/Root.cpp>
