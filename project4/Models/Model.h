//////////////////////////////////////////////////////////////////////////////
// @brief: This class represents a model. Upon construction, the model would
// 		   process information about its vertices, normals, textures and faces
//		   through an input file. This class offers functions that process the 
//		   model and display it.

// @TODO: Refactor tokenize(), only use texture when mtl file exists/image texture is supported
// Do not apply specular lighting to objects with image textures
// glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // light up inside the sun
// glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Set back to default front lighting
 	
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>

// GLM
#include "../Utilities/glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL 
#include "../Utilities/glm/vec2.hpp" // glm::vec3
#include "../Utilities/glm/vec3.hpp" // glm::vec3
#include "../Utilities/glm/geometric.hpp" // For normalize, cross, dot product, scalar multiply, etc.
#include "../Utilities/glm/gtx/vector_angle.hpp" // For calculating angle between vectors
#include "../Utilities/glm/gtx/rotate_vector.hpp"

#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>

#endif

#include "Face.h"
#include "MaterialInfo.h"
#include "../Utilities/Tokenizer.h"

using namespace std;

// Different types of style
enum Style{
  LINE,
  FILL,
  POINT
};

class Model {
private:
	vector<glm::vec3> points;	        //< Vector of the model's vertices 
	vector<glm::vec3> normals;			//< Vector of the model's normals
	vector<glm::vec3> textures;		    //< Vector of the model's textures
	vector<shared_ptr<Face>> facesTriangle;	  	 //< Vector of the model's triangular faces
	vector<shared_ptr<Face>> facesQuad;	   		 //< Vector of the model's quadrilateral faces

	string name;						//< name of model
	Style style{FILL};				    //< style the model is drawn in
	glm::vec3 color{0.6f, 0.6f, 0.6f};  //< Color of the model, default to grey
	glm::vec3 pos;						//< position of model in the world
	glm::vec3 orientation;				//< orientation of model
	glm::vec3 scale;					//< factor to scale by
	glm::vec3 centerOfMass;				//< To scale then translate correctly
	shared_ptr<MaterialInfo> materialInfo;	//< Material object to handle all texture reading
											//< and loading
	unsigned int materialNum{0};
	float alpha = 0;
	void getTokens(string input);
	void storeValue(string input, vector<glm::vec3>& vec);
	void readFace(string input);
	void drawFace(shared_ptr<Face> face) const;
	void changeOrientation();
	float moonDist {0.f};					//< Distance of planet from moon
											//< Might not be a great design to make this a variable of Model,
											//< but I temporarily do so until I get more time to refactor
	glm::vec3 moonDir;						//< Direction from planet to moon
	
public:

	Model(string inputFile, string materialFile, string _name, glm::vec3 _pos, glm::vec3 _orientation, glm::vec3  scale, glm::vec3 _color);
	void draw();
	static void parseInModels(string inputFile, unordered_map<string, shared_ptr<Model>>& models);
	void setColor(glm::vec3 _color){ color = _color;}
	void setPos(glm::vec3 p){ pos = p; }
	glm::vec3 getPos(){ return pos; }
	void drawOrbits();

	// Getter methods
	const vector<glm::vec3>& getPoints() { return points; }
	const vector<glm::vec3>& getNormals() { return normals; }
	const vector<glm::vec3>& getTextures() { return textures; }
	float getMoonDist(){ return moonDist;}
	void setMoonDist(float d){ moonDist = d;}
	void setMoonDir(glm::vec3 dir){ moonDir = dir;}
	glm::vec3 getMoonDir(){return moonDir;}
	string getName(){return name;}

};

#if   defined(OSX)
#pragma clang diagnostic pop
#endif
#endif