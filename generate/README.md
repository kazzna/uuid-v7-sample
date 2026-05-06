# UUID v7 Generator

This directory contains the source code and configuration for the UUID version 7 generator.

## Docker Build Instructions

To ensure consistent builds across different environments, it is recommended to use the provided Docker configurations. Due to the modular structure of the project, please ensure that the build context is set to the `generate` directory.

### Production Image

To build the production-ready image with the current Git hash, execute the following command from the root of the repository:

```bash
docker build \
  --tag uuid-generate:latest \
  --file generate/src/Dockerfile \
  --build-arg GIT_HASH=$(git rev-parse --short HEAD) \
  --build-context project_root=generate \
  generate/src
```

### Development and Testing Image

To build the image used for development and automated testing:

```bash
docker build \
  --tag uuid-generate-dev:latest \
  --file generate/tests/Dockerfile \
  --build-arg GIT_HASH=$(git rev-parse --short HEAD) \
  generate
```

## Docker Compose Usage

The simplest way to generate a UUID v7 with version metadata is using Docker Compose:

```bash
# Set GIT_HASH environment variable and run
GIT_HASH=$(git rev-parse --short HEAD) docker compose run --build --rm generate
```

To run tests with metadata:

```bash
GIT_HASH=$(git rev-parse --short HEAD) docker compose run --build --rm generate-dev
```

## Build Context Rationale

The production Dockerfile (`src/Dockerfile`) uses `additional_contexts` (via `--build-context project_root=...`) to access the root `CMakeLists.txt` while keeping the main build context focused on the `src` directory. This ensures a minimal and efficient build process.

## Usage Options

### Multiple Generation

You can generate multiple UUIDs at once using the `--count` (or `-c`) option:

```bash
docker compose run --rm generate ./uuid_generate --count 5
```

### Versioning

The binary includes version metadata. You can check it with:

```bash
docker compose run --rm generate ./uuid_generate --version
```

Output format: `uuid_generate version 1.0.0 (hash)`
