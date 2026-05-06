FROM gcc:15.2.0-trixie

WORKDIR /workspace

RUN apt-get update && \
    apt-get install --assume-yes --no-install-recommends \
    ninja-build \
    cmake && \
    rm -rf /var/lib/apt/lists/*

# 開発用なので、ソース全体をコピーするか、composeでマウントする前提
COPY . .
