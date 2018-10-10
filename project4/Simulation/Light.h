#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>
#include "../Utilities/Tokenizer.h"
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
	GLenum getID(){ return id;}
	void toggleLight() { 
		on = !on;
		glDisable(id);
	}

private:
	GLenum id;					//< Enumeration for which light it is
	GLfloat pos [4];			//< Position
	GLfloat ambientColor[4];	//< Ambient color of the light
	GLfloat diffuseColor[4];	//< Diffuse color of the light
	GLfloat specularColor[4];	//< Specular color of the light
	GLfloat constantAtten{1.0}; //< Constant attenuation coefficient of light source
	GLfloat linearAtten{0.0};	//< Linear attenuation coefficient of light source
	GLfloat quadraticAtten{0.0};//< Quadratic attenuation coefficient of light source

	bool spotlight {false};     //< Indicates whether light is a spotlight
	bool on {true};				//< Lighting is on

	// For directional and spot light
	GLfloat dir [3];			//< Direction of directional light

	// For spot lights
	GLfloat spotCutOff;			//< Cone angle in degrees 
	GLfloat exponent;			//< exponent value for intensity attenuation
};
#endif