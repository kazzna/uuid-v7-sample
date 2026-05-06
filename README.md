# uuid-v7-sample

Practice UUID v7

## generate

### Build and Test in Docker

To generate a UUID v7 using the default settings:

```bash
docker compose run --build --rm generate
```

Run the dev container with the default workflow, or pass a command to run instead:

```bash
docker compose run --build --interactive --rm --service-ports --tty generate-dev [COMMAND [ARG] ...]
```
