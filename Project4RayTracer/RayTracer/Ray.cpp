#include "Ray.h"

//////////////////////////////////////////////////////////////////////////////
// @brief: Constructor for ray
// @param p: origin of ray
// @param d: direction of ray
Ray::Ray(glm::vec3 p, glm::vec3 d){
  pos = p;
  dir = d;
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Detect if the ray intersects a given sphere
// @param sphere: the given Sphere
// @param s1: the intersection point nearest to the ray's origin (if exists)
// @param s2: the other intersection point (if exists)
// @return true if ray intersects with sphere, false otherwise
bool Ray::findIntersection(shared_ptr<Sphere> sphere, float& s1, float& s2){
  glm::vec3 deltaP = sphere->getCenter() - pos;
  float uDotP = glm::dot(dir, deltaP);
  // If ray's direction and deltaP are in opposite direction
  if(uDotP < 0)
    return false;
  float r = sphere->getRadius();
  float value = glm::length(deltaP - dir*(uDotP));
  float delta = r*r - value*value;
  // Delta is less than 0 means there are no intersection
  if(delta < 0)
    return false;
  s1 = uDotP - sqrt(delta);
  s2 = uDotP + sqrt(delta);
  return true;
}