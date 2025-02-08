#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *next;
};

void printList(Node* head) {
  if (head != nullptr) {
    Node* current = head;
    do {
      printf("%d", current->data);
      current = current->next;
    } while(current!=head);
  }
  printf("\n");
}


void deleteNode(Node **headRef, int value) {
  Node *current = *headRef;
  Node *prev = nullptr;
  if (current != nullptr && current->data == value) {
    *headRef = current->next;
    free(current);
    return;
  }
  while (current != nullptr && current->data != value) {
    prev = current;
    current = current->next;
  }
  if (current != nullptr) {
    prev->next = current->next;
    free(current);
  }
}

void insertNode(Node **headRef, int pos, int val) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == nullptr)
    return;
  newNode->data = val;
  if (*headRef == nullptr || pos == 0) {
    newNode->next = *headRef;
    *headRef = newNode;
    return;
  }
  Node *current = *headRef;
  int count = 1;
  while (current->next != nullptr && count < pos) {
    current = current->next;
    count++;
  }
  newNode->next = current->next;
  current->next = newNode;
}


int main() {
  Node* head = nullptr;
  insertNode(&head, 1, 1);
  insertNode(&head, 2, 2);
  insertNode(&head, 3, 3);
  printf("origin linkedlist:");
  printList(head);
  deleteNode(&head, 2);
  printf("after:");
  printList(head);
}
