# 本番用ソースコードのビルド設定

# 引数解析ロジックをライブラリとして定義
# これにより、テストコードからも同じロジックを簡単に利用できるようになるよ！
add_library(arg_parser_lib STATIC 
    arg_parser.c
)

# ライブラリのヘッダーファイルを探す場所を指定
target_include_directories(arg_parser_lib PUBLIC .)

# PkgConfig を使って外部ライブラリ (libuuid) を探す
find_package(PkgConfig REQUIRED)
pkg_check_modules(UUID REQUIRED uuid)

# UUID v7 生成ロジックをライブラリとして定義
add_library(uuid_v7_lib STATIC 
    uuid_v7.c
)
target_include_directories(uuid_v7_lib PUBLIC .)
target_link_libraries(uuid_v7_lib PRIVATE ${UUID_LIBRARIES})
target_compile_options(uuid_v7_lib PRIVATE ${UUID_CFLAGS})

# 実行ファイルの定義
# 名前を main から uuid_generate に変えて、より分かりやすく！
add_executable(uuid_generate main.c)

# 実行ファイルにライブラリをリンク
target_link_libraries(uuid_generate PRIVATE arg_parser_lib uuid_v7_lib)

# インストール設定
install(TARGETS uuid_generate DESTINATION bin)
