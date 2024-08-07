#cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

file(GLOB MACRO_FILES
  "*.mac"
)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES
  "*.dat"
)
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Copy input.in to the build directory
file(COPY ${PROJECT_SOURCE_DIR}/input.in DESTINATION ${PROJECT_BINARY_DIR})

add_custom_target(Simulation DEPENDS sim)
