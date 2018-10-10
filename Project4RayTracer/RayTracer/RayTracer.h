#ifndef __RAY_TRACER__
#define __RAY_TRACER__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>
#include <memory>
#include <limits>

#include "../Utilities/glm/gtc/matrix_transform.hpp"
#include "../Utilities/glm/mat4x4.hpp"
#include "../Utilities/glm/trigonometric.hpp"
#include "../Utilities/Tokenizer.h"
#include "Ray.h"
#include "Sphere.h"
#include "../Simulation/Light.h"

#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>

#endif

using namespace std;
class RayTracer {
public:
  RayTracer(string inputFile, int w, int h);
  void draw();
  glm::vec4 traceRay(shared_ptr<Ray> ray, vector<shared_ptr<Sphere>>& spheres, int depth);
  glm::vec4 calcLightColor(shared_ptr<Ray> ray, glm::vec3 N, shared_ptr<Sphere> currSphere, glm::vec3 P);
  glm::vec4 calcReflectionColor(shared_ptr<Ray> ray, glm::vec3 N, shared_ptr<Sphere> currSphere, glm::vec3 P);
  glm::vec4 calcRefractionColor(shared_ptr<Ray> ray, glm::vec3 N, shared_ptr<Sphere> currSphere, glm::vec3 P);
private:
  int g_width;                            //< Width of the plane
  int g_height;                           //< Height of the plane
  int maxDepth;                           //< Max depth for recursive tracing rays

  vector<shared_ptr<Light>>lights;        //< Collection of lights
  vector<shared_ptr<Sphere>> spheres;     //< Collection of spheres
  // @TODO: make a movable camera
  // Camera camera;                       //< Camera

  // Camera parameters
  glm::vec3 eyePos;                       //< Eye position of camera
  glm::vec3 lookAt;                       //< Look at point of camera
  glm::vec3 upVec;                        //< Up vector of camera
  float fov;                              //< Field of view of camera

  unique_ptr<glm::vec4[]> pixels;         
  glm::vec4 defaultBg;                    //< Default background color of pixels

};

#endif