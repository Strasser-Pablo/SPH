cmake_minimum_required(VERSION 2.8)
project(sph)
ADD_DEFINITIONS(-Wall -W -Wconversion  -Wcast-qual -Wwrite-strings )
ADD_DEFINITIONS(-march=native)
INCLUDE(CPack)
find_package (Doxygen)
add_subdirectory(src/computation ./computation  )
add_custom_target(sph ALL)
if(${DOXYGEN_FOUND})
add_custom_target(doc)
add_dependencies(doc  doc_computation)
add_dependencies(sph doc)
endif()
add_custom_target(sph_computation)
add_dependencies(sph_computation computation)


add_dependencies(sph  sph_computation)

