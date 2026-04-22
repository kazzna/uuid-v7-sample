cmake_minimum_required(VERSION 3.10)

# プロジェクト設定
project(uuid_v7 C)

# C標準を指定
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# コンパイラフラグ
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -static")

# 実行ファイル
add_executable(main main.c)

# インストール設定
install(TARGETS main DESTINATION bin)
