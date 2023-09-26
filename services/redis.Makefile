# Define variables
REDIS_COMPOSE_FILE := services/redis.yml

# Command to start the Redis service
start-redis:
	docker-compose -f $(REDIS_COMPOSE_FILE) up -d

# Command to stop the Redis service
stop-redis:
	docker-compose -f $(REDIS_COMPOSE_FILE) down

# Command to view Redis service logs
redis-logs:
	docker-compose -f $(REDIS_COMPOSE_FILE) logs

# Command to connect to the Redis service using redis-cli
redis-cli:
	docker-compose -f $(REDIS_COMPOSE_FILE) exec redis redis-cli
