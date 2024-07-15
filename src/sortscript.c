#include "sortscript.h"
#include "common.h"
#include "raylib.h"
#include "script.h"
#include "sortfns.h"
#include "step.h"
#include <stdlib.h>
#include <time.h>

float cd, default_cd, col_width;
int *arr, *arr_sort;
int len;
Color c_red, c_blue;

void sortscript_get_script(Script *script) {
  script->init = sortscript_init;
  script->run = sortscript_run;
  script->draw = sortscript_draw;
  script->cleanup = sortscript_cleanup;
}

void sortscript_init() {
  len = 100;
  arr = malloc(sizeof(int) * len);
  arr_sort = malloc(sizeof(int) * len);
  srand(time(0));
  for (int i = 0; i < len; i += 1) {
    arr[i] = rand() % HEIGHT;
    arr_sort[i] = arr[i];
  }
  quick_sort(arr_sort, len, 0);
  /*insertion_sort(arr_sort, len);*/
  /*selection_sort(arr_sort, len);*/

  c_red = ((Color){255, 0, 0, 255});
  c_blue = ((Color){0, 0, 255, 80});
  col_width = (float)WIDTH / (float)len;

  default_cd = 1.0f / (len * 100.0f);
  cd = default_cd;
}

void sortscript_run() {
  if (cd <= 0.0f && !step_queue_empty()) {
    cd = default_cd;
    int a, b;
    step_dequeue(&a, &b);
    if (arr[a] != arr[b]) {
      arr[a] ^= arr[b];
      arr[b] ^= arr[a];
      arr[a] ^= arr[b];
    }
  }
  cd -= 1.0 / FR;
}

void sortscript_draw() {

  for (int i = 0; i < len; i += 1) {
    DrawRectangle(i * col_width, HEIGHT - arr[i], col_width, arr[i], c_red);
    DrawRectangle(i * col_width, HEIGHT - arr_sort[i], col_width, arr_sort[i],
                  c_blue);
  }
}

void sortscript_cleanup() {
  free(arr);
  free(arr_sort);
}
