//////////////////////////////////////////////////////////////////////////////
// @brief: This class loads in Material from image, store variables from mtl 
// 		   file that are necessary to render realistic Materials and lighting
// References: I read the tutorial https://learnopengl.com/Getting-started/Materials
//			and used stb_image.h library developed by Sean Barrett
#ifndef MATERIALINFO_H
#define MATERIALINFO_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>

#endif
#include "../Utilities/Tokenizer.h"
#include "../Utilities/SOIL/src/SOIL.h"
class MaterialInfo {

private:
	string imageFile = "";
	GLfloat ambientReflectivity [4];			//< Ka
	GLfloat diffuseReflectivity [4];			//< Kd
	GLfloat specularReflectivity [4];			//< Ks
	GLfloat emissionReflectivity [4];			//< Ke
	GLfloat transmissionFilter [4];				//< Tf
	GLuint illumModel;							//< illum
	GLfloat dissolve;							//< d [-halo]
	GLfloat exponent;							//< Ns
	GLfloat sharpness;							//< sharpness
	GLfloat indexOfRefraction;					//< Ni
public:
	MaterialInfo(string materialFile, string materialLabel);
	unsigned int setUpTexture();
	void setUpMaterial();
	bool hasImageTexture(){ return (imageFile != "");}
};
#if   defined(OSX)
#pragma clang diagnostic pop
#endif
#endif