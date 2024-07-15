#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct particle {
  Vector2 pos;
  Vector2 vec;
  Vector2 acc;
  Vector2 netForce;
  float invMass;
} Particle;

void integrate(Particle *);
void add_force(Particle *, Vector2);

#endif
