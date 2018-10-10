#ifndef __RAY__
#define __RAY__

#include "../Utilities/glm/vec3.hpp" // glm::vec3
#include "../Utilities/glm/vec4.hpp" // glm::vec3
#include "../Utilities/glm/geometric.hpp"
#include "../Utilities/glm/mat4x4.hpp"
#include "Sphere.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>   
#include <stdlib.h>

using namespace std;

class Ray {
  public:
    Ray(glm::vec3 p, glm::vec3 d);
    // Might add variables near, far for clipping plane?
    bool findIntersection(shared_ptr<Sphere> sphere, float& s1, float& s2);
    glm::vec3 getPos() { return pos;}
    glm::vec3 getDir() { return dir;}

  private:
    glm::vec3 pos;       //< origin of the ray 
    glm::vec3 dir;       //< direction of the ray                
};

#endif