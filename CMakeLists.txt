cmake_minimum_required(VERSION 3.25)
project(FakeCheatIndicator)

set(CMAKE_CXX_STANDARD 20)

find_package(GeodeFramework REQUIRED)

setup_geode_mod(
    FakeCheatIndicator
    SOURCES
        src/main.cpp
)
