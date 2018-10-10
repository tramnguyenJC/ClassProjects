#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>
#include <memory>

#include "../Models/Model.h"
#include "Attractor.h"
#include "../Utilities/Camera.h"
#include "../Utilities/Tokenizer.h"
#include "Light.h"
#include "ParticleGenerator.h"
#include "Repeller.h"
#include "Obstacle.h"
class Simulator {

public:
	Simulator(string inputFile);
	void draw();
	void generateScene();
	void update();
	void toggleFog(){ 
		fog = !fog;
		glDisable(GL_FOG);
	}

	const vector<shared_ptr<Repeller>>& getRepellers(){ return repellers; }
	const vector<shared_ptr<Attractor>>& getAttractors(){ return attractors; }
	const vector<shared_ptr<ParticleGenerator>>& getGenerators() { return generators; }
	vector<shared_ptr<Light>>& getLights(){ return lights; }
	Camera& getCamera() {return camera;}

private:
	unordered_map<string, shared_ptr<Model>> models;
	vector<shared_ptr<ParticleGenerator>> generators;
	vector<shared_ptr<Obstacle>> obstacles;
	vector<shared_ptr<Repeller>> repellers;
	vector<shared_ptr<Attractor>> attractors;
	vector<shared_ptr<Light>> lights;
	bool flagAlreadySetBg{false};

	Camera camera;

	// Scene parameters
	glm::vec3 sceneColor;
	glm::vec3 planeColor;
	int planeSize;
	float timeStep;
	string staticModelFile;
	glm::vec3 cameraPos;
	glm::vec3 cameraDir;
	float angle{0.0f};

	void updateGenerators();
	void drawPlane();
	void drawFog();
	void movePlanetAroundSun(string planetName);
	void drawBackground();

	bool fog{false};
	bool enabled_lighting{false};
};
#endif