cmake_minimum_required(VERSION 3.17)

project(pazi2)
add_executable(${PROJECT_NAME} main.cpp ocb1.cpp ocb1.h util.cpp util.h)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
find_package(BOTAN REQUIRED)
target_link_libraries(${PROJECT_NAME} ${BOTAN_LIBRARY})