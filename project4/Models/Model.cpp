#include "Model.h"

//////////////////////////////////////////////////////////////////////////////
// @brief: Process input file to retrieve information about the Model, including
//		   points, normals, textures, and faces; and position and orientation
//		   of the model.
// @param inputFile given name of the input file
// @param _name given name
// @param _materialFile given name of the mtl file
// @param _pos given position 
// @param _orientation given orientation
// @param _scale: vector to scale by
// @param _color: color of model
Model::Model(string inputFile, string materialFile, string _name, glm::vec3 _pos, glm::vec3 _orientation,
	glm::vec3 _scale, glm::vec3 _color){
	pos = _pos;
	name = _name;
	orientation = _orientation;
	scale = _scale;
	color = _color;
	// declare an input-file stream variable for reading
  ifstream inputFileStream;

  // open file and check that it was successfully opened
  inputFileStream.open(inputFile);
  if (!inputFileStream.is_open()){
    cerr << "Error: Unable to open file " << inputFile << endl;
    exit(1);
  }
  while (inputFileStream.good()){
  // Read each line
    string input;
    getline(inputFileStream, input);
       
    // Skip to next line if line is empty or starts with pound sign
    if(input == "")
      continue;
    else if (input[0] == '#')
      continue;

    if(input.find("usemtl") != string::npos && materialFile != "" && !materialInfo){
    /// TODO: Improve later. Right now we assume that the model
    /// is simple enough it only uses 1 texture. In reality, complex 
    /// models can have multiple textures for different faces
      materialInfo = make_shared<MaterialInfo>(materialFile, input.substr(7));
    }
    else
      getTokens(input);

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
  centerOfMass/=(points.size());
  inputFileStream.close();
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Read input file, then add models and information about each model's
//         position, orientation, color, scale.
// @param input: given string for input file name
// @param models: vector of Model pointers
void
Model::parseInModels(string input, unordered_map<string, shared_ptr<Model>>& models){
    //declare an input-file stream variable for reading
    ifstream inputFileStream;
    // open file and check that it was successfully opened
    inputFileStream.open(input);
    if (!inputFileStream.is_open()){
        cerr << "Error: Unable to open file " << input << endl;
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

        vector<string> tokens;
        string file, name, materialFile = "";
        glm::vec3 pos, orientation, color;
        glm::vec3 scale(1.0, 1.0, 1.0);
        Tokenizer::tokenize(input, " ", tokens);
        if(tokens[0] == "start"){
          do{
            getline(inputFileStream,input);
            Tokenizer::tokenize(input, " ", tokens);
            if(tokens[0] == "file")
              file = tokens[1];
            if(tokens[0] == "materialFile")
              materialFile = tokens[1];
            if(tokens[0] == "name")
              name = tokens[1];
            if(tokens[0] == "pos")
              pos = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
            if(tokens[0] == "orientation")
              orientation = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
            if(tokens[0] == "color")
              color = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
            if(tokens[0] == "scale")
              scale = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
          }
          while(tokens[0] != "end");
        }

        shared_ptr<Model> model = make_shared<Model>(file, materialFile, name, pos, orientation, scale, color);
        models.insert(make_pair(name, model));

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
// @brief: Read input line to call corresponding functions based on the 
//		   identifier "v", "vt", "vn", or "f"
// @param input the line given to extract information from
void Model::getTokens(string input){
	string identifier = input.substr(0,2);
	if(identifier == "v ")
		storeValue(input, points);
	else if (identifier == "vt")
		storeValue(input, textures);
	else if (identifier == "vn")
		storeValue(input, normals);
	else if (identifier == "f ")
		readFace(input);
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Read information of a glm::vec3's x, y, z coordinates
// 		   Add newly read glm::vec3'to the given vector<glm::vec3> (can be
//	       points, textures, normals)
// @param input the line given to extract information from
// @param vec given vector<glm::vec3> for the new vec3 to be added to
void Model::storeValue(string input, vector<glm::vec3>& vec){
	// extract x, y, z values
	vector<string> tokens;
	Tokenizer::tokenize(input, " ", tokens);
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	float z = 0;
	if(tokens.size() > 3){
    	z = atof(tokens[3].c_str());
    } 
	glm::vec3 point(x, y, z);
	centerOfMass = centerOfMass + point;
	vec.push_back(point);
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Read information of face.
// 		   Add newly read face to the model's face vector.
//		   Flexible for triangular and quadrilateral faces;
//		   Support these styles: f v v v
//                 f v/vt v/vt v/vt
//								 f v//vn v//vn v//vn
//								 f v/vt/vn v/vt/vn v/vt/vn
// @param input the line given to extract information from
void Model::readFace(string input){
	vector<string> tokens;
	Tokenizer::tokenize(input.substr(2), " ", tokens);
	size_t numVertices = 0;
	shared_ptr<Face> face = make_shared<Face>();
	for(auto& token : tokens){
    if(token.length() == 1){
      continue;
    }
		Vertex vertex;
		vector<string> triples;
		if(input.find("//") != string::npos){
			Tokenizer::tokenize(token, "//", triples);
			vertex.pointIdx = stoi(triples[0]);
			vertex.normalIdx = stoi(triples[1]);
		} 
		else if (input.find("/") != string::npos){
			Tokenizer::tokenize(token, "/", triples);
      vertex.pointIdx = stoi(triples[0]);
      vertex.textureIdx = stoi(triples[1]);
      if(triples.size() == 3)
        vertex.normalIdx = stoi(triples[2]);
		}
		else{
			vertex.pointIdx = stoi(token);
    }
		numVertices++;
		face->addVertex(vertex);
	}

	if(face->getNumVertices() == 3)
		facesTriangle.push_back(face);
	else if(face->getNumVertices() == 4)
		facesQuad.push_back(face);
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Draw face
// @param face Face to be drawn
void Model::drawFace(shared_ptr<Face> face) const {
	vector<Vertex> vertices = face->getVertices();
	for (auto& vertex : vertices){
    // Since some OBJ lines have format "f v v v" or "f v//vn v//vn v//vn",
    // check if OBJ line provides normals or textures before incorporating them
    // If the OBJ line provides normals
		if(vertex.normalIdx != 0){
			glm::vec3 normal = normals[vertex.normalIdx - 1];
			glNormal3f(normal.x, normal.y, normal.z);
		}
		// If the OBJ line provides textures
		if(vertex.textureIdx  != 0){
			glm::vec3 tex = textures[vertex.textureIdx - 1];
			glTexCoord2f(tex.x, tex.y);
		}
		glm::vec3 vec = points[vertex.pointIdx - 1];
		glVertex3f(vec.x,vec.y,vec.z);
	}
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Draw model
//		   Flexible for both triangular and quadrilateral faces
void Model::draw(){
	 // Style and color
  	glColor3f(color.x, color.y, color.z);
  	if(style == FILL)
  		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  	else if(style == POINT)
  		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  	else if(style == LINE)
  		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  	// Transformations
  	glPushMatrix();
    alpha += 2;
  	glTranslatef(pos.x, pos.y, pos.z);
    if(name == "Earth" || name == "Venus"){
      glRotatef(alpha, 0, 1, 0);
    }

  	glScalef(scale.x, scale.y, scale.z);
  	changeOrientation();
  	// Translated back to origin before any non-translation transformation
  	glTranslatef(-centerOfMass.x, -centerOfMass.y, -centerOfMass.z);
   
    // If the model contains texture material and we haven't loaded them
    if(materialNum == 0 && materialInfo){
      if(materialInfo->hasImageTexture())
        materialNum = materialInfo->setUpTexture();
    }
    if(materialInfo){
      glBindTexture(GL_TEXTURE_2D, materialNum);
      glEnable(GL_TEXTURE_2D);
      materialInfo->setUpMaterial();
    }
   
  	glBegin(GL_TRIANGLES);
  	for(auto& face : facesTriangle){
  		drawFace(face);
  	}
  	glEnd();
  	glBegin(GL_QUADS);
  	for(auto& face : facesQuad){
  		drawFace(face);
  	}
  	glEnd();

    if(materialInfo)
      glDisable(GL_TEXTURE_2D);
  	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Draw orbits or planets
void
Model::drawOrbits(){
  glColor4f(1, 1, 1, 0.3);
  float distFromSun = glm::length(glm::vec3(0,0,0) - pos);
  glBegin(GL_LINE_STRIP);
  for (float angle = 0.0f; angle < 2*M_PI; angle += 0.0001f){
    glVertex3f(sin(angle) * distFromSun, 0.0f,  cos(angle) * distFromSun);
  }
  glVertex3f(0.0f, 0.0f, distFromSun);
  
  glEnd();
}

//////////////////////////////////////////////////////////////////////////////
// @brief: Change orientation of model.
// @note: I could not find what functions of OpenGL can change 3D orientation, so
// I devised my own method, though I think it's messy and not 100% sure if it's correct.
void Model::changeOrientation(){
	// Change the xz-orientation of model
	glm::vec3 vec1 = glm::normalize(glm::vec3(orientation.x, 0, orientation.z));
	// Default xz orientation of model (without any orientation input) is (0,0,1)
	// Find the angle to rotate the model from default orientation to desired orientation,
	// with reference to the y-axis
	// Note that argument to glm::orientedAngle need to be normalized
	float angle = glm::orientedAngle(glm::vec3(0,0,1), vec1, glm::vec3(0,1,0));
	// convert angle from radians to degrees then rotate model with reference to y-axis
  	glRotatef(angle/M_PI * 180, 0, 1, 0);

  	// Change the y-orientation of model
  	glm::vec3 vec2(0, orientation.y, 1);
  	// Find the angle to rotate the model from y = 0 to y = orientation.y, keeping xz orientation
  	// the same
  	float angle2 = glm::orientedAngle(glm::vec3(0,0,1),
  		glm::normalize(glm::vec3(0,orientation.y,1)), glm::vec3(1,0,0));
   	glRotatef(angle2/M_PI * 180, 1, 0, 0); 
}