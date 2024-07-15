#include "game.h"
#include "common.h"
#include "graphscript.h"
#include "script.h"
#include "sortscript.h"
#include "step.h"
#include <raylib.h>

Script script;

void graphscript_get_script(Script *);

void Init() {
  InitWindow(WIDTH, HEIGHT, "AlgoViz");
  SetTargetFPS(FR);

  graphscript_get_script(&script);
}

void Run() {
  script.init();
  while (!WindowShouldClose()) {
    script.run();

    BeginDrawing();
    ClearBackground(SKYBLUE);
    script.draw();
    EndDrawing();
  }

  CloseWindow();
}

void Cleanup() {
  step_queue_cleanup();
  script.cleanup();
}
