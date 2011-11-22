cmake_minimum_required(VERSION 2.8)
project(test)
CXXTEST_ADD_TEST(test_cov_physvector test_physvector.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_physvector.h)
set_target_properties(test_cov_physvector PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_key test_key.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_key.h)
set_target_properties(test_cov_key PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")

CXXTEST_ADD_TEST(test_cov_voisin test_voisin.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_voisin.h)
set_target_properties(test_cov_voisin PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")


add_dependencies(check  computation test_cov_physvector test_cov_key test_cov_voisin)
