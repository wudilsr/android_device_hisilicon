cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE libdashadp_source *.cpp)

include_directories(./)
include_directories(./Decoder)
include_directories(./Managers)
include_directories(./libdashframework/Protable)
include_directories(./libdashframework/MPD)
include_directories(./libdashframework/Input)
include_directories(./libdashframework/Buffer)
include_directories(./libdashframework/Adaptation)

add_library(dashadp SHARED ${libdashadp_source})
if(PLAYREADY_SUPPORT)
target_link_libraries(dashadp dash hi_playready hi_playready_protect hi_msp)
else()
target_link_libraries(dashadp dash)
endif()
