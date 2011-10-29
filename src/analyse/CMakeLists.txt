cmake_minimum_required(VERSION 2.8)
project(analyse)
find_package (Doxygen)
FIND_PACKAGE(SDL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
find_package( Boost COMPONENTS serialization REQUIRED)
link_directories ( ${Boost_LIBRARY_DIRS} )
link_directories ( ${SDL_LIBRARY_DIRS} )
file(GLOB_RECURSE source_analyse *.cpp )
add_executable(analyse ${source_analyse})

  if(${DOXYGEN_FOUND})
add_custom_target(doc_analyse COMMAND "${DOXYGEN_EXECUTABLE}" "Doxyfile"
COMMENT "Writing documentation ..."
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../doc/analyse/")
else()
message("Documentation will no be created because Doxygen was no found.
 After installation of Doxygen relaunch cmake")
endif()

target_link_libraries (	   analyse ${Boost_LIBRARIES})
target_link_libraries (	   analyse ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES( analyse ${OPENGL_LIBRARIES})

install(TARGETS analyse  DESTINATION bin)
