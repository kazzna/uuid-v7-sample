FROM gcc:15.2.0-trixie

WORKDIR /workspace

RUN apt-get update && \
    apt-get install --assume-yes --no-install-recommends \
    ninja-build \
    cmake \
    uuid-dev \
    pkg-config && \
    rm -rf /var/lib/apt/lists/*

# 開発用なので、ソース全体をコピーするか、composeでマウントする前提
COPY . .

# ビルド引数でGitハッシュを受け取る
ARG GIT_HASH=unknown

# ビルド時にGitハッシュを渡す
ENV GIT_HASH=${GIT_HASH}
