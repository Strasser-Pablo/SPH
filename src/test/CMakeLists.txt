cmake_minimum_required(VERSION 2.8)
project(test)

CXXTEST_ADD_TEST(test_cov_physvector test_physvector.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_physvector.h)
add_dependencies(check  computation test_cov_physvector)
