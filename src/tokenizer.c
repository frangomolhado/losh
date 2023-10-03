#include "tokenizer.h"

#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tk_q_node {
    Token *token;
    struct tk_q_node *next;
} TokenQNode;

typedef struct token_queue {
    TokenQNode *head;
    TokenQNode *tail;
} TokenQueue;

static TokenQueue *alloc_token_queue(void) {
    TokenQueue *q = malloc(sizeof(TokenQueue));
    q->head = NULL;
    q->tail = NULL;

    return q;
}

static void enqueue(TokenQueue *q, Token *tk) {
    TokenQNode *new_node = malloc(sizeof(TokenQNode));
    new_node->token = tk;
    new_node->next = NULL;

    if (!q->head) {
        q->head = new_node;
        q->tail = new_node;
    } else if (q->head == q->tail) {
        q->tail = new_node;
        q->head->next = q->tail;
    } else {
        q->tail->next = new_node;
        q->tail = q->tail->next;
    }
}

Token *dequeue(TokenQueue *q) {
    Token *result = NULL;

    if (!q->head) return result;

    if (q->head == q->tail) {
        result = q->head->token;
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
    } else if (q->head->next == q->tail) {
        result = q->head->token;
        free(q->head);
        q->head = q->tail;
    } else {
        result = q->head->token;
        TokenQNode *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }

    return result;
}

static Token *alloc_token(char *str, TokenType type) {
    Token *tk = malloc(sizeof(Token));
    tk->value = str;
    tk->type = type;

    return tk;
}

TokenQueue *tokenize(char input[INPUT_BUFFER_SIZE]) {
    TokenQueue *q = alloc_token_queue();

    char *delimiter = " \n";
    char *tk_value = strtok(input, delimiter);
    Token *tk = alloc_token(tk_value, COMMAND);
    enqueue(q, tk);
    while (tk_value) {
        tk_value = strtok(NULL, delimiter);
        tk = alloc_token(tk_value, ARGUMENT);
        enqueue(q, tk);
    }

    return q;
}
