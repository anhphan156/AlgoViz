#include "particle.h"

void integrate(Particle *p) {
  p->acc.x = p->netForce.x * p->invMass;
  p->acc.y = p->netForce.y * p->invMass;
  p->vec.x += p->acc.x;
  p->vec.y += p->acc.y;
  p->pos.x += p->vec.x;
  p->pos.y += p->vec.y;

  // clear force
  p->netForce = (Vector2){0.0f, 0.0f};
}
void add_force(Particle *p, Vector2 f) {
  p->netForce.x += f.x;
  p->netForce.y += f.y;
}
