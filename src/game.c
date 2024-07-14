#include "game.h"
#include "common.h"
#include "sortfns.h"
#include "step.h"
#include <raylib.h>
#include <time.h>

void Init() {
  InitWindow(WIDTH, HEIGHT, "AlgoViz");
  SetTargetFPS(FR);
}

void Run() {
  int len = 100;
  int *arr = alloca(sizeof(int) * len);
  int *arr_sort = alloca(sizeof(int) * len);
  srand(time(0));
  for (int i = 0; i < len; i += 1) {
    arr[i] = rand() % HEIGHT;
    arr_sort[i] = arr[i];
  }
  quick_sort(arr_sort, len, 0);
  /*insertion_sort(arr_sort, len);*/
  /*selection_sort(arr_sort, len);*/

  Color c = {255, 0, 0, 255};
  Color c_blue = {0, 0, 255, 100};
  float col_width = (float)WIDTH / (float)len;

  float default_cd = 1.0f / (len * 100.0f);
  /*float default_cd = 1.0f;*/
  float cd = default_cd;
  while (!WindowShouldClose()) {

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

    BeginDrawing();
    ClearBackground(SKYBLUE);
    for (int i = 0; i < len; i += 1) {
      DrawRectangle(i * col_width, HEIGHT - arr[i], col_width, arr[i], c);
      DrawRectangle(i * col_width, HEIGHT - arr_sort[i], col_width, arr_sort[i],
                    c_blue);
    }
    EndDrawing();
  }

  CloseWindow();
}

void Cleanup() { step_queue_cleanup(); }
