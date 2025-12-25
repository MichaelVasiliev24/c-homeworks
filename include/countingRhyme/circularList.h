#pragma once

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value);
Node* createCircularList(int n);
void freeCircularList(Node* head);