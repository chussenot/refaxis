#include <iostream>
#include <string>
#include <hiredis/hiredis.h>
#include <nlohmann/json.hpp>
#include "utils/env_utils.h" 
#include "cxxopts.hpp"

using json = nlohmann::json;

// Function to execute a Redis command and print the result
void executeRedisCommand(redisContext* redis, const std::string& command) {
    redisReply* reply = (redisReply*)redisCommand(redis, command.c_str());

    if (reply == nullptr || redis->err) {
        std::cerr << "Redis command error: " << (reply ? reply->str : "") << std::endl;
    } else {
        std::cout << "Redis command result: " << reply->str << std::endl;
    }

    freeReplyObject(reply);
}

// Function to list all keys in Redis and print them to standard output
void listAllKeys(redisContext* redis) {
    redisReply* reply = (redisReply*)redisCommand(redis, "KEYS *");

    if (reply == nullptr || redis->err) {
        std::cerr << "Redis KEYS command error: " << (reply ? reply->str : "") << std::endl;
    } else {
        if (reply->type == REDIS_REPLY_ARRAY) {
            for (size_t i = 0; i < reply->elements; ++i) {
                std::cout << "Key: " << reply->element[i]->str << std::endl;
            }
        }
    }

    freeReplyObject(reply);
}

int main(int argc, char* argv[]) {

    cxxopts::Options options("refaxis", "assets referencial");
    
    // Define flags for the --eval and --list-keys options
    options.add_options()
        ("eval", "Execute Redis command", cxxopts::value<std::string>())
        ("list-keys", "List all keys in Redis");

    // Parse command-line options
    auto result = options.parse(argc, argv);

    // Get the Redis host, port, and database number from environment variables
    std::string REDIS_HOST = getEnvironmentVariable("REDIS_HOST");
    std::string REDIS_PORT_STR = getEnvironmentVariable("REDIS_PORT");
    std::string REDIS_DB_NUM_STR = getEnvironmentVariable("REDIS_DB_NUM");

    // Convert the Redis port and database number to integers
    int REDIS_PORT = 6379; // Default port
    int REDIS_DB_NUM = 0; // Default database number

    if (!REDIS_PORT_STR.empty()) {
        try {
            REDIS_PORT = std::stoi(REDIS_PORT_STR);
        } catch (const std::exception& e) {
            std::cerr << "Failed to parse Redis port: " << e.what() << std::endl;
            return 1;
        }
    }

    if (!REDIS_DB_NUM_STR.empty()) {
        try {
            REDIS_DB_NUM = std::stoi(REDIS_DB_NUM_STR);
        } catch (const std::exception& e) {
            std::cerr << "Failed to parse Redis database number: " << e.what() << std::endl;
            return 1;
        }
    }

    // Establish a connection to the Redis server with the specified database number
    redisContext* redis = redisConnect(REDIS_HOST.c_str(), REDIS_PORT);

    if (redis == nullptr || redis->err) {
        if (redis) {
            std::cerr << "Redis connection error: " << redis->errstr << std::endl;
            redisFree(redis);
        } else {
            std::cerr << "Could not allocate Redis context" << std::endl;
        }
        return 1;
    }

    // Set the Redis database number
    redisReply* selectReply = (redisReply*)redisCommand(redis, "SELECT %d", REDIS_DB_NUM);
    if (selectReply == nullptr || redis->err) {
        std::cerr << "Failed to select Redis database: " << (selectReply ? selectReply->str : "") << std::endl;
        redisFree(redis);
        return 1;
    }

    freeReplyObject(selectReply);

    // Check if the --eval option is specified
    if (result.count("eval")) {
        // Execute the provided Redis command
        std::string redisCommand = result["eval"].as<std::string>();
        executeRedisCommand(redis, redisCommand);
        redisFree(redis);

        return 0;
    } else if (result.count("list-keys")) { // Check for the new --list-keys option
        listAllKeys(redis);

        // Free the Redis reply and disconnect from the Redis server
        redisFree(redis);

        return 0;
    } else {

        // Create a custom JSON structure {"foo": "bar"}
        json assetData = {
            {"foo", "bar"}
        };

        // Generate a unique identifier (UUID) for the asset
        std::string assetId = "foo";

        // Convert the asset data to a string
        std::string assetString = assetData.dump();

        // Store the asset data in Redis using the assetId as the key
        redisReply* reply = (redisReply*)redisCommand(redis, "SET %s \"%s\"", assetId.c_str(), assetString.c_str());

        if (reply == nullptr || redis->err) {
            std::cerr << "Redis SET error: " << (reply ? reply->str : "") << std::endl;
        } else {
            std::cout << "Asset data stored in Redis with key: " << assetId << std::endl;
        }

        // Free the Redis reply and disconnect from the Redis server
        freeReplyObject(reply);
        redisFree(redis);
        return 0;
    }
}
