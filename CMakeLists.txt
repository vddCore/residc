cmake_minimum_required(VERSION 3.0)

project(reSIDc)

if(!WIN32)
  add_definitions("-Wall -pedantic")
  add_definitions("-fPIC")
endif(!WIN32)

add_subdirectory(src)