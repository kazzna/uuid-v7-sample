# Build stage
FROM gcc:16.2.0-trixie@sha256:b69972d6afe6d5f6c7f91ae30027caf8a50549ee25b63031071383d00941bf2f AS builder

WORKDIR /app

# 必要なビルドツールをインストール
RUN apt-get update && \
    apt-get install --assume-yes --no-install-recommends ninja-build && \
    apt-get install --assume-yes --no-install-recommends cmake && \
    apt-get install --assume-yes --no-install-recommends uuid-dev && \
    apt-get install --assume-yes --no-install-recommends pkg-config && \
    rm -rf /var/lib/apt/lists/*

# ビルド引数でGitハッシュを受け取る
ARG GIT_HASH=unknown

# コンテキストからソースをコピー
COPY . .
COPY --from=project_root CMakeLists.txt ..
COPY --from=project_root tests/ ../tests/

# ビルド (Gitハッシュを明示的に渡す)
RUN cmake -S .. -B build -G Ninja -DGIT_HASH=${GIT_HASH} && cmake --build build

# Runtime stage
FROM alpine:3.24.1@sha256:28bd5fe8b56d1bd048e5babf5b10710ebe0bae67db86916198a6eec434943f8b

WORKDIR /app

# 実行に必要なライブラリをコピー
COPY --from=builder /app/build/src/uuid_generate .

# デフォルトコマンド
CMD ["./uuid_generate"]
