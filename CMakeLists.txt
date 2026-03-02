cmake_minimum_required(VERSION 3.31)
project(test LANGUAGES CXX) # Project name

set(CMAKE_CXX_STANDARD 17) # C std version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(SOURCES 
  src/main.cpp
  src/passenger.cpp
  src/flight.cpp
  src/route.cpp
  src/seat.cpp
  src/airline.cpp
)
add_executable(a.out ${SOURCES})

target_compile_options(a.out PRIVATE -Wall) # Any compiler options, exlcuding link libraries

# Linker libraries
set(LINK_LIBS

)
target_link_libraries(a.out PRIVATE ${LINK_LIBS}) 
