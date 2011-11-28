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
target_link_libraries(test_cov_voisin computation_lib)

CXXTEST_ADD_TEST(test_cov_particle test_particle.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_particle.h)

set_target_properties(test_cov_particle PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
target_link_libraries(test_cov_particle computation_lib)

CXXTEST_ADD_TEST(test_cov_particle_real test_particle_real.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_particle_real.h)

set_target_properties(test_cov_particle_real PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
target_link_libraries(test_cov_particle_real computation_lib)


CXXTEST_ADD_TEST(test_cov_particles test_particles.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_particles.h)

set_target_properties(test_cov_particles PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
target_link_libraries(test_cov_particles computation_lib)

CXXTEST_ADD_TEST(test_cov_particle_list test_particle_list.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_particle_list.h)

set_target_properties(test_cov_particle_list PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
target_link_libraries(test_cov_particle_list computation_lib)

CXXTEST_ADD_TEST(test_thread_stl test_thread_stl.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/computation/test_thread_stl.h)

set_target_properties(test_thread_stl PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
target_link_libraries(test_thread_stl ${TBB_LIBRARIES})


add_dependencies(check  computation test_cov_physvector test_cov_key test_cov_voisin test_cov_particle test_cov_particle_real test_cov_particles test_cov_particle_list)
