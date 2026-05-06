# 本番用ソースコードのビルド設定

# 引数解析ロジックをライブラリとして定義
# これにより、テストコードからも同じロジックを簡単に利用できるようになるよ！
add_library(arg_parser_lib STATIC 
    arg_parser.c
)

# ライブラリのヘッダーファイルを探す場所を指定
target_include_directories(arg_parser_lib PUBLIC .)

# 実行ファイルの定義
# 名前を main から uuid_create に変えて、より分かりやすく！
add_executable(uuid_create main.c)

# 実行ファイルにライブラリをリンク
target_link_libraries(uuid_create PRIVATE arg_parser_lib)

# インストール設定
install(TARGETS uuid_create DESTINATION bin)
