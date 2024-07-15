#include "graphscript.h"
#include "common.h"
#include "force.h"
#include "particle.h"
#include "raylib.h"
#include "script.h"
#include <math.h>
#include <stdio.h>

typedef struct al {
  Particle p;
  struct al *next;
} AdjacencyList;

#define NUM_PARTICLES 5

Particle A, B, C;
AdjacencyList particles[NUM_PARTICLES];

void graphscript_init() {
  Vector2 center = {WIDTH / 2.0f, HEIGHT / 2.0f};

  float angle = 6.28f / NUM_PARTICLES;
  float theta = 0.0f;
  float d = 50.0f;
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    particles[i].p.pos =
        (Vector2){d * cos(theta) + center.x, d * sin(theta) + center.y};
    particles[i].p.invMass = 1.0f / 10.0f;
    theta += angle;

    particles[i].next = &particles[(i + 1) % NUM_PARTICLES];
  }

  /*A.invMass = 1.0f / 25.0f;*/
  /*A.pos = (Vector2){center.x, center.y};*/
  /**/
  /*B.invMass = 1.0f / 25.0f;*/
  /*B.pos = (Vector2){center.x, center.y - 100.0f};*/
  /**/
  /*C.invMass = 1.0f / 25.0f;*/
  /*C.pos = (Vector2){center.x + 50.0f, center.y - 50.0f};*/
}

void graphscript_run() {
  /*Vector2 fa, fb, fc, fc2, dragA, dragB, dragC;*/
  /*make_spring_force(A.pos, B.pos, 1.5f, 150.0f, &fa);*/
  /*make_spring_force(B.pos, A.pos, .5f, 150.0f, &fb);*/
  /*make_spring_force(C.pos, A.pos, .8f, 150.0f, &fc);*/
  /*make_spring_force(C.pos, B.pos, .2f, 150.0f, &fc2);*/
  /**/
  /*add_force(&A, fa);*/
  /*add_force(&B, fb);*/
  /*add_force(&C, fc);*/
  /*add_force(&C, fc2);*/
  /**/
  /*float k = 5.0f;*/
  /*make_drag_force(A, k, &dragA);*/
  /*make_drag_force(B, k, &dragB);*/
  /*make_drag_force(C, k, &dragC);*/
  /*add_force(&A, dragA);*/
  /*add_force(&B, dragB);*/
  /*add_force(&C, dragC);*/
  /**/
  /*integrate(&A);*/
  /*integrate(&B);*/
  /*integrate(&C);*/
}

void graphscript_draw() {
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    DrawCircle(particles[i].p.pos.x, particles[i].p.pos.y,
               1.0f / particles[i].p.invMass, RED);

    AdjacencyList *ptr = particles + i;
    while (ptr->next != NULL) {

      DrawLine(ptr->p.pos.x, ptr->p.pos.y, ptr->next->p.pos.x,
               ptr->next->p.pos.y, BLACK);
      ptr = ptr->next;
    }
  }

  /*DrawCircle(A.pos.x, A.pos.y, 1.0f / A.invMass, RED);*/
  /*DrawCircle(B.pos.x, B.pos.y, 1.0f / B.invMass, BLUE);*/
  /*DrawCircle(C.pos.x, C.pos.y, 1.0f / C.invMass, BLUE);*/
  /*DrawLine(A.pos.x, A.pos.y, B.pos.x, B.pos.y, BLACK);*/
  /*DrawLine(C.pos.x, C.pos.y, B.pos.x, B.pos.y, BLACK);*/
  /*DrawLine(C.pos.x, C.pos.y, A.pos.x, A.pos.y, BLACK);*/

  /*char str[25];*/
  /*Vector2 v = A.vec;*/
  /*sprintf(str, "%f %f", v.x, v.y);*/
  /*DrawText(str, WIDTH / 2, 0, 32, RED);*/
}

void graphscript_cleanup() {}

void graphscript_get_script(Script *s) {
  s->init = graphscript_init;
  s->run = graphscript_run;
  s->draw = graphscript_draw;
  s->cleanup = graphscript_cleanup;
}
