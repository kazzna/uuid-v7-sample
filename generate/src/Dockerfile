# Build stage
FROM gcc:15.2.0-trixie@sha256:7c7782df5e7281b07fbd616c77310253a42c144068eefb71e202ad27c8be8488 AS builder

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
FROM alpine:3.22.4@sha256:310c62b5e7ca5b08167e4384c68db0fd2905dd9c7493756d356e893909057601

WORKDIR /app

# 実行に必要なライブラリをコピー
COPY --from=builder /app/build/src/uuid_generate .

# デフォルトコマンド
CMD ["./uuid_generate"]
