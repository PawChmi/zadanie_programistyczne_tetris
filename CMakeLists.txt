cmake_minimum_required(VERSION 2.6)
project(tetris)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${tetris_SOURCE_DIR}/cmake")
set(BIN_DIR ${tetris_SOURCE_DIR}/bin)

# Bump up warning levels tetrisropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    if(WIN32)
    message("Windows detected")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpdcurses")
    set(CURSES_LIBRARY "pdcurses")
    set(CURSES_INCLUDE_PATH "./pdcurses")
    endif(WIN32)
    if(UNIX)
    message("Linux detected")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lncursesw")
    endif(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories("./src")
file (GLOB tetris_SOURCES src/*.cpp)

add_executable(tetris ${tetris_SOURCES})
target_link_libraries(tetris ${CURSES_LIBRARY})
install(TARGETS tetris RUNTIME DESTINATION ${BIN_DIR})
