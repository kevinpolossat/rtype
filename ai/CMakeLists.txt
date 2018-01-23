CMAKE_MINIMUM_REQUIRED(VERSION 3.2.1)
project(ai CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BASIC_SOURCE Basic/Basic.cpp Basic/Basic.h)
set(CIRCLE_SOURCE Circle/Circle.cpp Circle/Circle.h)
set(LINEAR_SOURCE Linear/Linear.cpp Linear/Linear.h)
set(RANDOM_SOURCE Random/Random.cpp Random/Random.h)
set(SINUS_SOURCE Sinus/Sinus.cpp Sinus/Sinus.h)

include_directories(./)
add_library(Basic SHARED ${BASIC_SOURCE})
add_library(Circle SHARED ${CIRCLE_SOURCE})
add_library(Linear SHARED ${LINEAR_SOURCE})
add_library(Random SHARED ${RANDOM_SOURCE})
add_library(Sinus SHARED ${SINUS_SOURCE})