#include "graphscript.h"
#include "common.h"
#include "force.h"
#include "particle.h"
#include "raylib.h"
#include "script.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct pl {
  Particle *p;
  struct pl *next;
} ParticleList;

#define NUM_PARTICLES 5

Particle A, B, C;
Particle particles[NUM_PARTICLES];
ParticleList *adjacency_list;

void graphscript_init() {
  Vector2 center = {WIDTH / 2.0f, HEIGHT / 2.0f};

  adjacency_list = malloc(sizeof(ParticleList) * NUM_PARTICLES);

  float angle = 6.28f / NUM_PARTICLES;
  float theta = 0.0f;
  float d = 100.0f;
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    particles[i].pos =
        (Vector2){d * cos(theta) + center.x, d * sin(theta) + center.y};
    particles[i].invMass = 1.0f / 10.0f;
    theta += angle;

    adjacency_list[i].p = &particles[i];
    adjacency_list[i].next = malloc(sizeof(ParticleList));
    adjacency_list[i].next->p = &particles[(i + 1) % NUM_PARTICLES];
    adjacency_list[i].next->next = (void *)0;
  }
}

void graphscript_run() {
  float spring_k = 0.05f, drag_k = 5.0f;
  Vector2 f;
  ParticleList *cur, *adj;
  for (int i = 0; i < NUM_PARTICLES; i += 1) {

    // spring
    cur = adjacency_list + i;
    adj = cur;
    while (adj->next != 0) {
      adj = adj->next;
      make_spring_force(cur->p->pos, adj->p->pos, spring_k, 100.0f, &f);
      add_force(cur->p, f);
      make_spring_force(adj->p->pos, cur->p->pos, spring_k, 100.0f, &f);
      add_force(adj->p, f);
    }

    // drag
    make_drag_force(*cur->p, drag_k, &f);
    add_force(cur->p, f);

    integrate(cur->p);
  }
}

void graphscript_draw() {
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    DrawCircle(particles[i].pos.x, particles[i].pos.y,
               1.0f / particles[i].invMass, RED);

    ParticleList *ptr = adjacency_list + i;
    ParticleList *cur = ptr;
    while (ptr->next != 0) {
      ptr = ptr->next;
      DrawLine(cur->p->pos.x, cur->p->pos.y, ptr->p->pos.x, ptr->p->pos.y,
               BLACK);
    }
  }

  /*char str[25];*/
  /*Vector2 v = A.vec;*/
  /*sprintf(str, "%f %f", v.x, v.y);*/
  /*DrawText(str, WIDTH / 2, 0, 32, RED);*/
}

void graphscript_cleanup() {
  ParticleList *tmp;
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    ParticleList *ptr = adjacency_list + i;
    ptr = ptr->next;
    while (ptr != NULL) {
      tmp = ptr->next;
      free(ptr);
      ptr = tmp;
    }
  }
  free(adjacency_list);
}

void graphscript_get_script(Script *s) {
  s->init = graphscript_init;
  s->run = graphscript_run;
  s->draw = graphscript_draw;
  s->cleanup = graphscript_cleanup;
}
