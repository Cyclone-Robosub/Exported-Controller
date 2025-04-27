cmake_minimum_required(VERSION 3.10)
project(MyProgram VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include all source files from the generated code
file(GLOB CONTROLLER_SOURCES
    "${PROJECT_SOURCE_DIR}/SimulinkPlant/ControllerForExport_grt_rtw/*.c"
    "${PROJECT_SOURCE_DIR}/SimulinkPlant/ControllerForExport_grt_rtw/*.cpp"
)

# Add executable target with all necessary files
add_executable(MyProgram main.cpp ${CONTROLLER_SOURCES})

# Includes
target_include_directories(MyProgram PRIVATE
    ${PROJECT_SOURCE_DIR}/SimulinkPlant/ControllerForExport_grt_rtw
    ${PROJECT_SOURCE_DIR}/R2024a/extern/include
    ${PROJECT_SOURCE_DIR}/R2024a/simulink/include
    ${PROJECT_SOURCE_DIR}/R2024a/rtw/c/src)

# You may also need to link against MATLAB's runtime libraries
# Look for libmwrtwlib.a or similar files in your MATLAB installation
find_library(RTW_LIB
    NAMES rtwlib mwrtwlib
    PATHS "${PROJECT_SOURCE_DIR}/R2024a/rtw/c/lib"
          "${PROJECT_SOURCE_DIR}/R2024a/bin/glnxa64")

if(RTW_LIB)
    target_link_libraries(MyProgram PRIVATE ${RTW_LIB})
endif()

# Look for common RTW library names and locations
find_library(RTW_LIB
    NAMES grt_malloc rtwlib mwrtwlib libgrt_malloc.a
    PATHS "${PROJECT_SOURCE_DIR}/R2024a/rtw/c/lib"
          "${PROJECT_SOURCE_DIR}/R2024a/bin/glnxa64"
          "${PROJECT_SOURCE_DIR}/R2024a/rtw/c/grt"
          "${PROJECT_SOURCE_DIR}/R2024a/rtw/c/src"
)

if(RTW_LIB)
    message(STATUS "Found RTW library: ${RTW_LIB}")
    target_link_libraries(MyProgram PRIVATE ${RTW_LIB})
else()
    message(WARNING "RTW library not found - using stub implementations")
    # Create a stub implementation
    file(WRITE ${CMAKE_BINARY_DIR}/rtw_stubs.c "
        void rt_UpdateTXYLogVars(void* rtm, void* tid) {}
        void* rt_StartDataLoggingWithStartTime(void* rtm, double startTime,
                                          double finalTime, double* stepSize,
                                          char_T** errStatus) { return 0; }
    ")
    target_sources(MyProgram PRIVATE ${CMAKE_BINARY_DIR}/rtw_stubs.c)
endif()
