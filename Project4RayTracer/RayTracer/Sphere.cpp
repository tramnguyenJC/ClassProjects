#include "Sphere.h"

/////////////////////////////////////////////////////////////////////////////
// Default constructor
// @param inputFileStream: stream passed in to read inputFile
Sphere::Sphere(ifstream& inputFileStream){
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
        
        if(tokens[0] == "center")
          center = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
        if(tokens[0] == "radius")
          r = atof(tokens[1].c_str());
        if(tokens.size() > 0 && tokens[0] == "Ka")
          ambientReflectivity = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
        if(tokens.size() > 0 && tokens[0] == "Kd")
          diffuseReflectivity = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
        if(tokens.size() > 0 && tokens[0] == "Ks")
          specularReflectivity = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
        if(tokens.size() > 0 && tokens[0] == "Ke")
          emissionReflectivity = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
        if(tokens.size() > 0 && tokens[0] == "SurfaceColor")
          surfaceColor = glm::vec4(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()), atof(tokens[4].c_str()));
        if(tokens.size() > 0 && tokens[0] == "d")
          dissolve = atof(tokens[1].c_str());
        if(tokens.size() > 0 && tokens[0] == "Ns")
          exponent = atof(tokens[1].c_str());
        if(tokens.size() > 0 && tokens[0] == "sharpness")
          sharpness = atof(tokens[1].c_str());
        if(tokens.size() > 0 && tokens[0] == "Ni")
          indexOfRefraction = atof(tokens[1].c_str());
      } while(tokens[0] != "end");
      break;
    } 
}

/////////////////////////////////////////////////////////////////////////////
// Transform the position of the sphere to be in camera coordinates
void 
Sphere::transformView(glm::mat4 view){
  glm::vec4 posVec4 = view*(glm::vec4(center, 1.0));
  center = glm::vec3(posVec4);
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Parse in the light input file and create lights accordingly
// @param inputFile filename of the generator input file
// @param lights a vector of lights that each newly created light should be added to.
void Sphere::parseSpheres(string inputFile,  vector<shared_ptr<Sphere>>& spheres){
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
      shared_ptr<Sphere> sphere = make_shared<Sphere>(inputFileStream);
      spheres.push_back(sphere);
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