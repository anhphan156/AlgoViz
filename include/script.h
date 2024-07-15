#ifndef SCRIPT_H
#define SCRIPT_H

typedef struct script {
  void (*init)();
  void (*run)();
  void (*draw)();
  void (*cleanup)();
} Script;

#endif
