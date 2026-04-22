# Build stage
FROM gcc:15.2.0-trixie AS builder

WORKDIR /app

# 必要なビルドツールをインストール
RUN apt-get update && \
    apt-get install --assume-yes --no-install-recommends ninja-build && \
    apt-get install --assume-yes --no-install-recommends cmake && \
    rm -rf /var/lib/apt/lists/*

# ソースコードをコピー
COPY . .

# ビルド
RUN cmake -B build -G Ninja && cmake --build build

# Runtime stage
FROM alpine:3.22.4

WORKDIR /app

# 実行に必要なライブラリをコピー
COPY --from=builder /app/build/main .

# デフォルトコマンド
CMD ["./main"]
