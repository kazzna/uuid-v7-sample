# テストコードのビルド設定

# テスト用の実行ファイルを定義するマクロ
# 同じような記述を繰り返さないための工夫だよ！
macro(add_uuid_test name)
    add_executable(${name} ${name}.c)
    # 本番用のライブラリ (arg_parser_lib) をリンク！
    target_link_libraries(${name} PRIVATE arg_parser_lib)
    # ヘッダーファイルを探す場所に src を追加
    target_include_directories(${name} PRIVATE ../src)
    # CTest に登録
    add_test(NAME ${name} COMMAND ${name})
endmacro()

# テスト一覧
add_uuid_test(test_parse_args_help)
add_uuid_test(test_parse_args_help_short)
add_uuid_test(test_parse_args_version)
add_uuid_test(test_parse_args_count)
add_uuid_test(test_parse_args_count_eq)
add_uuid_test(test_parse_args_count_short)
add_uuid_test(test_parse_args_count_quoted)
add_uuid_test(test_parse_args_count_error)
add_uuid_test(test_parse_args_short_combo)
add_uuid_test(test_parse_args_equals_reject)
add_uuid_test(test_parse_args_count_short_eq)
