# Build stage
FROM gcc:15.2.0-trixie@sha256:7c7782df5e7281b07fbd616c77310253a42c144068eefb71e202ad27c8be8488 AS builder

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
FROM alpine:3.23.4@sha256:5b10f432ef3da1b8d4c7eb6c487f2f5a8f096bc91145e68878dd4a5019afde11

WORKDIR /app

# 実行に必要なライブラリをコピー
COPY --from=builder /app/build/src/uuid_generate .

# デフォルトコマンド
CMD ["./uuid_generate"]
