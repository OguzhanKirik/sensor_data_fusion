cmake_minimum_required (VERSION 3.13)
project(ObjectFusion)
set (CMAKE_CXX_STANDARD 11)
# Add source to this project's executable.
add_executable (ObjectFusion)
target_include_directories(ObjectFusion PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
target_sources(ObjectFusion PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/JSONFileLogger.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/../inc/Definitions.h
			${CMAKE_CURRENT_SOURCE_DIR}/inc/ISensorInterface.h
			${CMAKE_CURRENT_SOURCE_DIR}/src/ISensorInterface.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/IFusionInterface.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/inc/IFusionInterface.h
			${CMAKE_CURRENT_SOURCE_DIR}/inc/JSONFileLogger.h)
if(CMAKE_HOST_WIN32)
  target_link_libraries(ObjectFusion ws2_32.lib)
endif()
