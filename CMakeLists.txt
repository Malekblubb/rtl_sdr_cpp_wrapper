project(rtl_sdr_wrapper)

cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_FLAGS "-std=c++0x")
set(SRC "src")
set(HDR "include")
set(LIST "")
include_directories(${HDR} ${EXT_Z})


file(GLOB_RECURSE LIST "${HDR}/*.*")
add_library(sdr SHARED ${LIST})
set_target_properties(sdr PROPERTIES LINKER_LANGUAGE CXX) 
