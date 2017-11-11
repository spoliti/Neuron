cmake_minimum_required (VERSION 2.6)

project(Neuron)

set(CMAKE_CXX_FLAGS "-03 -W -Wall -pedantic -std=c++11 -g")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

enable_testing()
add_subdirectiory(gtest)
include_directories(${GTEST_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (Neuron main.cpp network.cpp neuron.cpp)
add_exectutable (Unit_test network.cpp neuron.cpp unit_test.cpp)
target_link_libraries (Unit_test gtest gtest_main)
add_test(Unit_test Unit_test)

find_package(doxygen)
if(DOXYGEN_FOUND)
	add_custum_target(doc
	  ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
	  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	  COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)



###### Doxygen generation ######

# 

 # We first check if Doxygen is present.
find_package(Doxygen)

if(DOXYGEN_FOUND)

    

 # We then check if the Doxygen.in configuration file exists.
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         
	- ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found
         
	- Generate one in the project folder with doxygen -g Doxyfile.in")
    
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)



 # We configure the doxyfile for make.
    
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    
add_custom_target(doc 
  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    

else(DOXYGEN_FOUND)
    
	message(FATAL_ERROR "Doxygen is needed to build the documentation.")

endif(DOXYGEN_FOUND)
