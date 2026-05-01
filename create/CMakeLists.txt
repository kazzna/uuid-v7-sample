cmake_minimum_required(VERSION 3.10)

# プロジェクト設定
project(uuid_v7 C)

include(CTest)
enable_testing()

# C標準を指定
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# コンパイラフラグ
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -static")

# 実行ファイル
add_executable(main
	main.c
	arg_parser.c
)

add_executable(test_parse_args_help
	tests/test_parse_args_help.c
	arg_parser.c
)

add_test(NAME parse_args_help COMMAND test_parse_args_help)

add_executable(test_parse_args_help_short
	tests/test_parse_args_help_short.c
	arg_parser.c
)

add_test(NAME parse_args_help_short COMMAND test_parse_args_help_short)

add_executable(test_parse_args_version
	tests/test_parse_args_version.c
	arg_parser.c
)

add_test(NAME parse_args_version COMMAND test_parse_args_version)

add_executable(test_parse_args_count
	tests/test_parse_args_count.c
	arg_parser.c
)

add_test(NAME parse_args_count COMMAND test_parse_args_count)

add_executable(test_parse_args_count_eq
	tests/test_parse_args_count_eq.c
	arg_parser.c
)

add_test(NAME parse_args_count_eq COMMAND test_parse_args_count_eq)

add_executable(test_parse_args_count_short
	tests/test_parse_args_count_short.c
	arg_parser.c
)

add_test(NAME parse_args_count_short COMMAND test_parse_args_count_short)

add_executable(test_parse_args_count_quoted
	tests/test_parse_args_count_quoted.c
	arg_parser.c
)

add_test(NAME parse_args_count_quoted COMMAND test_parse_args_count_quoted)

add_executable(test_parse_args_count_error
	tests/test_parse_args_count_error.c
	arg_parser.c
)

add_test(NAME parse_args_count_error COMMAND test_parse_args_count_error)

add_executable(test_parse_args_short_combo
	tests/test_parse_args_short_combo.c
	arg_parser.c
)

add_test(NAME parse_args_short_combo COMMAND test_parse_args_short_combo)

add_executable(test_parse_args_equals_reject
	tests/test_parse_args_equals_reject.c
	arg_parser.c
)

add_test(NAME parse_args_equals_reject COMMAND test_parse_args_equals_reject)

add_executable(test_parse_args_count_short_eq
	tests/test_parse_args_count_short_eq.c
	arg_parser.c
)

add_test(NAME parse_args_count_short_eq COMMAND test_parse_args_count_short_eq)

# インストール設定
install(TARGETS main DESTINATION bin)
