#ifndef STEP_H
#define STEP_H

typedef struct step {
  int a;
  int b;
  struct step *next;
} Step;

void step_enqueue(int, int);
void step_dequeue(int *, int *);
void step_queue_cleanup();
char step_queue_empty();

#endif
