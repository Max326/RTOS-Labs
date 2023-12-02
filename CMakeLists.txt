cmake_minimum_required(VERSION 3.10) # Specify the minimum version of CMake required

# Set the project name and version
project(MyCProject VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


file(GLOB SOURCE_FILES "src/*.c")
add_executable(my_executable_name ${SOURCE_FILES})


# Link any libraries if necessary
# target_link_libraries(my_executable_name name_of_library)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()