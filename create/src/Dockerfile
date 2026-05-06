# Build stage
FROM gcc:15.2.0-trixie AS builder

WORKDIR /app

# 必要なビルドツールをインストール
RUN apt-get update && \
    apt-get install --assume-yes --no-install-recommends ninja-build && \
    apt-get install --assume-yes --no-install-recommends cmake && \
    rm -rf /var/lib/apt/lists/*

# コンテキストからソースをコピー（src, tests, CMakeLists.txt 等が含まれる想定）
COPY . .

# ビルド
RUN cmake -B build -G Ninja && cmake --build build

# Runtime stage
FROM alpine:3.22.4

WORKDIR /app

# 実行に必要なライブラリをコピー
# TODO: 後で CMakeLists.txt を修正したらバイナリ名が uuid_create に変わるかも
COPY --from=builder /app/build/src/main .

# デフォルトコマンド
CMD ["./main"]
