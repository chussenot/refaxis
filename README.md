## Configuration

The utility uses environment variables to configure the Redis server connection and database number.

```bash
REDIS_HOST: The hostname or IP address of the Redis server (default is localhost).
REDIS_PORT: The port of the Redis server (default is 6379).
REDIS_DB_NUM: The Redis database number (default is 0).
```
You can set these environment variables before running the utility.

## Usage
Set the environment variables to configure the Redis connection. For example:

```bash
export REDIS_HOST=localhost
export REDIS_PORT=6379
export REDIS_DB_NUM=0
```