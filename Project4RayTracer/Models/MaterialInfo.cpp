#include "MaterialInfo.h"

// For loading texture from image
// Include this in cpp file after researching
// when include this in .h file there are duplicate symbols errors, as
// it gets defined in all the files that include that header
#define STB_IMAGE_IMPLEMENTATION
#include "../Utilities/stb_image.h"

MaterialInfo::MaterialInfo(string materialFile, string materialLabel){
	//declare an input-file stream variable for reading
    ifstream inputFileStream;
    // open file and check that it was successfully opened
    inputFileStream.open(materialFile);
    if (!inputFileStream.is_open()){
        cerr << "Error: Unable to open file " << materialFile << endl;
        exit(1);
    }
    while (inputFileStream.good()){
        string input;
        getline(inputFileStream, input);
        // Skip to next line if line is empty or starts with pound sign
        if(input == "")
          continue;
        else if (input[0] == '#')
          continue;
         // Skip to next line if line is empty or starts with pound sign
        if(input.find(materialLabel) != string::npos){  
            do {
                vector<string> tokens;
                getline(inputFileStream,input);
                Tokenizer::tokenize(input, " ", tokens);
                if(tokens.size() > 0 && tokens[0] == "map_Kd")
                    imageFile = tokens[1];
                if(tokens.size() > 0 && tokens[0] == "Ka"){
                    ambientReflectivity[0] = atof(tokens[1].c_str());
                    ambientReflectivity[1] = atof(tokens[2].c_str());
                    ambientReflectivity[2] = atof(tokens[3].c_str());
                    ambientReflectivity[3] = atof(tokens[4].c_str());
                }
                if(tokens.size() > 0 && tokens[0] == "Kd"){
                    diffuseReflectivity[0] = atof(tokens[1].c_str());
                    diffuseReflectivity[1] = atof(tokens[2].c_str());
                    diffuseReflectivity[2] = atof(tokens[3].c_str());
                    diffuseReflectivity[3] = atof(tokens[4].c_str());
                }
                if(tokens.size() > 0 && tokens[0] == "Ks"){
                    specularReflectivity[0] = atof(tokens[1].c_str());
                    specularReflectivity[1] = atof(tokens[2].c_str());
                    specularReflectivity[2] = atof(tokens[3].c_str());
                    specularReflectivity[3] = atof(tokens[4].c_str());
                }
                if(tokens.size() > 0 && tokens[0] == "Tf"){
                    transmissionFilter[0] = atof(tokens[1].c_str());
                    transmissionFilter[1] = atof(tokens[2].c_str());
                    transmissionFilter[2] = atof(tokens[3].c_str());
                    transmissionFilter[3] = atof(tokens[4].c_str());
                }
                if(tokens.size() > 0 && tokens[0] == "Ke"){
                    emissionReflectivity[0] = atof(tokens[1].c_str());
                    emissionReflectivity[1] = atof(tokens[2].c_str());
                    emissionReflectivity[2] = atof(tokens[3].c_str());
                    emissionReflectivity[3] = atof(tokens[4].c_str());
                }
                if(tokens.size() > 0 && tokens[0] == "illum")
                    illumModel = atoi(tokens[1].c_str());
                if(tokens.size() > 0 && tokens[0] == "d")
                    dissolve = atof(tokens[1].c_str());
                if(tokens.size() > 0 && tokens[0] == "Ns")
                    exponent = atof(tokens[1].c_str());
                if(tokens.size() > 0 && tokens[0] == "sharpness")
                    sharpness = atof(tokens[1].c_str());
                if(tokens.size() > 0 && tokens[0] == "Ni")
                    indexOfRefraction = atof(tokens[1].c_str());
            } while (input.find("newmtl") == string::npos && inputFileStream.good());
        }
    
        if(inputFileStream.fail()){
            if (inputFileStream.eof())
                break;
            else{
                // failed for some other reason than reaching eof
                // print a message and exit
                cerr << "Error reading data. " << endl;
                exit(1);
            }
        }
    }
    inputFileStream.close();
}

//////////////////////////////////////////////////////////////////////////////
// @brief: This function sets up material based on the material properties 
// specified in the mtl file
void 
MaterialInfo::setUpMaterial(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientReflectivity);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseReflectivity);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularReflectivity);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, exponent);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionReflectivity);
}

//////////////////////////////////////////////////////////////////////////////
// @brief: This function loads texture from image data and sets up texture
//		   for drawing models
// @return: the unsigned int representing the texture that we should bind to GL_TEXTURE_2D
unsigned int
MaterialInfo::setUpTexture(){
	/// REFERENCES: https://learnopengl.com/Getting-started/Textures
	/// Not written by me
	/// Generating a texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// // Set options
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Load data from image
	int width, height, numColorChannels;
	unsigned char *data = stbi_load(imageFile.c_str(), &width, &height, &numColorChannels, 0); 

	if(data){
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	} else {
		cout << "Failed to load texture from file: " << imageFile << endl;
	}
	stbi_image_free(data);
	return texture;
}