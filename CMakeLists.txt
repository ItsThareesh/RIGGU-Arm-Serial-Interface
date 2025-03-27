cmake_minimum_required(VERSION 3.10)
project(rigguArm)

# Include directories
include_directories(
  include
)

set(SOURCE_FILES
  src/main.cpp
  src/UARTProtocol.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
