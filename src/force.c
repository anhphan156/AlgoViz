#include "force.h"
#include <math.h>

void make_spring_force(Vector2 p, Vector2 anchor, float k, float restLength,
                       Vector2 *out_force) {
  Vector2 pa = {p.x - anchor.x, p.y - anchor.y};
  float d = sqrt(pa.x * pa.x + pa.y * pa.y);

  float dx = d - restLength;

  pa.x /= d;
  pa.y /= d;
  out_force->x = pa.x * -k * dx;
  out_force->y = pa.y * -k * dx;
}

void make_drag_force(Particle p, float k, Vector2 *out_force) {
  Vector2 v = p.vec;
  float vecLenSq = v.x * v.x + v.y * v.y;

  out_force->x = -v.x * vecLenSq * k;
  out_force->y = -v.y * vecLenSq * k;
}
