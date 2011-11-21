cmake_minimum_required(VERSION 2.8)
project(computation)
find_package (Doxygen)
file(GLOB_RECURSE source_computation *.cpp )
add_executable(computation ${source_computation})
target_link_libraries(computation ${TBB_LIBRARIES})
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