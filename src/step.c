#include "step.h"
#include <stdlib.h>

Step *head, *tail;

void step_enqueue(int a, int b) {
  if (head == 0) {
    head = malloc(sizeof(Step));
    head->a = a;
    head->b = b;
    head->next = NULL;
    tail = head;

    return;
  }

  Step *new = malloc(sizeof(Step));
  new->a = a;
  new->b = b;
  new->next = 0;
  head->next = new;
  head = new;
}

void step_dequeue(int *a, int *b) {
  if (tail == 0) {
    head = 0;
    return;
  }

  Step *tmp = tail;
  tail = tail->next;
  *a = tmp->a;
  *b = tmp->b;
  free(tmp);
}

void step_queue_cleanup() {
  int a, b;
  while (tail != 0) {
    step_dequeue(&a, &b);
  }
}

char step_queue_empty() { return tail == 0; }
