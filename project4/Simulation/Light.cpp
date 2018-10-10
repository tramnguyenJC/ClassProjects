#include "Light.h"

//////////////////////////////////////////////////////////////////////////////
// @brief: Constructor
// @param inputFileStream: stream passed in to read inputFile
Light::Light(ifstream& inputFileStream, unsigned int num){
	while (inputFileStream.good()){
	    vector<string> tokens;
	    do {
	    	string input;
	    	getline(inputFileStream, input);
	    	Tokenizer::tokenize(input, " ", tokens);
	    	if(input == "end")
		      break;
		    if(input == "")
		      continue;
		    else if (input[0] == '#')
		      continue;
		    
	    	if(tokens[0] == "pos"){
	    		pos[0] = atof(tokens[1].c_str());
	    		pos[1] = atof(tokens[2].c_str());
	    		pos[2] = atof(tokens[3].c_str());
          pos[3] = atof(tokens[4].c_str());
	    	}
	    	if(tokens[0] == "dir"){
	    		dir[0] = atof(tokens[1].c_str());
	    		dir[1] = atof(tokens[2].c_str());
	    		dir[2] = atof(tokens[3].c_str());
	    	}
	    	if(tokens[0] == "ambientColor"){
	    		ambientColor[0] = atof(tokens[1].c_str());
	    		ambientColor[1] = atof(tokens[2].c_str());
	    		ambientColor[2] = atof(tokens[3].c_str());
	    		ambientColor[3] = atof(tokens[4].c_str());
	    	}
	    	if(tokens[0] == "diffuseColor"){
	    		diffuseColor[0] = atof(tokens[1].c_str());
	    		diffuseColor[1] = atof(tokens[2].c_str());
	    		diffuseColor[2] = atof(tokens[3].c_str());
	    		diffuseColor[3] = atof(tokens[4].c_str());
	    	}
	    	if(tokens[0] == "specularColor"){
	    		specularColor[0] = atof(tokens[1].c_str());
	    		specularColor[1] = atof(tokens[2].c_str());
	    		specularColor[2] = atof(tokens[3].c_str());
	    		specularColor[3] = atof(tokens[4].c_str());
	    	}
	    	if(tokens[0] == "constantAtten")
	    		constantAtten = atof(tokens[1].c_str());
	    	if(tokens[0] == "linearAtten")
	    		linearAtten = atof(tokens[1].c_str());
	    	if(tokens[0] == "quadraticAtten")
	    		quadraticAtten = atof(tokens[1].c_str());
	    	if(tokens[0] == "spotCutOff")
	    		spotCutOff = atof(tokens[1].c_str());
        if(tokens[0] == "spotlight")
          spotlight = true;
	    	if(tokens[0] == "exponent")
	    		exponent = atof(tokens[1].c_str());
	    } while(tokens[0] != "end");
	    break;
    	
  	}	
    switch(num) {
    case 0:
      id = GL_LIGHT0;
      break;
    case 1:
      id = GL_LIGHT1;
      break;
    case 2:
      id = GL_LIGHT2;
      break;
    case 3:
      id = GL_LIGHT3;
      break;
    case 4:
      id = GL_LIGHT4;
      break;
    case 5:
      id = GL_LIGHT5;
      break;
    case 6:
      id = GL_LIGHT6;
      break;
    case 7:
      id = GL_LIGHT7;
      break;
    default:
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////
// @brief: set the light parameters
void Light::setLight(){
  glLightfv(id, GL_POSITION, pos);  
  glLightfv(id, GL_AMBIENT, ambientColor);
  glLightfv(id, GL_DIFFUSE, diffuseColor);
  glLightfv(id, GL_SPECULAR, specularColor);
  if(spotlight){
    glLightfv(id, GL_SPOT_DIRECTION, dir);
    glLightf(id, GL_SPOT_CUTOFF, spotCutOff);
    glLightf(id, GL_SPOT_EXPONENT, exponent);
  } else {
    glLightf(id, GL_CONSTANT_ATTENUATION, constantAtten);
    glLightf(id, GL_LINEAR_ATTENUATION, linearAtten);
    glLightf(id, GL_QUADRATIC_ATTENUATION, quadraticAtten);
  }
  if(on)
    glEnable(id);
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Parse in the light input file and create lights accordingly
// @param inputFile filename of the generator input file
// @param lights a vector of lights that each newly created light should be added to.
void Light::parseLights(string inputFile, 
  vector<shared_ptr<Light>>& lights){
  int idx = 0;
  // declare an input-file stream variable for reading
  ifstream inputFileStream;

 // open file and check that it was successfully opened
  inputFileStream.open(inputFile);
  if (!inputFileStream.is_open()){
   cout << "inputFile: " << inputFile << endl;
   cerr << "Error: Unable to open file " << inputFile << endl;
   exit(1);
  }
  while (inputFileStream.good()){
  	string input;
    getline(inputFileStream, input);
    if(input == "")
      continue;
    else if (input[0] == '#')
      continue;
    
  	if(input == "start"){
	    shared_ptr<Light> light = make_shared<Light>(inputFileStream, idx++);
	    lights.push_back(light);
	}
    if(inputFileStream.fail()){
      if (inputFileStream.eof())
        break;
      else{
        cerr << "Error reading data. " << endl;
        exit(1);
      }
    }
  }
}
