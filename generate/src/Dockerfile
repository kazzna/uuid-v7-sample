# Build stage
FROM gcc:16.2.0-trixie@sha256:5c2f83335c97e233c80d2bc754bd5c46b2d9c32f236a765a4ac40a59f216c064 AS builder

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
FROM alpine:3.24.4@sha256:f59abe656b692d901e184be3445e084786602108599d2a51d229c0f5a48c71bf

WORKDIR /app

# 実行に必要なライブラリをコピー
COPY --from=builder /app/build/src/uuid_generate .

# デフォルトコマンド
CMD ["./uuid_generate"]
