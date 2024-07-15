#ifndef FORCE_H
#define FORCE_H

#include "particle.h"
#include <raylib.h>

void make_spring_force(Vector2, Vector2, float, float, Vector2 *);
void make_drag_force(Particle, float, Vector2 *);

#endif
