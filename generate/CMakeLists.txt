cmake_minimum_required(VERSION 3.10)

# プロジェクト設定
project(uuid_v7 C)

# C標準を指定
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# コンパイラフラグ
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -static")

# テストを有効化
include(CTest)
enable_testing()

# Git ハッシュの取得
find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endif()

if(NOT GIT_HASH)
    set(GIT_HASH "unknown")
endif()

message(STATUS "Git hash: ${GIT_HASH}")
add_definitions(-DGIT_HASH="${GIT_HASH}")

# 子ディレクトリの追加
# src を先に読み込むことで、tests からライブラリが見えるようにするよ！
add_subdirectory(src)
add_subdirectory(tests)
