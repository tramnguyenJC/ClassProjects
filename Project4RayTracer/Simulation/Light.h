#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>
#include "../Utilities/Tokenizer.h"
#include "../Utilities/glm/vec3.hpp" // glm::vec3
#include "../Utilities/glm/vec4.hpp" // glm::vec3
#include "../Utilities/glm/mat4x4.hpp"
#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>

#endif
class Light {
public:
	Light(ifstream& inputFileStream, unsigned int num);
	static void parseLights(string inputFile, vector<shared_ptr<Light>>& lights);
	void setLight();

	void transformView(glm::mat4 view);

	//////////////////////////////////////////////////////////////////////////////
	// Accessor methods
	GLenum getID(){ return id;}
	glm::vec3 getPos(){
		glm::vec3 posVec3(pos[0], pos[1], pos[2]);
		return posVec3;
	}
	glm::vec3 getDiffuseColor(){
		glm::vec3 myColor(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
		return myColor;
	}
	glm::vec3 getAmbientColor(){
		glm::vec3 myColor(ambientColor[0], ambientColor[1], ambientColor[2]);
		return myColor;
	}
	glm::vec3 getSpecularColor(){
		glm::vec3 myColor(specularColor[0], specularColor[1], specularColor[2]);
		return myColor;
	}
	float getConstantAtten(){ return constantAtten; }
	float getLinearAtten() { return linearAtten; }
	float getQuadraticAtten() { return quadraticAtten; }

	void toggleLight() { 
		on = !on;
		glDisable(id);
	}

private:
	GLenum id;												//< Enumeration for which light it is
	GLfloat pos [4];									//< Position
	GLfloat ambientColor[3];					//< Ambient color of the light
	GLfloat diffuseColor[3];					//< Diffuse color of the light
	GLfloat specularColor[3];					//< Specular color of the light
	GLfloat constantAtten{1.0};		 		//< Constant attenuation coefficient of light source
	GLfloat linearAtten{0.0};					//< Linear attenuation coefficient of light source
	GLfloat quadraticAtten{0.0};			//< Quadratic attenuation coefficient of light source

	bool spotlight {false};     			//< Indicates whether light is a spotlight
	bool on {true};										//< Lighting is on

	// For directional and spot light
	GLfloat dir [3];									//< Direction of directional light

	// For spot lights
	GLfloat spotCutOff;								//< Cone angle in degrees 
	GLfloat exponent;									//< exponent value for intensity attenuation
};
#endif