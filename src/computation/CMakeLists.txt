cmake_minimum_required(VERSION 2.8)
project(computation)
IF(NOT No_DOC)
find_package (Doxygen)
ENDIF(NOT No_DOC)
file(GLOB_RECURSE source_computation *.cpp )
add_executable(computation ${source_computation})
target_link_libraries(computation ${TBB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lprofiler -lspooles -lumfpack -lsuitesparseconfig -lrt -lamd -lcholmod -lcolamd -lblas -llapack )
add_library(computation_lib STATIC ${source_computation})
set_target_properties(computation_lib PROPERTIES COMPILE_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage" LINK_FLAGS "-g -ftest-coverage -fprofile-arcs -o0 --coverage")
target_link_libraries(computation_lib ${TBB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lprofiler -lspooles -lumfpack -lsuitesparseconfig -lrt -lamd -lcholmod -lcolamd -lblas -llapack)
  if(${DOXYGEN_FOUND})
add_custom_target(doc_computation COMMAND "${DOXYGEN_EXECUTABLE}" "Doxyfile"
COMMENT "Writing documentation ..."
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../doc/computation/")
else()
message("Documentation will no be created because Doxygen was no found.
 After installation of Doxygen relaunch cmake")
endif()

install (TARGETS computation DESTINATION bin)

add_test(NAME computation_crash_test  COMMAND $<TARGET_FILE:computation>)

add_test(NAME determinism  COMMAND ${test_determinism} $<TARGET_FILE:computation>)
add_dependencies(check  computation)
