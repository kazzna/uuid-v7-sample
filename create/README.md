# UUID v7 Generator

This directory contains the source code and configuration for the UUID version 7 generator.

## Docker Build Instructions

To ensure consistent builds across different environments, it is recommended to use the provided Docker configurations. Due to the modular structure of the project, please ensure that the build context is set to the `create` directory.

### Production Image

To build the production-ready image, execute the following command from the root of the repository:

```bash
docker build -t uuid-create:latest -f create/src/Dockerfile create
```

### Development and Testing Image

To build the image used for development and automated testing, execute the following command:

```bash
docker build -t uuid-create-dev:latest -f create/tests/Dockerfile create
```

## Build Context Rationale

The Dockerfiles are situated within their respective subdirectories (`src/` and `tests/`) to maintain a clean separation of concerns. However, as the build process requires access to the shared `CMakeLists.txt` located in the root of the `create` directory, the build context must be set to `create`.
