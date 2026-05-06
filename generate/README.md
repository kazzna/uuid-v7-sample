# UUID v7 Generator

This directory contains the source code and configuration for the UUID version 7 generator.

## Docker Build Instructions

To ensure consistent builds across different environments, it is recommended to use the provided Docker configurations. Due to the modular structure of the project, please ensure that the build context is set to the `generate` directory.

### Production Image

To build the production-ready image, execute the following command from the root of the repository:

```bash
docker build --tag uuid-generate:latest --file generate/src/Dockerfile generate
```

### Development and Testing Image

To build the image used for development and automated testing, execute the following command:

```bash
docker build --tag uuid-generate-dev:latest --file generate/tests/Dockerfile generate
```

## Docker Compose Usage

The simplest way to generate a UUID v7 is using Docker Compose from the root of the repository:

```bash
docker compose run --build --rm generate
```

## Build Context Rationale

The Dockerfiles are situated within their respective subdirectories (`src/` and `tests/`) to maintain a clean separation of concerns. However, as the build process requires access to the shared `CMakeLists.txt` located in the root of the `generate` directory, the build context must be set to `generate`.
