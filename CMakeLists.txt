cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(Geant4_Detector)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
#include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(Geant4_Detector main.cc ${sources})
target_link_libraries(Geant4_Detector ${Geant4_LIBRARIES})
