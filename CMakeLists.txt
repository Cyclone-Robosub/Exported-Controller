cmake_minimum_required(VERSION 3.10)
project(MyProgram VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)



# Add executable target - this is the important line
add_executable(MyProgram main.cpp)

# Includes
target_include_directories(MyProgram PRIVATE ${PROJECT_SOURCE_DIR}/SimulinkPlant/ControllerForExport_grt_rtw)

target_include_directories(MyProgram PRIVATE ${PROJECT_SOURCE_DIR}/R2024a/extern/include)
target_include_directories(MyProgram PRIVATE ${PROJECT_SOURCE_DIR}/R2024a/simulink/include)
# No output directory redirection
target_include_directories(MyProgram PRIVATE ${PROJECT_SOURCE_DIR}/R2024a/rtw/c/src)
# No other optional settings
