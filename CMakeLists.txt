cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name: chess
project(chess_yz6120 LANGUAGES CXX)

# build type, default Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# flags
message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")
list(APPEND flags "-fPIC" "-Wall")
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

# game components
add_library(game_component
    STATIC
        util.hpp
        util.cpp
        piece.hpp
        piece.cpp
        board.hpp
        board.cpp
        player.hpp
        player.cpp
        ChessBoard.h
        Chessboard.cpp
)
set_target_properties(game_component
PROPERTIES
  CXX_STANDARD 14
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE 1
)
target_compile_options(game_component
  PRIVATE
    ${flags}
  )

# executable chess
add_executable(chess ChessMain.cpp)
set_target_properties(chess
PROPERTIES
  CXX_STANDARD 14
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE 1
)
target_compile_options(chess
  PRIVATE
    "-fPIC"
  )
target_link_libraries(chess game_component)

# download and add catch2
include(ExternalProject)
ExternalProject_Add(catch2
	URL https://github.com/catchorg/Catch2/archive/v2.9.2.tar.gz
  DOWNLOAD_DIR $ENV{HOME}/.cmake-downloads
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps
  )
include_directories(PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/deps/include)

# testing binary
add_executable(Tests Tests/ChessTests.cpp)
set_target_properties(Tests
PROPERTIES
  # catch2 required cxx17
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE 1
)
target_link_libraries(Tests game_component)
add_dependencies(Tests catch2)

# enable testing
enable_testing()

# define test
add_test(
  NAME catch_test
  COMMAND $<TARGET_FILE:Tests> --success
  )
  