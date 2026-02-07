cmake_minimum_required(VERSION 3.16)
project(BL4S2026)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/src/*.hh)

file(COPY mac stl dat DESTINATION ${PROJECT_BINARY_DIR})

add_executable(main ${SOURCES} ${HEADERS})
target_link_libraries(main ${Geant4_LIBRARIES})