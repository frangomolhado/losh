#pragma once

typedef enum {
    COMMAND,
    ARGUMENT,
} TokenType;

typedef struct {
    char *value;
    TokenType type;
} Token;

typedef struct token_queue TokenQueue;

Token *dequeue(TokenQueue *q);

TokenQueue *parse(char *input);
