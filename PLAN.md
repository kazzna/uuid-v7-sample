# PLAN

## コマンドライン引数仕様

- [ ] コマンドライン引数が0個でも正常に動く（デフォルト動作が定義される）
- [ ] `-h` または `--help` がコマンドライン引数に指定されていた場合、他に引数があってもなくてもヘルプを表示して終了する
  - ヘルプには以下の情報を表示する（詳細は後で決める）：
    - バージョン
    - 起動方法
    - ヘルプ起動方法
- [ ] `-v` または `--version` が指定されていた場合、バージョンを表示して終了する
  - 他に引数があった場合でもversionを優先する
  - ただし、helpがあった場合にはhelpの方が優先される（versionは無視される）
- [ ] `-c` または `--count` という引数があった場合、その直後にスペース区切りまたは `=` で繋げて数値を指定する
  - 成功する形式：
    - `-c 8`
    - `-c=4`
    - `--count 11`
    - `--count=6`
    - `--count="19"`
  - エラーになる形式：
    - `-c` （数値がない）
    - `--count` なし （数値がない）
    - `--count = 11` （スペースで分ける）
    - `-c -4` （負の数）
    - `--count 0.8` （小数）
    - `--count 4*2` （数式や非数値）
  - 正の整数のみ有効
- [ ] 短い形式のフラグは連結して書ける
  - フラグは左から右へ処理される
  - 各フラグは独立したフラグとして認識される
  
#### 短い形式での `-c` の処理ルール
- `-c` は直後に数値が必要
  - 短い形式の残りの文字列に数値があればそれを使う
  - 短い形式の残りが数値ではない場合：
    - 残りの文字列に `-h` が含まれている場合（`-ch`, `-hcv` など）：パース成功。`-h` を優先してヘルプ表示
    - `-h` が含まれていない他のフラグが続く場合（`-cv`, `-vc` など）：パースエラー
  - 短い形式に数値がない場合、次の引数を見る
    - 次の引数が数値なら：パース成功（`-vc 3` など）
    - 次の引数がない、または数値でなければ：パースエラー

#### 短い形式の処理例
- `-hvc 4`：`-h`, `-v`, `-c 4` と解釈。パース成功。`-h` 優先でヘルプ表示
- `-ch`：`-c` の直後に `h` （`-h` フラグ）。パース成功。`-h` 優先でヘルプ表示
- `-hcv`：`-h`, `-c`, `v` と解釈。`-c` の直後に `v` だが、全体に `-h` が含まれている。パース成功。`-h` 優先でヘルプ表示
- `-cv`：`-c` の直後に `v` （`-v` フラグ）、`-h` が含まれていない。パースエラー
- `-vc`：`-v`, `-c` と解釈。`-c` の直後に数値がなく、次の引数もない。パースエラー
- `-vc 3`：`-v`, `-c` と解釈。`-c` の次の引数が `3`。パース成功。`-v` 優先でバージョン表示

## `parse_args` 関数設計

### シグネチャー
```c
ParseResult *parse_args(int argc, char *argv[]);
```

### ステータス型
```c
typedef enum {
    PARSE_SUCCESS,
    PARSE_ERROR
} ParseStatus;
```

### Count 結果型
```c
typedef enum {
    COUNT_SUCCESS,
    COUNT_ERROR
} CountStatus;

typedef struct {
    CountStatus status;
    union {
        int value;          // COUNT_SUCCESS の場合の値（未指定時はデフォルト1）
        char *message;      // COUNT_ERROR の場合のエラーメッセージ
    } data;
} CountResult;
```

### 成功時の設定構造体
```c
typedef struct {
    int help;           // 1 if -h or --help
    int version;        // 1 if -v or --version
    CountResult count;  // -c で指定された値（成功・失敗で分かれる）
} Config;
```

### エラー情報構造体
```c
typedef struct {
    char *message;  // エラーメッセージ
} ArgParseError;
```

### 結果型
```c
typedef struct {
    ParseStatus status;
    union {
        Config *config;         // PARSE_SUCCESS の場合（malloc で確保）
        ArgParseError *error;   // PARSE_ERROR の場合（malloc で確保）
    } value;
} ParseResult;
```

**注意：** 
- ParseStatusは2種類のみ（成功 or エラー）
- `parse_args` の戻り値は `malloc` で確保されるので、呼び出し側で `free()` で解放する責任がある
- 成功時は `result->value.config`、失敗時は `result->value.error` をアクセス
