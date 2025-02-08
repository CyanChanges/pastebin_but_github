#include <stdlib.h>

struct Node {
  Node *pre;
  int data;
  Node *next;
};

Node *insertNode(Node *head, int data, int position) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->data = data;
  temp->pre = nullptr;
  temp->next = nullptr;
  if (position == 1) {
    temp->next = head;
    temp->pre = temp;
    head = temp;
  } else {
    Node *body = head;
    for (int i = 1; i < position - 1; i++) {
      body = body->next;
      if (!body) {
        abort();
      }
    }
    if (body && (body->next == nullptr)) {
      body->next = temp;
      temp->pre = body;
    } else {
      body->next->pre = temp;
      temp->next = body->next;
      body->next = temp;
      temp->pre = body;
    }
  }
  return head;
}
