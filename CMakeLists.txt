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