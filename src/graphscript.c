#include "graphscript.h"
#include "common.h"
#include "filehelper.h"
#include "force.h"
#include "particle.h"
#include "raylib.h"
#include "script.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adjacency_list_parser();

typedef struct pl {
  Particle *p;
  struct pl *next;
} ParticleList;

int NUM_PARTICLES;

Particle A, B, C;
Particle *particles;
ParticleList *adjacency_list;
Particle *particle_on_mouse = NULL;
float spring_k = 0.05f, drag_k = 5.0f;

void graphscript_init() { adjacency_list_parser(); }

void graphscript_input() {
  Vector2 mouse_pos = (Vector2){GetMouseX(), GetMouseY()};
  Vector2 particle_pos;
  Vector2 d;
  char str[100];
  if (IsMouseButtonPressed(0)) {
    mouse_pos = (Vector2){GetMouseX(), GetMouseY()};

    if (particle_on_mouse == NULL) {
      for (int i = 0; i < NUM_PARTICLES; i += 1) {
        particle_pos = particles[i].pos;
        d = (Vector2){particle_pos.x - mouse_pos.x,
                      particle_pos.y - mouse_pos.y};

        if (d.x * d.x + d.y * d.y < 100.0f) {
          particle_on_mouse = particles + i;
          break;
        }
      }
    }
  }
  if (IsMouseButtonDown(0)) {
    if (particle_on_mouse != NULL) {
      particle_on_mouse->pos = mouse_pos;
    }
  }
  if (IsMouseButtonReleased(0)) {
    particle_on_mouse = NULL;
  }
}

void graphscript_run() {
  graphscript_input();
  /*Vector2 v = particles[0].vec;*/
  /*Vector2 a = particles[0].acc;*/
  /*float vm = v.x * v.x + v.y * v.y;*/
  /*float am = a.x * a.x + a.y * a.y;*/
  /*if (vm <= 0.05f && am < vm) {*/
  /*  return;*/
  /*}*/

  Vector2 f;
  Particle *cur;
  ParticleList *adj;
  for (int i = 0; i < NUM_PARTICLES; i += 1) {

    // spring
    cur = particles + i;
    adj = adjacency_list + i;
    int rest_len = 100.0f;
    while (adj != 0) {
      make_spring_force(cur->pos, adj->p->pos, spring_k, rest_len, &f);
      add_force(cur, f);
      make_spring_force(adj->p->pos, cur->pos, spring_k, rest_len, &f);
      add_force(adj->p, f);
      adj = adj->next;
    }

    // drag
    make_drag_force(*cur, drag_k, &f);
    add_force(cur, f);

    integrate(cur);
  }
}

void graphscript_draw() {
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    DrawCircle(particles[i].pos.x, particles[i].pos.y,
               1.0f / particles[i].invMass, RED);

    Particle *cur = particles + i;
    ParticleList *ptr = adjacency_list + i;
    while (ptr != 0) {
      DrawLine(cur->pos.x, cur->pos.y, ptr->p->pos.x, ptr->p->pos.y, BLACK);
      ptr = ptr->next;
    }
  }
  DrawFPS(10.0f, 10.0f);

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
    while (ptr != 0) {
      tmp = ptr->next;
      free(ptr);
      ptr = tmp;
    }
  }
  free(adjacency_list);
  free(particles);
}

void graphscript_get_script(Script *s) {
  s->init = graphscript_init;
  s->run = graphscript_run;
  s->draw = graphscript_draw;
  s->cleanup = graphscript_cleanup;
}

void adjacency_list_parser() {
  const char *path = "/home/backspace/data/dev/algoviz/res/adjlist.txt";
  char *result = read_file(path);
  NUM_PARTICLES = *result - 48;
  char *c = result + 2;

  particles = malloc(sizeof(Particle) * NUM_PARTICLES);
  adjacency_list = malloc(sizeof(ParticleList) * NUM_PARTICLES);

  Vector2 center = {WIDTH / 2.0f, HEIGHT / 2.0f};
  float angle = 6.28f / NUM_PARTICLES;
  float theta = 0.0f;
  float d = 50.5f;
  for (int i = 0; i < NUM_PARTICLES; i += 1) {
    particles[i].netForce = (Vector2){0.0f, 0.0f};
    particles[i].acc = (Vector2){0.0f, 0.0f};
    particles[i].vec = (Vector2){0.0f, 0.0f};
    particles[i].pos =
        (Vector2){d * cos(theta) + center.x, d * sin(theta) + center.y};
    particles[i].invMass = 1.0f / 10.0f;
    theta += angle;

    adjacency_list[i].p = NULL;
    adjacency_list[i].next = NULL;
  }

  int n;
  int i = 0, j = -1;
  ParticleList *ptr = adjacency_list + i;
  ParticleList *prev, *tmp;
  while (*c != 0) {
    if (*c == 10) {
      i += 1;
      j = -1;
      tmp = ptr;
      ptr = adjacency_list + i;
      prev->next = NULL;
      free(tmp);
    } else if (*c >= 48 && *c <= 57) {
      j += 1;
      if (*c - 48 == 1) {
        prev = ptr;
        ptr->p = particles + j;
        ptr->next = malloc(sizeof(ParticleList));
        ptr = ptr->next;
        ptr->next = (void *)0;
      }
    }

    c++;
  }
  free(result);
}
