#include "RayTracer.h"

RayTracer::RayTracer(string inputFile, int w, int h){
  // Set width and height
  g_width = w;
  g_height = h;

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

    // Skip to next line if line is empty or starts with pound sign
    if(input == "")
      continue;
    else if (input[0] == '#')
      continue;

    vector<string> tokens;
    Tokenizer::tokenize(input, " ", tokens);
    if(tokens[0] == "Lights")
      Light::parseLights(tokens[1], lights);
    if(tokens[0] == "Spheres")
      Sphere::parseSpheres(tokens[1], spheres);
    if(tokens[0] == "eyePos")
      eyePos = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
    if(tokens[0] == "lookAt")
      lookAt = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
    if(tokens[0] == "upVec")
      upVec = glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()));
    if(tokens[0] == "fieldOfView")
      fov = atof(tokens[1].c_str());
    if(tokens[0] == "maxDepth")
      maxDepth = atoi(tokens[1].c_str());
    if(tokens[0] == "defaultBackground")
      defaultBg = glm::vec4(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()), atof(tokens[4].c_str()));
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
  // Transform all the sphere's coordinates into camera coordinates before hand
  glm::mat4 view = glm::lookAt(eyePos, lookAt, glm::vec3(0,1,0));
  for(auto& sphere : spheres)
    sphere->transformView(view);
  for(auto& light : lights)
    light->transformView(view);
  pixels = make_unique<glm::vec4[]>(g_width*g_height);
}

/////////////////////////////////////////////////////////////////////////////
// @brief: Trace a ray and compute the accumulative color of the objects the ray
//         hits (up until a specified recursive depth), if any
// @param ray: The ray we are tracing
// @param spheres: List of spheres in scene
// @param depth: the current depth level
// @return color of the object at the intersection points
//        or background color if no intersection is found
glm::vec4 RayTracer::traceRay(shared_ptr<Ray> ray, 
    vector<shared_ptr<Sphere>>& spheres, int depth){

  if(depth >= maxDepth)
    return(glm::vec4(0,0,0,0));
  // Minimum distance to the nearest intersection
  float minDist = numeric_limits<float>::infinity();
  // The sphere that the ray first hit
  shared_ptr<Sphere> currSphere;
  for(auto& sphere : spheres){
    float x1, x2;
    if(ray->findIntersection(sphere, x1, x2)) {
      // Prioritize x1 as it's the closer intersection among two roots (if there
      // are two). However, if x1 < 0 then the ray is inside the circle and in
      // front of x1
      if(x1 < 0)
        x1 = x2;
      if(x1 < minDist){
        minDist = x1;
        currSphere = sphere;
      }
    }
  }

  // If currSphere has not been assigned and is null, no intersection with the
  // ray is found, so we return the background color
  if(!currSphere)
    return(defaultBg);

  glm::vec3 intersectPoint = ray->getPos() + ray->getDir()*minDist;
  glm::vec3 N = glm::normalize(intersectPoint - currSphere->getCenter());
  glm::vec4 totalColor;   //< accumulated color at this pixel

  glm::vec4 color = calcLightColor(ray, N, currSphere, intersectPoint);
  totalColor += color;
  
  // Add reflected color
  bool insideSphere = false;
  // If ray.dir dot N > 0, we are inside the cirle
  /// normal and view are the same direction so we reverse N
  if(glm::dot(ray->getDir(),N) > 0){
    N*=(-1);
    insideSphere = true;
  }
  glm::vec3 R = ray->getDir() - N*(glm::dot(ray->getDir()*(2.f), N));
  shared_ptr<Ray> reflectionRay = make_shared<Ray>(intersectPoint, glm::normalize(R));
  glm::vec4 reflectedColor = traceRay(reflectionRay, spheres, depth + 1);
  float alpha = currSphere->getSurfaceColor()[3];
  color = (1 - alpha)*reflectedColor;
  totalColor += color;

  // Page 646 for plane
  // // Add refracted color
  // Calculate index of refraction inside (or outside) sphere, index of refraction
  // for air is 1.f

  // Generate first refracting ray
  float ratio = 1.f/currSphere->getIndexOfRefraction();
  float angleOfIncidence = glm::dot(N, ray->getDir()*(-1.f));
  float refractionAngle = sqrt(1.f - ratio*ratio*(1.f - angleOfIncidence*angleOfIncidence));
  glm::vec3 transmissionVec =  ray->getDir()*(ratio) - N*(refractionAngle - ratio*angleOfIncidence );
  shared_ptr<Ray> refractRay = make_shared<Ray>(intersectPoint , glm::normalize(transmissionVec));

  // Generate second refracting ray
  float s1 = 0, s2 = 0;
  // We know the second refract side's direction is into the sphere, so the first
  // intersection point will be on the surface of the sphere, the opposite side
  if(!refractRay->findIntersection(currSphere, s1, s2)){
    if(s1 == 0 )
      cout << "ERROR: Refract ray does not go through the other side of the sphere" << endl;
  }

  // s1 now contains the distance to the intersection point
  ratio = currSphere->getIndexOfRefraction();
  glm::vec3 otherIntersectPoint = refractRay->getPos() + refractRay->getDir()*s1;
  glm::vec3 otherN = glm::normalize(currSphere->getCenter() - otherIntersectPoint);
  angleOfIncidence =  glm::dot(otherN, refractRay->getDir()*(-1.f));
  refractionAngle = sqrt(1.f - ratio*ratio*(1.f - angleOfIncidence*angleOfIncidence));
  transmissionVec =  refractRay->getDir()*(ratio) - otherN*(refractionAngle - ratio*angleOfIncidence );
  shared_ptr<Ray> otherRefractRay = make_shared<Ray>(otherIntersectPoint,
    glm::normalize(transmissionVec));

  glm::vec4 refractColor = traceRay(otherRefractRay, spheres, depth + 1);
  totalColor += refractColor*alpha;

  return(totalColor*(1.f/minDist));
}


/////////////////////////////////////////////////////////////////////////////
// Calculate the color contributed by ambient light, diffuse and specular light
// @param N: normalized normal vector of sphere
// @param ray: The ray from viewer to object
// @param currSphere: the sphere we are investigating
// @param P: The point on the surface of the sphere that the ray intersects
glm::vec4
RayTracer::calcLightColor(shared_ptr<Ray> ray, glm::vec3 N, 
  shared_ptr<Sphere> currSphere, glm::vec3 P){
  // Ambient background color
  glm::vec3 color(0, 0, 0);
  glm::vec3 defaultBgVec3(defaultBg[0], defaultBg[1], defaultBg[2]);
  color += (defaultBgVec3*currSphere->getDiffuseReflectivity());

  bool shadowed = false;
  for(auto& light : lights){
    glm::vec3 dirToLight = glm::normalize(light->getPos() - P);
    // Create shadow ray
    shared_ptr<Ray> shadowRay = make_shared<Ray>(P, dirToLight); 
    for(auto& sphere : spheres){
      if(currSphere == sphere)
        continue;
      float t1, t2;
      if(shadowRay->findIntersection(sphere, t1, t2)){
        shadowed = true;
        break;
      }
    }

    if(!shadowed){
      // Ambient light color
      color += (light->getAmbientColor()*currSphere->getAmbientReflectivity());

      // Diffuse color
      float dotNL = glm::dot(N, dirToLight);
      if(dotNL > 0){
        color += (light->getDiffuseColor()*(currSphere->getDiffuseReflectivity()*dotNL));
      }

      // Specular lighting
      // Specular-reflection direction
      glm::vec3 R = glm::dot(N*(2.f), dirToLight)*N - dirToLight;
      float dotVR  = glm::dot(ray->getDir()*(-1.f), R);
      if(dotVR > 0 && dotNL > 0){
        color += (light->getSpecularColor()*(currSphere->getSpecularReflectivity()*(pow(dotVR, currSphere->getExponent()))));
      }
    }
  }
  glm::vec4 lightColor(color, 1);
  lightColor *= (currSphere->getSurfaceColor());
  return(lightColor);
}

void RayTracer::draw(){

  /////////////////////////////////////////////////////////////////////////////
  // Hard-coded variables for camera that should be user-specified later on
  // I learned about coordinates conversion at 
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
  // So helpful!
  
  for(int i = 0; i < g_width; i++){
    for(int j = 0; j < g_height; j++){
      // Normalized device coordinates
      // In range [0:1], the 0.5 is for the final camera ray to pass through 
      // the middle of the pixel
      float x = (i + 0.5)/g_width;
      float y = (j + 0.5)/g_height;

      // aspect ratio, accounted for in calculation for x so that pixels are 
      // not squashed/elongated
      float aspectRatio = (float)g_width/g_height;

      // Take tan(fov/2) to adjust up or down (equivalent to zooming in and out)
      float angle = glm::tan(glm::radians(fov/2));

      // Convert to screen coordinates, range [-1:1]
      x = (2*(x) - 1) * aspectRatio * angle;
      y = (1 - 2*(y)) * angle;

      // Direction of the ray (or pixel's position - eyePosition which is (0,0,0))
      glm::vec3 dir = glm::normalize(glm::vec3(x, y, -1));
      shared_ptr<Ray> ray = make_shared<Ray>(eyePos, dir);

      pixels[j * g_width + i] = traceRay(ray, spheres, 0);
  
    }
  }
  glDrawPixels(g_width, g_height, GL_RGBA, GL_FLOAT, pixels.get());
}