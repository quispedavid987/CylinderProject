cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(G4wcd)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories($(PROJECT_SOURCE_DIR)/src ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.h)

add_executable(simu simu.cc ${sources} ${headers})

target_link_libraries(simu ${Geant4_LIBRARIES})

add_custom_target(G4wcd DEPENDS simu)