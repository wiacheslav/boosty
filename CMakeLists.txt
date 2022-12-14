cmake_minimum_required(VERSION 3.24)
project(boosty)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
set(Boost_USE_STATIC_LIBS        ON)
ELSE()
    set(Boost_USE_STATIC_LIBS        ON)
ENDIF()
set(Boost_USE_MULTITHREADED      ON)

set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.80.0 COMPONENTS system log REQUIRED)
find_package(OpenCL REQUIRED)
find_package(clFFT REQUIRED)

find_package(OpenGL)


if (Boost_FOUND AND OpenCL_FOUND)

    add_executable(boosty main.cpp)

    target_link_libraries(boosty LINK_PUBLIC ${Boost_LIBRARIES} OpenCL::OpenCL)


    add_executable(server server.cpp server.h session.cpp session.h)

    target_link_libraries(server LINK_PUBLIC ${Boost_LIBRARIES} OpenCL::OpenCL)
endif()