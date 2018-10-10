#ifndef __SPHERE__
#define __SPHERE__

#include "../Utilities/glm/vec3.hpp" // glm::vec3
#include "../Utilities/glm/mat4x4.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>
#include <memory>

#include "../Utilities/Tokenizer.h"

using namespace std;

class Sphere {
public:
  Sphere(ifstream& inputFileStream);
  glm::vec3 getCenter() { return center; }
  float getRadius() { return r;}
  void transformView(glm::mat4 view);
  static void parseSpheres(string inputFile,  vector<shared_ptr<Sphere>>& spheres);
  glm::vec3 getAmbientReflectivity() { return ambientReflectivity;}
  glm::vec3 getDiffuseReflectivity() { return diffuseReflectivity;}
  glm::vec3 getSpecularReflectivity() { return specularReflectivity;}
  glm::vec3 getEmissionReflectivity() { return emissionReflectivity;}
  glm::vec4 getSurfaceColor() { return surfaceColor;}
  float getExponent() { return exponent;}
  float getIndexOfRefraction() { return indexOfRefraction; }

private:
  float r;                                //< radius of sphere
  glm::vec3 center;                       //< center of sphere
  glm::vec4 surfaceColor;                 //< Surface color of sphere
  glm::vec3 ambientReflectivity;          //< Ka
  glm::vec3 diffuseReflectivity;          //< Kd
  glm::vec3 specularReflectivity;         //< Ks
  glm::vec3 emissionReflectivity;         //< Ke
  float dissolve;                         //< d [-halo]
  float exponent;                         //< Ns
  float sharpness;                        //< sharpness
  float indexOfRefraction;                //< Ni

};

#endif