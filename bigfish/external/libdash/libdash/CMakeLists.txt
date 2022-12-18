cmake_minimum_required(VERSION 2.8)

include_directories(include)

file(GLOB_RECURSE libdash_source *.cpp)

add_library(dash SHARED ${libdash_source})
target_link_libraries(dash z xml2 curl)