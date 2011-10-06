cmake_minimum_required(VERSION 2.8)
project(sph)
find_package (Doxygen)
find_package( Boost COMPONENTS serialization)
link_directories ( ${Boost_LIBRARY_DIRS} )
file(GLOB_RECURSE source src/*.cpp )
add_executable(sph ${source})

add_custom_target(doc COMMAND "${DOXYGEN_EXECUTABLE}" "Doxyfile"
COMMENT "Writing documentation ..."
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc")
#add_custom_target(doc)
#add_dependencies(doc doxygen)

target_link_libraries (	   sph ${Boost_LIBRARIES})

