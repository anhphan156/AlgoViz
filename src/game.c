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
  insertion_sort(arr_sort, len);

  float r = 30.0f;
  Color c = {255, 0, 0, 255};
  Vector2 circle_pos = {WIDTH / 2.0, HEIGHT / 2.0};
  Vector2 pos = {WIDTH / 3.0, HEIGHT / 3.0};
  float col_width = (float)WIDTH / (float)len;

  float default_cd = 1.0f / len;
  float cd = cd;
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(SKYBLUE);

    if (cd <= 0.0f && step_queue_empty()) {
      cd = default_cd;
      int a, b;
      step_dequeue(&a, &b);
      if (arr[a] != arr[b]) {
        arr[a] = arr[a] ^ arr[b];
        arr[b] = arr[a] ^ arr[b];
        arr[a] = arr[a] ^ arr[b];
      }
    }

    for (int i = 0; i < len; i += 1) {
      DrawRectangle(i * col_width, HEIGHT - arr[i], col_width, arr[i], c);
    }

    EndDrawing();
    cd -= 1.0 / FR;
  }

  CloseWindow();
}

void Cleanup() { step_queue_cleanup(); }
